// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: AgentMessage.proto

#ifndef PROTOBUF_AgentMessage_2eproto__INCLUDED
#define PROTOBUF_AgentMessage_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_AgentMessage_2eproto();
void protobuf_AssignDesc_AgentMessage_2eproto();
void protobuf_ShutdownFile_AgentMessage_2eproto();

class AgentMessage;
class AgentMessage_Threads;
class AgentMessage_Threads_Thread;

// ===================================================================

class AgentMessage_Threads_Thread : public ::google::protobuf::Message {
 public:
  AgentMessage_Threads_Thread();
  virtual ~AgentMessage_Threads_Thread();
  
  AgentMessage_Threads_Thread(const AgentMessage_Threads_Thread& from);
  
  inline AgentMessage_Threads_Thread& operator=(const AgentMessage_Threads_Thread& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const AgentMessage_Threads_Thread& default_instance();
  
  void Swap(AgentMessage_Threads_Thread* other);
  
  // implements Message ----------------------------------------------
  
  AgentMessage_Threads_Thread* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AgentMessage_Threads_Thread& from);
  void MergeFrom(const AgentMessage_Threads_Thread& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required int32 id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  inline ::google::protobuf::int32 id() const;
  inline void set_id(::google::protobuf::int32 value);
  
  // required string name = 2;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 2;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  
  // required int32 priority = 3;
  inline bool has_priority() const;
  inline void clear_priority();
  static const int kPriorityFieldNumber = 3;
  inline ::google::protobuf::int32 priority() const;
  inline void set_priority(::google::protobuf::int32 value);
  
  // required string state = 4;
  inline bool has_state() const;
  inline void clear_state();
  static const int kStateFieldNumber = 4;
  inline const ::std::string& state() const;
  inline void set_state(const ::std::string& value);
  inline void set_state(const char* value);
  inline void set_state(const char* value, size_t size);
  inline ::std::string* mutable_state();
  inline ::std::string* release_state();
  
  // required bool isContextClassLoaderSet = 5;
  inline bool has_iscontextclassloaderset() const;
  inline void clear_iscontextclassloaderset();
  static const int kIsContextClassLoaderSetFieldNumber = 5;
  inline bool iscontextclassloaderset() const;
  inline void set_iscontextclassloaderset(bool value);
  
  // optional bool enteredMonitorWait = 6;
  inline bool has_enteredmonitorwait() const;
  inline void clear_enteredmonitorwait();
  static const int kEnteredMonitorWaitFieldNumber = 6;
  inline bool enteredmonitorwait() const;
  inline void set_enteredmonitorwait(bool value);
  
  // optional bool leftMonitorWait = 7;
  inline bool has_leftmonitorwait() const;
  inline void clear_leftmonitorwait();
  static const int kLeftMonitorWaitFieldNumber = 7;
  inline bool leftmonitorwait() const;
  inline void set_leftmonitorwait(bool value);
  
  // @@protoc_insertion_point(class_scope:AgentMessage.Threads.Thread)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_priority();
  inline void clear_has_priority();
  inline void set_has_state();
  inline void clear_has_state();
  inline void set_has_iscontextclassloaderset();
  inline void clear_has_iscontextclassloaderset();
  inline void set_has_enteredmonitorwait();
  inline void clear_has_enteredmonitorwait();
  inline void set_has_leftmonitorwait();
  inline void clear_has_leftmonitorwait();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* name_;
  ::google::protobuf::int32 id_;
  ::google::protobuf::int32 priority_;
  ::std::string* state_;
  bool iscontextclassloaderset_;
  bool enteredmonitorwait_;
  bool leftmonitorwait_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(7 + 31) / 32];
  
  friend void  protobuf_AddDesc_AgentMessage_2eproto();
  friend void protobuf_AssignDesc_AgentMessage_2eproto();
  friend void protobuf_ShutdownFile_AgentMessage_2eproto();
  
  void InitAsDefaultInstance();
  static AgentMessage_Threads_Thread* default_instance_;
};
// -------------------------------------------------------------------

class AgentMessage_Threads : public ::google::protobuf::Message {
 public:
  AgentMessage_Threads();
  virtual ~AgentMessage_Threads();
  
