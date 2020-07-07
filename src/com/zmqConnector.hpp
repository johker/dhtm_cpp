#pragma once

#include <thread>
#include <mutex>
#include <queue>
#include <zmq.hpp>

#include "comInterface.hpp"

namespace dh {

class ZmqConnector : public ComInterface {

public: 
	ZmqConnector();
	virtual ~ZmqConnector();

	virtual	int initialize();
	virtual	void publish(const char* argData);
		

private: 
	std::mutex sendMutex;
	zmq::context_t* zmqContext;
	zmq::socket_t* socketPublisher;
	zmq::socket_t* socketSubscriber;
	std::string rcvProtocol;
	std::string sendProtocol;

};
}
