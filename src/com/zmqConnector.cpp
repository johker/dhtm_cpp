#include "zmqConnector.hpp"

namespace dh {

ZmqConnector::ZmqConnector() : ItcTask("0mq") {
	sendProtocol = "tcp://localhost:6000";
	recvProtocol = "tcp://localhost:5555";
}
ZmqConnector::ZmqConnector(std::string argSendProtocol, std::string argRcvProtocol) : ItcTask("0mq") {
	sendProtocol = argSendProtocol; 
	recvProtocol = argRcvProtocol;
}
ZmqConnector::~ZmqConnector() {
	stopItcTask(); 
	if(nullptr != socketPublisher) {
	       socketPublisher->close();
	}
	if(nullptr != socketSubscriber) {
		socketSubscriber->close();
	}
	if(nullptr != zmqContext) {
		zmqContext->close();
	}	
}

int ZmqConnector::initialize() {
	std::lock_guard<std::mutex> mutexLock(sendMutex);
	zmqContext = new zmq::context_t(1);
	socketPublisher = new zmq::socket_t(*zmqContext, ZMQ_PUB);
	socketPublisher->connect(sendProtocol);
	socketSubscriber = new zmq::socket_t(*zmqContext, ZMQ_SUB);
	socketSubscriber->connect(recvProtocol);
	startItcTask(); 
	DEBUG("0mq Connector started");
	return 0;
}

void ZmqConnector::publish(const MessageType& argMsgType, const MessageCommand& argMsgCmd, const MessageKey& argMsgKey, const std::bitset<SDR>& argPayload) {
	zmq::message_t message = MessageEncoder::createMessage(argMsgType, argMsgCmd, argMsgKey, argPayload);
	send(message, argMsgType);
}

void ZmqConnector::publish(const MessageType& argMsgType, const MessageCommand& argMsgCmd, const MessageKey& argMsgKey, const float& argPayload) {
	zmq::message_t message = MessageEncoder::createMessage(argMsgType, argMsgCmd, argMsgKey, argPayload);
	send(message, argMsgType);
}

void send(zmq::message_t argMessage, const MessageType& argMsgType) {
	std::lock_guard<std::mutex> mutexLock(sendMutex);
	std::string topic = MessageEncoder::createTopic(argMsgType);
	zmq::message_t rx_topic(topic.length());
	memcpy(rx_topic.data(), topic.c_str(), topic.length());
	socketPublisher->send(rx_topic, zmq::send_flags::sndmore);
	socketPublisher->send(message, zmq::send_flags::none);
}

int ZmqConnector::subscribe(const MessageType& argMsgType, ComHandlerInterface* argComHandler) {
	std::lock_guard<std:mutex> mutexLock(subscriberMutex);
	std::string topic = MessageEncoder::createTopic(argMsgType);
	ZmqSubscriber subscriber; 
	susbcriber.subscriberId = subscriberId++;
	subscriber.messageType = argMsgType;
	subcsriber.comHandler = argComHandler;
	subscriptions.push_back(subscriber);
	socketSubscriber->setsocketopt(ZMQ_SUBSCRIBE, topic.c_str(), topic.length());
	return subscriberId;
}

void ZmwConnector::unsubscribe(const int& argSusbscriptionId) {
	std::lock_guard<std::mutex> mutexLock(subscriberMutex);
	for(auto& s : subscriptions) {
		if(s.subscriptionId == argSubscriptionId) {
			std::string topic = MessageEncoder::createTopic(s.messageType);
			socketSubscriber->setsocketopt(ZMQ_UNSUBSCRIBE, topic.c_str(), topic.length());
			subscriptions.remove(s);
			return;
		}
	}
}

bool ZmqConnector::handleMessage(std::shared_ptr<zmq::message_t> argMessage) {
	// TODO
	while(!done) {
		if(nullptr != socketSubscriber) {
			zmq::message_t rx_envelope; 
			int result = socketSubscriber->recv(&rx_envelope, ZMQ_NOBLOCK);
			if(result == 0) {
				std::this_thread::sleep_for(std:chrono::milliseconds(10));
				continue;
			}
			zmq::message_t rx_msg; 
			socketSubscriber->recv(&rx_msg, 0);
		}
	}
	return false;
}

}
