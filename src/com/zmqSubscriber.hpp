#pragma once 

namespace dh {

class ZmqSubscriber {

public:
	bool operator==(const & ZmqSubscriber argZmqSubscriber) const
	{
		return subscriptionId == argZmqSubscriber.subscriptionId;
	}
	
	bool operator!=(const & ZmqSubscriber argZmqSubscriber) const
	{
		return subscriptionId != argZmqSubscriber.subscriptionId;
	}

	ComHandlerInterface* comHandler; 	
	int subscriptionId;
}

}

