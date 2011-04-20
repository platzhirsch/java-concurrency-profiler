/**
 * The agent profiler collects data based on specified callback events which occur inside the JVM.
 */

#include <iostream>
#include <string>

#include <jvmti.h>
#include <stdio.h>
#include <stdlib.h>

#include <vector>

#include "AgentSocket.h"
#include "AgentMessage.pb.h"
#include "Agent.h"
#include "AgentHelper.h"

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

#include <boost/lexical_cast.hpp>

using namespace google::protobuf::io;

/** Some constant maximum sizes */
#define MAX_TOKEN_LENGTH        16
#define MAX_THREAD_NAME_LENGTH  512
#define MAX_METHOD_NAME_LENGTH  1024

static jvmtiEnv *jvmti = NULL;
static jvmtiCapabilities capa;

static AgentSocket agentSocket("192.168.1.101", "50000");
static int JVM_ID;
static int THREAD_ID = 1;

/** Global agent data structure */
typedef struct {
	/** JVMTI Environment */
	jvmtiEnv *jvmti;
	jboolean vm_is_started;
	/** Data access Lock */
	jrawMonitorID lock;
} GlobalAgentData;

static GlobalAgentData *gdata;

static jlong combined_size;
static int num_class_refs;
static int num_field_refs;
static int num_array_refs;
static int num_classloader_refs;
static int num_signer_refs;
static int num_protection_domain_refs;
static int num_interface_refs;
static int num_static_field_refs;
static int num_constant_pool_refs;

/** Every JVMTI interface returns an error code, which should be checked
 *   to avoid any cascading errors down the line.
 *   The interface GetErrorName() returns the actual enumeration constant
 *   name, making the error messages much easier to understand.
 */
static void check_jvmti_error(jvmtiEnv *jvmti, jvmtiError errnum,
		const char *str) {
	if (errnum != JVMTI_ERROR_NONE) {
		char *errnum_str;

		errnum_str = NULL;
		jvmti->GetErrorName(errnum, &errnum_str);

		printf("ERROR: JVMTI: %d(%s): %s\n", errnum,
				(errnum_str == NULL ? "Unknown" : errnum_str),
				(str == NULL ? "" : str));
	}
}

/**
 * Inserts the data accessible by jthread into an AgentMessage.
 *
 * @todo memset ensures the stack variable are garbage free - what does that mean?
 *
 * @param agentMessage the agent message containing valuable information which are send by the socket.
 * @param thread the thread containing valueable information.
 * @param lifeCycle whether the thread is a new one (true) or a finished one (false).
 * @return the extended agent message.
 */
static AgentMessage mergeThreadData(AgentMessage agentMessage, jthread thread,
		bool lifeCycle) {

	jvmtiThreadInfo jvmtiThreadInfo;
	jint thr_st_ptr;
	jlong thr_id_ptr;
	jvmtiError error;

	(void) memset(&jvmtiThreadInfo, 0, sizeof(jvmtiThreadInfo));
	error = jvmti->GetThreadInfo(thread, &jvmtiThreadInfo);
	check_jvmti_error(jvmti, error, "Cannot get thread information.");

	error = jvmti->GetThreadState(thread, &thr_st_ptr);
	check_jvmti_error(jvmti, error, "Cannot get thread state.");

	std::string threadState;
	switch (thr_st_ptr & JVMTI_JAVA_LANG_THREAD_STATE_MASK) {
	case JVMTI_JAVA_LANG_THREAD_STATE_NEW:
		threadState = "NEW";
		break;
	case JVMTI_JAVA_LANG_THREAD_STATE_TERMINATED:
		threadState = "TERMINATED";
		break;
	case JVMTI_JAVA_LANG_THREAD_STATE_RUNNABLE:
		threadState = "RUNNABLE";
		break;
	case JVMTI_JAVA_LANG_THREAD_STATE_BLOCKED:
		threadState = "BLOCKED";
		break;
	case JVMTI_JAVA_LANG_THREAD_STATE_WAITING:
		threadState = "WAITING";
		break;
	case JVMTI_JAVA_LANG_THREAD_STATE_TIMED_WAITING:
		threadState = "TIMED_WAITING";
		break;
	default:
		threadState = "NONE";
		break;
	}

	jvmti->GetTag(thread, &thr_id_ptr);
	if (thr_id_ptr == 0) {
		jvmti->SetTag(thread, THREAD_ID);
		++THREAD_ID;
		jvmti->GetTag(thread, &thr_id_ptr);
	}

	AgentMessage::Threads *threads = agentMessage.mutable_threads();
	threads->set_lifecycle(lifeCycle ? "start" : "end");

	AgentMessage::Threads::Thread *newThread = threads->add_thread();
	newThread->set_id(thr_id_ptr);
	newThread->set_name(jvmtiThreadInfo.name);
	newThread->set_priority(jvmtiThreadInfo.priority);
	newThread->set_state(threadState);
	newThread->set_iscontextclassloaderset(jvmtiThreadInfo.context_class_loader
			== NULL);

	return agentMessage;
}