  AgentMessage_Threads(const AgentMessage_Threads& from);
  
  inline AgentMessage_Threads& operator=(const AgentMessage_Threads& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const AgentMessage_Threads& default_instance();
  
  void Swap(AgentMessage_Threads* other);
  
  // implements Message ----------------------------------------------
  
  AgentMessage_Threads* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AgentMessage_Threads& from);
  void MergeFrom(const AgentMessage_Threads& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  typedef AgentMessage_Threads_Thread Thread;
  
  // accessors -------------------------------------------------------
  
  // required string lifeCycle = 1;
  inline bool has_lifecycle() const;
  inline void clear_lifecycle();
  static const int kLifeCycleFieldNumber = 1;
  inline const ::std::string& lifecycle() const;
  inline void set_lifecycle(const ::std::string& value);
  inline void set_lifecycle(const char* value);
  inline void set_lifecycle(const char* value, size_t size);
  inline ::std::string* mutable_lifecycle();
  inline ::std::string* release_lifecycle();
  
  // repeated .AgentMessage.Threads.Thread thread = 2;
  inline int thread_size() const;
  inline void clear_thread();
  static const int kThreadFieldNumber = 2;
  inline const ::AgentMessage_Threads_Thread& thread(int index) const;
  inline ::AgentMessage_Threads_Thread* mutable_thread(int index);
  inline ::AgentMessage_Threads_Thread* add_thread();
  inline const ::google::protobuf::RepeatedPtrField< ::AgentMessage_Threads_Thread >&
      thread() const;
  inline ::google::protobuf::RepeatedPtrField< ::AgentMessage_Threads_Thread >*
      mutable_thread();
  
  // @@protoc_insertion_point(class_scope:AgentMessage.Threads)
 private:
  inline void set_has_lifecycle();
  inline void clear_has_lifecycle();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* lifecycle_;
  ::google::protobuf::RepeatedPtrField< ::AgentMessage_Threads_Thread > thread_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_AgentMessage_2eproto();
  friend void protobuf_AssignDesc_AgentMessage_2eproto();
  friend void protobuf_ShutdownFile_AgentMessage_2eproto();
  
  void InitAsDefaultInstance();
  static AgentMessage_Threads* default_instance_;
};
// -------------------------------------------------------------------

class AgentMessage : public ::google::protobuf::Message {
 public:
  AgentMessage();
  virtual ~AgentMessage();
  
  AgentMessage(const AgentMessage& from);
  
