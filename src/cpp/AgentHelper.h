/*
 * AgentHelper.h
 *
 *  Created on: 19.04.2011
 *      Author: Konrad Johannes Reiche
 */

#ifndef AGENTHELPER_H_
#define AGENTHELPER_H_

#include <jvmti.h>

#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

#include "AgentSocket.h"

#include "AgentMessage.pb.h"

namespace Agent {

namespace Helper {

/**
 * Sends an agent message via socket to the listening interface.
 * The message is serialized to a byte stream.
 *
 * @param agentMessage
 * @param agentSocket
 * @param JVM_ID
 */
void commitAgentMessage(AgentMessage agentMessage, AgentSocket agentSocket,
		int JVM_ID);

}
}

#endif /* AGENTHELPER_H_ */
