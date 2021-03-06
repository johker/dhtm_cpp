#pragma once


#include <thread>
#include <mutex>
#include <queue>
#include <zmq.hpp>

#include "comInterface.hpp"
#include "zmqSubscriber.hpp"
#include "messageEncoder.hpp"
#include "../utils/itcTask.hpp"


namespace dh {

class ZmqConnector : public ComInterface, public ItcTask<zmq::message_t> {

public:
	ZmqConnector();
	ZmqConnector(std::string argSendProtocol, std::string argRcvProtocol);
	virtual ~ZmqConnector();

	virtual	int initialize();
	virtual	void publish(const ComMessage& argComMessage);
	virtual int subscribe(const MessageType& argMsgType, ComHandlerInterface* argComHandler);
	virtual void unsubscribe(const int& argSusbscriptionId);
	
protected:
	virtual bool handleMessage(std::shared_ptr<zmq::message_t> argMessage); 


private:
	void send(zmq::message_t& argMessage, const MessageType& argMsgType);

	zmq::context_t* zmqContext;
	zmq::socket_t* socketPublisher;
	zmq::socket_t* socketSubscriber;
	std::string recvProtocol;
	std::string sendProtocol;
	std::mutex sendMutex;
	std::mutex subscriberMutex;
	int subscriptionId = 0;
	std::vector<ZmqSubscriber> subscriptions;

};
}
