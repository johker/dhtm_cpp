#pragma once

#include <bitset>

#include "coreConstants.hpp"
#include "../../dhtm_msg/cpp/messageConstants.hpp"

namespace dh {

class ComInterface {

public: 
	ComInterface() {};
	virtual ~ComInterface() {};

	virtual int initialize() = 0;
	
	virtual	void publish(const MessageType& argMsgType, const MessageCommand& argMsgCmd, const MessageKey& argMsgKey, const std::bitset<SDR>& argPayload) = 0;

	virtual	void publish(const MessageType& argMsgType, const MessageCommand& argMsgCmd, const MessageKey& argMsgKey, const float& argPayload) = 0;

	virtual int subscribe() = 0;

	virtual void unsubscribe() = 0;
	
};
}