/** Enter a critical section by doing a JVMTI Raw Monitor Enter */
static void enter_critical_section(jvmtiEnv *jvmti) {
	jvmtiError error;

	error = jvmti->RawMonitorEnter(gdata->lock);
	check_jvmti_error(jvmti, error, "Cannot enter with raw monitor");
}

/** Exit a critical section by doing a JVMTI Raw Monitor Exit */
static void exit_critical_section(jvmtiEnv *jvmti) {
	jvmtiError error;

	error = jvmti->RawMonitorExit(gdata->lock);
	check_jvmti_error(jvmti, error, "Cannot exit with raw monitor");
}

/**
 * @todo investigate if it is possible to assign the error to a string
 *
 * @param err
 */
void describe(jvmtiError err) {
	jvmtiError err0;
	char *descr;

	err0 = jvmti->GetErrorName(err, &descr);
	if (err0 == JVMTI_ERROR_NONE) {
		std::cout << descr;
	} else {
		printf("error [%d]", err);
	}
}

/** Monitor wait callback */
static void JNICALL callbackMonitorContendedEnter(jvmtiEnv *jvmti_env,
		JNIEnv *jni_env, jthread thread, jobject object) {

	jlong thr_id_ptr;
	jvmti->GetTag(thread, &thr_id_ptr);

	AgentMessage agentMessage;
	agentMessage.mutable_contendedmonitor()->set_threadid(thr_id_ptr);
	Agent::Helper::commitAgentMessage(agentMessage, agentSocket, JVM_ID);
}

/** A new thread is started */
static void JNICALL callbackThreadStart(jvmtiEnv *jvmti_env, JNIEnv* env,
		jthread thread) {

	enter_critical_section(jvmti);
	{
		AgentMessage agentMessage;
		agentMessage = mergeThreadData(agentMessage, thread, true);
		Agent::Helper::commitAgentMessage(agentMessage, agentSocket, JVM_ID);
	}
	exit_critical_section(jvmti);
}

/** Thread End callback */
static void JNICALL callbackThreadEnd(jvmtiEnv *jvmti_env, JNIEnv* env,
		jthread thread) {

	enter_critical_section(jvmti);
	{
		AgentMessage agentMessage;
		agentMessage = mergeThreadData(agentMessage, thread, false);
		Agent::Helper::commitAgentMessage(agentMessage, agentSocket, JVM_ID);
	}
	exit_critical_section(jvmti);
}

/** Exception callback */
static void JNICALL callbackException(jvmtiEnv *jvmti_env, JNIEnv* env,
		jthread thr, jmethodID method, jlocation location, jobject exception,
		jmethodID catch_method, jlocation catch_location) {

	enter_critical_section(jvmti);
	{

	}
	exit_critical_section(jvmti);

}
/** VM Death callback */
static void JNICALL callbackVMDeath(jvmtiEnv *jvmti_env, JNIEnv* jni_env) {
	enter_critical_section(jvmti);
	{

		printf("Got VM Death event\n");

		jvmtiError error;
		jint threadCount;
		jvmtiThreadInfo jvmtiThreadInfo;
		jthread *threads;

		AgentMessage agentMessage;
		error = jvmti->GetAllThreads(&threadCount, &threads);
		check_jvmti_error(jvmti, error, "Cannot get all threads.");

		if (threadCount > 0) {
			for (int i = 0; i < threadCount; ++i) {
				agentMessage = mergeThreadData(agentMessage, threads[i], true);
			}
			Agent::Helper::commitAgentMessage(agentMessage, agentSocket, JVM_ID);
		}
		exit_critical_section(jvmti);
	}
}

