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
void ZmqConnector::publish(const char* argData) {
	size_t size = strlen(argData); // Assuming your char* is NULL-terminated
	zmq::message_t message(size);
	std::memcpy (message.data(), argData, size);
	socketPublisher->send(message);
}
}
