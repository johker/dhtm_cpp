#pragma once

#include <zmq.hpp>
#include <bitset>

#include "coreConstants.hpp"
#include "../../dhtm_msg/cpp/messageConstants.hpp"
#include "../utils/logger.hpp"

namespace dh {

class MessageEncoder {


public: 
	MessageEncoder();
	virtual ~MessageEncoder();

	static zmq::message_t createMessage(const MessageCommand& argMsgCmd, const MessageKey& argMsgKey, const std::bitset<SDR>& argSdr);
	static MessageCommand parseMessageCommand(const unsigned char*& argMsgData);
	static MessageKey parseMessageKey(const unsigned char*& argMsgData);
	static std::bitset<SDR> parseSdr(const unsigned char*& argMsgData, const size_t& argMsgSize);
	static void printMessage(zmq::message_t& argMsg);

private:
	static uint32_t getUuid();
        
	static uint32_t uuid;

};
}