/** Get a name for a jthread */
static void get_thread_name(jvmtiEnv *jvmti, jthread thread, char *tname,
		int maxlen) {
	jvmtiThreadInfo info;
	jvmtiError error;

	/* Make sure the stack variables are garbage free */
	(void) memset(&info, 0, sizeof(info));

	/* Assume the name is unknown for now */
	(void) strcpy(tname, "Unknown");

	/* Get the thread information, which includes the name */
	error = jvmti->GetThreadInfo(thread, &info);
	check_jvmti_error(jvmti, error, "Cannot get thread info");

	/* The thread might not have a name, be careful here. */
	if (info.name != NULL) {
		int len;

		/* Copy the thread name into tname if it will fit */
		len = (int) strlen(info.name);
		if (len < maxlen) {
			(void) strcpy(tname, info.name);
		}

		/* Every string allocated by JVMTI needs to be freed */
		error = jvmti->Deallocate((unsigned char*) info.name);
		if (error != JVMTI_ERROR_NONE) {
			printf("(get_thread_name) Error expected: %d, got: %d\n",
					JVMTI_ERROR_NONE, error);
			describe(error);
			printf("\n");
		}

	}
}

/** VM init callback */
static void JNICALL callbackVMInit(jvmtiEnv *jvmti_env, JNIEnv* jni_env,
		jthread thread) {
	enter_critical_section(jvmti);
	{

		char tname[MAX_THREAD_NAME_LENGTH];
		static jvmtiEvent events[] = { JVMTI_EVENT_THREAD_START,
				JVMTI_EVENT_THREAD_END };
		int i;
		jvmtiFrameInfo frames[5];
		jvmtiError err, err1;
		jvmtiError error;
		jint count;

		/* The VM has started. */
		printf("Got VM init event\n");

		get_thread_name(jvmti_env, thread, tname, sizeof(tname));
		printf("callbackVMInit:  %s thread\n", tname);

		error = jvmti->SetEventNotificationMode(JVMTI_ENABLE,
				JVMTI_EVENT_EXCEPTION, (jthread) NULL);

		error = jvmti->SetEventNotificationMode(JVMTI_ENABLE,
				JVMTI_EVENT_THREAD_START, (jthread) NULL);

		error = jvmti->SetEventNotificationMode(JVMTI_ENABLE,
				JVMTI_EVENT_THREAD_END, (jthread) NULL);

		error = jvmti->SetEventNotificationMode(JVMTI_ENABLE,
				JVMTI_EVENT_MONITOR_CONTENDED_ENTER, (jthread) NULL);

		check_jvmti_error(jvmti_env, error, "Cannot set event notification");

		/*
		 * get all available threads and send them via socket
		 */
		jint threadCount;
		jthread *threads;

		AgentMessage agentMessage;
		error = jvmti->GetAllThreads(&threadCount, &threads);
		check_jvmti_error(jvmti, error, "Cannot get all threads.");

		if (threadCount > 0) {
			for (int i = 0; i < threadCount; ++i) {
				agentMessage = mergeThreadData(agentMessage, threads[i], true);
			}
			Agent::Helper::commitAgentMessage(agentMessage, agentSocket, JVM_ID);
		}
	}
	exit_critical_section(jvmti);
}

