#include "zmqConnector.hpp"

namespace dh {

ZmqConnector::ZmqConnector() {}
ZmqConnector::~ZmqConnector() {}

int ZmqConnector::initialize() {
	//zmqContext = new zmq::context_t(1);
	//socketPublisher = new zmq::socket_t(*zmqContext, ZMQ_PUB);
	//socketPublisher->connect(sendProtocol);
	//socketSubscriber = new zmq::socket_t(*zmqContext, ZMQ_SUB);
	//socketSubscriber->connect(subscriberToAddr);
	return 0;
}
void ZmqConnector::publish(const MessageCommand& argMsgCmd, const MessageKey& argMsgKey, const std::bitset<SDR>& argPayload) {
	std::lock_guard<std::mutex> mutexLock(sendMutex);
	zmq::message_t message = MessageEncoder::createMessage(argMsgCmd, argMsgKey, argPayload);
	socketPublisher->send(message);
}
void ZmqConnector::publish(const MessageCommand& argMsgCmd, const MessageKey& argMsgKey, const float& argPayload) {
	std::lock_guard<std::mutex> mutexLock(sendMutex);
	zmq::message_t message = MessageEncoder::createMessage(argMsgCmd, argMsgKey, argPayload);
	socketPublisher->send(message); 
}

}
