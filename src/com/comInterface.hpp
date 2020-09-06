#pragma once

#include <bitset>

#include "../htm/htmConstants.hpp"
#include "comHandlerInterface.hpp"
#include "../../dhtm_msg/cpp/messageConstants.hpp"

namespace dh {

class ComMessage {

public: 
	ComMessage(MessageType argMessageType, MessageCommand argMessageCommand, MessageKey argMessageKey, float argParameter) 
		: messageType(argMessageType),
		messageCommand(argMessageCommand),
		messageKey(argMessageKey),
		parameter(argParameter)
	{}
	
	ComMessage(MessageType argMessageType, MessageCommand argMessageCommand, MessageKey argMessageKey, bitset<SDR> argSdr)
		: messageType(argMessageType),
		messageCommand(argMessageCommand),
		messageKey(argMessageKey),
		sdr(argSdr)
	{}

	MessageType messageType;
	MessageCommand messageCommand; 
	MessageKey messageKey;
	float parameter;
	bitset<SDR> sdr;

}

class ComInterface {

public: 
	ComInterface() {};
	virtual ~ComInterface() {};

	virtual int initialize() = 0;
	virtual	void publish(const ComMessage& argComMessage) = 0;
	virtual int subscribe(const MessageType& argMsgType, ComHandlerInterface* argComHandler) = 0;
	virtual void unsubscribe(int argSubscriptionId) = 0;
	
};
}
