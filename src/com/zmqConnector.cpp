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
	std::lock_guard<std::mutex> mutexLock(sendMutex);
	std::string topic = MessageEncoder::createTopic(argMsgType);
	zmq::message_t rx_topic(topic.length());
	memcpy(rx_topic.data(), topic.c_str(), topic.length());
	zmq::message_t message = MessageEncoder::createMessage(argMsgType, argMsgCmd, argMsgKey, argPayload);
	socketPublisher->send(rx_topic, zmq::send_flags::sndmore);
	socketPublisher->send(message, zmq::send_flags::none);
}
void ZmqConnector::publish(const MessageType& argMsgType, const MessageCommand& argMsgCmd, const MessageKey& argMsgKey, const float& argPayload) {
	std::lock_guard<std::mutex> mutexLock(sendMutex);
	zmq::message_t message = MessageEncoder::createMessage(argMsgType, argMsgCmd, argMsgKey, argPayload);
	socketPublisher->send(message, zmq::send_flags::none);
}
bool ZmqConnector::handleMessage(std::shared_ptr<zmq::message_t> argMessage) {
	// TODO
	return false;
}

}
