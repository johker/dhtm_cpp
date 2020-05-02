#pragma once

#include <xtensor/xarray.hpp>
#include <zmq.hpp>

#include "../../dhtm_msg/cpp/messageConstants.hpp"

namespace dh {

class MessageEncoder {


public: 
	MessageEncoder();
	virtual ~MessageEncoder();

	static zmq::message_t createMessage(const MessageCommand& argMsgCmd, const MessageKey& argMsgKey, const xt::xarray<bool>& argSdr);
	static MessageCommand parseMessageCommand(const zmq::message_t& argMsg);
	static void printMessage(zmq::message_t& argMsg);

private:
	static uint32_t getUuid();
        
	static uint32_t uuid;

};
}