  inline AgentMessage& operator=(const AgentMessage& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const AgentMessage& default_instance();
  
  void Swap(AgentMessage* other);
  
  // implements Message ----------------------------------------------
  
  AgentMessage* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AgentMessage& from);
  void MergeFrom(const AgentMessage& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  typedef AgentMessage_Threads Threads;
  
  // accessors -------------------------------------------------------
  
  // required string timestamp = 1;
  inline bool has_timestamp() const;
  inline void clear_timestamp();
  static const int kTimestampFieldNumber = 1;
  inline const ::std::string& timestamp() const;
  inline void set_timestamp(const ::std::string& value);
  inline void set_timestamp(const char* value);
  inline void set_timestamp(const char* value, size_t size);
  inline ::std::string* mutable_timestamp();
  inline ::std::string* release_timestamp();
  
  // required int32 jvm_id = 2;
  inline bool has_jvm_id() const;
  inline void clear_jvm_id();
  static const int kJvmIdFieldNumber = 2;
  inline ::google::protobuf::int32 jvm_id() const;
  inline void set_jvm_id(::google::protobuf::int32 value);
  
  // optional .AgentMessage.Threads threads = 3;
  inline bool has_threads() const;
  inline void clear_threads();
  static const int kThreadsFieldNumber = 3;
  inline const ::AgentMessage_Threads& threads() const;
  inline ::AgentMessage_Threads* mutable_threads();
  inline ::AgentMessage_Threads* release_threads();
  
  // @@protoc_insertion_point(class_scope:AgentMessage)
 private:
  inline void set_has_timestamp();
  inline void clear_has_timestamp();
  inline void set_has_jvm_id();
  inline void clear_has_jvm_id();
  inline void set_has_threads();
  inline void clear_has_threads();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* timestamp_;
  ::AgentMessage_Threads* threads_;
  ::google::protobuf::int32 jvm_id_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  friend void  protobuf_AddDesc_AgentMessage_2eproto();
  friend void protobuf_AssignDesc_AgentMessage_2eproto();
  friend void protobuf_ShutdownFile_AgentMessage_2eproto();
  
  void InitAsDefaultInstance();
  static AgentMessage* default_instance_;
};
// ===================================================================


// ===================================================================

// AgentMessage_Threads_Thread

// required int32 id = 1;
inline bool AgentMessage_Threads_Thread::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void AgentMessage_Threads_Thread::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void AgentMessage_Threads_Thread::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void AgentMessage_Threads_Thread::clear_id() {
  id_ = 0;
  clear_has_id();
}
inline ::google::protobuf::int32 AgentMessage_Threads_Thread::id() const {
  return id_;
}
inline void AgentMessage_Threads_Thread::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
}

// required string name = 2;
inline bool AgentMessage_Threads_Thread::has_name() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void AgentMessage_Threads_Thread::set_has_name() {
  _has_bits_[0] |= 0x00000002u;
}
inline void AgentMessage_Threads_Thread::clear_has_name() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void AgentMessage_Threads_Thread::clear_name() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& AgentMessage_Threads_Thread::name() const {
  return *name_;
}
inline void AgentMessage_Threads_Thread::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void AgentMessage_Threads_Thread::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void AgentMessage_Threads_Thread::set_name(const char* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* AgentMessage_Threads_Thread::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  return name_;
}
inline ::std::string* AgentMessage_Threads_Thread::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// required int32 priority = 3;
inline bool AgentMessage_Threads_Thread::has_priority() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void AgentMessage_Threads_Thread::set_has_priority() {
  _has_bits_[0] |= 0x00000004u;
}
inline void AgentMessage_Threads_Thread::clear_has_priority() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void AgentMessage_Threads_Thread::clear_priority() {
  priority_ = 0;
  clear_has_priority();
}
inline ::google::protobuf::int32 AgentMessage_Threads_Thread::priority() const {
  return priority_;
}
inline void AgentMessage_Threads_Thread::set_priority(::google::protobuf::int32 value) {
  set_has_priority();
  priority_ = value;
}

// required string state = 4;
inline bool AgentMessage_Threads_Thread::has_state() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void AgentMessage_Threads_Thread::set_has_state() {
  _has_bits_[0] |= 0x00000008u;
}
inline void AgentMessage_Threads_Thread::clear_has_state() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void AgentMessage_Threads_Thread::clear_state() {
  if (state_ != &::google::protobuf::internal::kEmptyString) {
    state_->clear();
  }
  clear_has_state();
}
inline const ::std::string& AgentMessage_Threads_Thread::state() const {
  return *state_;
}
inline void AgentMessage_Threads_Thread::set_state(const ::std::string& value) {
  set_has_state();
  if (state_ == &::google::protobuf::internal::kEmptyString) {
    state_ = new ::std::string;
  }
  state_->assign(value);
}
inline void AgentMessage_Threads_Thread::set_state(const char* value) {
  set_has_state();
  if (state_ == &::google::protobuf::internal::kEmptyString) {
    state_ = new ::std::string;
  }
  state_->assign(value);
}
inline void AgentMessage_Threads_Thread::set_state(const char* value, size_t size) {
  set_has_state();
  if (state_ == &::google::protobuf::internal::kEmptyString) {
    state_ = new ::std::string;
  }
  state_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* AgentMessage_Threads_Thread::mutable_state() {
  set_has_state();
  if (state_ == &::google::protobuf::internal::kEmptyString) {
    state_ = new ::std::string;
  }
  return state_;
}
inline ::std::string* AgentMessage_Threads_Thread::release_state() {
  clear_has_state();
  if (state_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = state_;
    state_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// required bool isContextClassLoaderSet = 5;
inline bool AgentMessage_Threads_Thread::has_iscontextclassloaderset() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void AgentMessage_Threads_Thread::set_has_iscontextclassloaderset() {
  _has_bits_[0] |= 0x00000010u;
}
inline void AgentMessage_Threads_Thread::clear_has_iscontextclassloaderset() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void AgentMessage_Threads_Thread::clear_iscontextclassloaderset() {
  iscontextclassloaderset_ = false;
  clear_has_iscontextclassloaderset();
}
inline bool AgentMessage_Threads_Thread::iscontextclassloaderset() const {
  return iscontextclassloaderset_;
}
inline void AgentMessage_Threads_Thread::set_iscontextclassloaderset(bool value) {
  set_has_iscontextclassloaderset();
  iscontextclassloaderset_ = value;
}

// optional bool enteredMonitorWait = 6;
inline bool AgentMessage_Threads_Thread::has_enteredmonitorwait() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void AgentMessage_Threads_Thread::set_has_enteredmonitorwait() {
  _has_bits_[0] |= 0x00000020u;
}
inline void AgentMessage_Threads_Thread::clear_has_enteredmonitorwait() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void AgentMessage_Threads_Thread::clear_enteredmonitorwait() {
  enteredmonitorwait_ = false;
  clear_has_enteredmonitorwait();
}
inline bool AgentMessage_Threads_Thread::enteredmonitorwait() const {
  return enteredmonitorwait_;
}
inline void AgentMessage_Threads_Thread::set_enteredmonitorwait(bool value) {
  set_has_enteredmonitorwait();
  enteredmonitorwait_ = value;
}

// optional bool leftMonitorWait = 7;
inline bool AgentMessage_Threads_Thread::has_leftmonitorwait() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void AgentMessage_Threads_Thread::set_has_leftmonitorwait() {
  _has_bits_[0] |= 0x00000040u;
}
inline void AgentMessage_Threads_Thread::clear_has_leftmonitorwait() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void AgentMessage_Threads_Thread::clear_leftmonitorwait() {
  leftmonitorwait_ = false;
  clear_has_leftmonitorwait();
}
inline bool AgentMessage_Threads_Thread::leftmonitorwait() const {
  return leftmonitorwait_;
}
inline void AgentMessage_Threads_Thread::set_leftmonitorwait(bool value) {
  set_has_leftmonitorwait();
  leftmonitorwait_ = value;
}

// -------------------------------------------------------------------

// AgentMessage_Threads

// required string lifeCycle = 1;
inline bool AgentMessage_Threads::has_lifecycle() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void AgentMessage_Threads::set_has_lifecycle() {
  _has_bits_[0] |= 0x00000001u;
}
inline void AgentMessage_Threads::clear_has_lifecycle() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void AgentMessage_Threads::clear_lifecycle() {
  if (lifecycle_ != &::google::protobuf::internal::kEmptyString) {
    lifecycle_->clear();
  }
  clear_has_lifecycle();
}
inline const ::std::string& AgentMessage_Threads::lifecycle() const {
  return *lifecycle_;
}
inline void AgentMessage_Threads::set_lifecycle(const ::std::string& value) {
  set_has_lifecycle();
  if (lifecycle_ == &::google::protobuf::internal::kEmptyString) {
    lifecycle_ = new ::std::string;
  }
  lifecycle_->assign(value);
}
inline void AgentMessage_Threads::set_lifecycle(const char* value) {
  set_has_lifecycle();
  if (lifecycle_ == &::google::protobuf::internal::kEmptyString) {
    lifecycle_ = new ::std::string;
  }
  lifecycle_->assign(value);
}
inline void AgentMessage_Threads::set_lifecycle(const char* value, size_t size) {
  set_has_lifecycle();
  if (lifecycle_ == &::google::protobuf::internal::kEmptyString) {
    lifecycle_ = new ::std::string;
  }
  lifecycle_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* AgentMessage_Threads::mutable_lifecycle() {
  set_has_lifecycle();
  if (lifecycle_ == &::google::protobuf::internal::kEmptyString) {
    lifecycle_ = new ::std::string;
  }
  return lifecycle_;
}
inline ::std::string* AgentMessage_Threads::release_lifecycle() {
  clear_has_lifecycle();
  if (lifecycle_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = lifecycle_;
    lifecycle_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// repeated .AgentMessage.Threads.Thread thread = 2;
inline int AgentMessage_Threads::thread_size() const {
  return thread_.size();
}
inline void AgentMessage_Threads::clear_thread() {
  thread_.Clear();
}
inline const ::AgentMessage_Threads_Thread& AgentMessage_Threads::thread(int index) const {
  return thread_.Get(index);
}
inline ::AgentMessage_Threads_Thread* AgentMessage_Threads::mutable_thread(int index) {
  return thread_.Mutable(index);
}
inline ::AgentMessage_Threads_Thread* AgentMessage_Threads::add_thread() {
  return thread_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::AgentMessage_Threads_Thread >&
AgentMessage_Threads::thread() const {
  return thread_;
}
inline ::google::protobuf::RepeatedPtrField< ::AgentMessage_Threads_Thread >*
AgentMessage_Threads::mutable_thread() {
  return &thread_;
}

// -------------------------------------------------------------------

// AgentMessage

// required string timestamp = 1;
inline bool AgentMessage::has_timestamp() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void AgentMessage::set_has_timestamp() {
  _has_bits_[0] |= 0x00000001u;
}
inline void AgentMessage::clear_has_timestamp() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void AgentMessage::clear_timestamp() {
  if (timestamp_ != &::google::protobuf::internal::kEmptyString) {
    timestamp_->clear();
  }
  clear_has_timestamp();
}
inline const ::std::string& AgentMessage::timestamp() const {
  return *timestamp_;
}
inline void AgentMessage::set_timestamp(const ::std::string& value) {
  set_has_timestamp();
  if (timestamp_ == &::google::protobuf::internal::kEmptyString) {
    timestamp_ = new ::std::string;
  }
  timestamp_->assign(value);
}
inline void AgentMessage::set_timestamp(const char* value) {
  set_has_timestamp();
  if (timestamp_ == &::google::protobuf::internal::kEmptyString) {
    timestamp_ = new ::std::string;
  }
  timestamp_->assign(value);
}
inline void AgentMessage::set_timestamp(const char* value, size_t size) {
  set_has_timestamp();
  if (timestamp_ == &::google::protobuf::internal::kEmptyString) {
    timestamp_ = new ::std::string;
  }
  timestamp_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* AgentMessage::mutable_timestamp() {
  set_has_timestamp();
  if (timestamp_ == &::google::protobuf::internal::kEmptyString) {
    timestamp_ = new ::std::string;
  }
  return timestamp_;
}
inline ::std::string* AgentMessage::release_timestamp() {
  clear_has_timestamp();
  if (timestamp_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = timestamp_;
    timestamp_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// required int32 jvm_id = 2;
inline bool AgentMessage::has_jvm_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void AgentMessage::set_has_jvm_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void AgentMessage::clear_has_jvm_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void AgentMessage::clear_jvm_id() {
  jvm_id_ = 0;
  clear_has_jvm_id();
}
inline ::google::protobuf::int32 AgentMessage::jvm_id() const {
  return jvm_id_;
}
inline void AgentMessage::set_jvm_id(::google::protobuf::int32 value) {
  set_has_jvm_id();
  jvm_id_ = value;
}

// optional .AgentMessage.Threads threads = 3;
inline bool AgentMessage::has_threads() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void AgentMessage::set_has_threads() {
  _has_bits_[0] |= 0x00000004u;
}
inline void AgentMessage::clear_has_threads() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void AgentMessage::clear_threads() {
  if (threads_ != NULL) threads_->::AgentMessage_Threads::Clear();
  clear_has_threads();
}
inline const ::AgentMessage_Threads& AgentMessage::threads() const {
  return threads_ != NULL ? *threads_ : *default_instance_->threads_;
}
inline ::AgentMessage_Threads* AgentMessage::mutable_threads() {
  set_has_threads();
  if (threads_ == NULL) threads_ = new ::AgentMessage_Threads;
  return threads_;
}
inline ::AgentMessage_Threads* AgentMessage::release_threads() {
  clear_has_threads();
  ::AgentMessage_Threads* temp = threads_;
  threads_ = NULL;
  return temp;
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_AgentMessage_2eproto__INCLUDED