/** JVMTI callback function. */
static jvmtiIterationControl JNICALL
reference_object(jvmtiObjectReferenceKind reference_kind, jlong class_tag,
		jlong size, jlong* tag_ptr, jlong referrer_tag, jint referrer_index,
		void *user_data) {

	combined_size = combined_size + size;

	switch (reference_kind) {

	case JVMTI_REFERENCE_CLASS:
		num_class_refs = num_class_refs + 1;
		break;
	case JVMTI_REFERENCE_FIELD:
		num_field_refs = num_field_refs + 1;
		break;
	case JVMTI_REFERENCE_ARRAY_ELEMENT:
		num_array_refs = num_array_refs + 1;
		break;
	case JVMTI_REFERENCE_CLASS_LOADER:
		num_classloader_refs = num_classloader_refs + 1;
		break;
	case JVMTI_REFERENCE_SIGNERS:
		num_signer_refs = num_signer_refs + 1;
		break;
	case JVMTI_REFERENCE_PROTECTION_DOMAIN:
		num_protection_domain_refs = num_protection_domain_refs + 1;
		break;
	case JVMTI_REFERENCE_INTERFACE:
		num_interface_refs = num_interface_refs + 1;
		break;
	case JVMTI_REFERENCE_STATIC_FIELD:
		num_static_field_refs = num_static_field_refs + 1;
		break;
	case JVMTI_REFERENCE_CONSTANT_POOL:
		num_constant_pool_refs = num_constant_pool_refs + 1;
		break;
	default:
		break;
	}

	return JVMTI_ITERATION_CONTINUE;
}

static void JNICALL callbackVMObjectAlloc(jvmtiEnv *jvmti_env, JNIEnv* jni_env,
		jthread thread, jobject object, jclass object_klass, jlong size) {

	char *methodName;
	char *className;
	char *declaringClassName;
	jclass declaring_class;
	jvmtiError err;

	if (size > 50) {
		err = jvmti->GetClassSignature(object_klass, &className, NULL);

		if (className != NULL) {
			//                        printf("\ntype %s object allocated with size %d\n", className, (jint)size);
		}

		//print stack trace
		jvmtiFrameInfo frames[5];
		jint count;
		int i;

		err
				= jvmti->GetStackTrace(NULL, (jint) 0, (jint) 5, &frames[0],
						&count);
		if (err == JVMTI_ERROR_NONE && count >= 1) {

			for (i = 0; i < count; i++) {
				err = jvmti->GetMethodName(frames[i].method, &methodName, NULL,
						NULL);
				if (err == JVMTI_ERROR_NONE) {

					err = jvmti->GetMethodDeclaringClass(frames[i].method,
							&declaring_class);
					err = jvmti->GetClassSignature(declaring_class,
							&declaringClassName, NULL);
					if (err == JVMTI_ERROR_NONE) {
						//                                                printf("at method %s in class %s\n", methodName, declaringClassName);
					}
				}
			}
		}

		//reset counters
		combined_size = 0;
		num_class_refs = 0;
		num_field_refs = 0;
		num_array_refs = 0;
		num_classloader_refs = 0;
		num_signer_refs = 0;
		num_protection_domain_refs = 0;
		num_interface_refs = 0;
		num_static_field_refs = 0;
		num_constant_pool_refs = 0;

		err = jvmti->IterateOverObjectsReachableFromObject(object,
				&reference_object, NULL);
		if (err != JVMTI_ERROR_NONE) {
			printf("Cannot iterate over reachable objects\n");
		}

		//                printf("\nThis object has references to objects of combined size %d\n", (jint)combined_size);
		//                printf("This includes %d classes, %d fields, %d arrays, %d classloaders, %d signers arrays,\n", num_class_refs, num_field_refs, num_array_refs, num_classloader_refs, num_signer_refs);
		//                printf("%d protection domains, %d interfaces, %d static fields, and %d constant pools.\n\n", num_protection_domain_refs, num_interface_refs, num_static_field_refs, num_constant_pool_refs);

		err = jvmti->Deallocate((unsigned char*) className);
		err = jvmti->Deallocate((unsigned char*) methodName);
		err = jvmti->Deallocate((unsigned char*) declaringClassName);
	}
}

/*
 * Invoked when loading the library
 */
