#include "zmqConnector.hpp"

namespace dh {

ZmqConnector::ZmqConnector() {}
ZmqConnector::~ZmqConnector() {}

int ZmqConnector::initialize() {
	return 0;
}
void ZmqConnector::publish(const char* argData) {
	size_t size = strlen(argData); // Assuming your char* is NULL-terminated
	zmq::message_t message(size);
	std::memcpy (message.data(), argData, size);
	socketPublisher->send(message);
}
}
