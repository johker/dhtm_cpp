#pragma once

#include <bitset>

#include "../htm/htmConstants.hpp"
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
	
	ComMessage(MessageType argMessageType, MessageCommand argMessageCommand, MessageKey argMessageKey, std::bitset<SDR> argSdr)
		: messageType(argMessageType),
		messageCommand(argMessageCommand),
		messageKey(argMessageKey),
		sdr(argSdr)
	{}

	MessageType messageType;
	MessageCommand messageCommand; 
	MessageKey messageKey;
	float parameter;
	std::bitset<SDR> sdr;

};

class ComHandlerInterface {

public:
	ComHandlerInterface(); 
	
	virtual ~ComHandlerInterface();

	virtual void handleMessageCallback(std::shared_ptr<ComMessage> argComMessage) = 0; 

};

class ComInterface {

public: 
	ComInterface() {};
	virtual ~ComInterface() {};

	virtual int initialize() = 0;
	virtual	void publish(const ComMessage& argComMessage) = 0;
	virtual int subscribe(const MessageType& argMsgType, ComHandlerInterface* argComHandler) = 0;
	virtual void unsubscribe(const int& argSubscriptionId) = 0;
	
};
}
