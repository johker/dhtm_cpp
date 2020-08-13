#pragma once 

#include "../../dhtm_msg/cpp/messageConstants.hpp"

namespace dh {

class ZmqSubscriber {

public:
	bool operator==(const ZmqSubscriber& argZmqSubscriber) const
	{
		return subscriptionId == argZmqSubscriber.subscriptionId;
	}
	
	bool operator!=(const ZmqSubscriber& argZmqSubscriber) const
	{
		return subscriptionId != argZmqSubscriber.subscriptionId;
	}

	ComHandlerInterface* comHandler; 	
	MessageType messageType;
	int subscriptionId;
};

}