JNIEXPORT
jint JNICALL Agent_OnLoad(JavaVM *jvm, char *options, void *reserved) {

	static GlobalAgentData data;
	jvmtiError error;
	jint res;
	jvmtiEventCallbacks callbacks;

	JVM_ID = boost::lexical_cast<int>(options);

	/* Setup initial global agent data area
	 * Use of static/extern data should be handled carefully here.
	 * We need to make sure that we are able to cleanup after ourselves
	 * so anything allocated in this library needs to be freed in
	 * the Agent_OnUnload() function.
	 */
	(void) memset((void*) &data, 0, sizeof(data));
	gdata = &data;

	/*  get the jvmtiEnv* or JVMTI environment */
	res = jvm->GetEnv((void **) &jvmti, JVMTI_VERSION_1_0);

	if (res != JNI_OK || jvmti == NULL) {
		/* This means that the VM was unable to obtain this version of the
		 *   JVMTI interface, this is a fatal error.
		 */
		printf("ERROR: Unable to access JVMTI Version 1 (0x%x),"
			" is your J2SE a 1.5 or newer version?"
			" JNIEnv's GetEnv() returned %d\n", JVMTI_VERSION_1, res);

	}

	/* Here we save the jvmtiEnv* for Agent_OnUnload(). */
	gdata->jvmti = jvmti;

	/* set the needed capabukutues needed for profiling */
	(void) memset(&capa, 0, sizeof(jvmtiCapabilities));
	capa.can_signal_thread = 1;
	capa.can_get_owned_monitor_info = 1;
	capa.can_generate_method_entry_events = 1;
	capa.can_generate_exception_events = 1;
	capa.can_generate_vm_object_alloc_events = 1;
	capa.can_tag_objects = 1;
	capa.can_generate_monitor_events = 1;

	error = jvmti->AddCapabilities(&capa);
	check_jvmti_error(jvmti, error,
			"Unable to get necessary JVMTI capabilities.");

	/* register callback functions */
	(void) memset(&callbacks, 0, sizeof(callbacks));
	callbacks.VMInit = &callbackVMInit; /* JVMTI_EVENT_VM_INIT */
	callbacks.VMDeath = &callbackVMDeath; /* JVMTI_EVENT_VM_DEATH */
	callbacks.Exception = &callbackException;/* JVMTI_EVENT_EXCEPTION */
	callbacks.VMObjectAlloc = &callbackVMObjectAlloc;/* JVMTI_EVENT_VM_OBJECT_ALLOC */
	callbacks.ThreadStart = &callbackThreadStart;/* JVMTI_EVENT_THREAD_START */
	callbacks.ThreadEnd = &callbackThreadEnd;/* JVMTI_EVENT_THREAD_END */
	callbacks.MonitorContendedEnter = &callbackMonitorContendedEnter;/* JVMTI_EVENT_MONITOR_CONTENDED_ENTER*/

	error = jvmti->SetEventCallbacks(&callbacks, (jint) sizeof(callbacks));
	check_jvmti_error(jvmti, error, "Cannot set jvmti callbacks");

	/*
	 * Activate the notification of certain events. At first only initial events are activated.
	 * More events are requested on demand.
	 *
	 * The NULL argument implies global notifying, a thread can be passed for local notifying.
	 */
	error = jvmti->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_VM_INIT,
			(jthread) NULL);
	error = jvmti->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_VM_DEATH,
			(jthread) NULL);
	error = jvmti->SetEventNotificationMode(JVMTI_ENABLE,
			JVMTI_EVENT_VM_OBJECT_ALLOC, (jthread) NULL);
	check_jvmti_error(jvmti, error, "Cannot set event notification");

	/* Here we create a raw monitor for our use in this agent to
	 *   protect critical sections of code.
	 */
	error = jvmti->CreateRawMonitor("agent data", &(gdata->lock));
	check_jvmti_error(jvmti, error, "Cannot create raw monitor");

	/* Return JNI_OK to signify success */
	return JNI_OK;

}

/* Agent_OnUnload: This is called immediately before the shared library is
 *   unloaded. This is the last code executed.
 */
JNIEXPORT void JNICALL
Agent_OnUnload(JavaVM *vm) {
	/* Make sure all malloc/calloc/strdup space is freed */

}
