#pragma once

#include <thread>
#include <mutex>
#include <queue>
#include <zmq.hpp>

#include "comInterface.hpp"
#include "messageEncoder.hpp"
#include "../utils/itcTask.hpp"


namespace dh {

class ZmqConnector : public ComInterface {

public: 
	ZmqConnector();
	virtual ~ZmqConnector();

	virtual	int initialize();
	virtual	void publish(const MessageCommand& argMsgCmd, const MessageKey& argMsgKey, const std::bitset<SDR>& argPayload);
	virtual	void publish(const MessageCommand& argMsgCmd, const MessageKey& argMsgKey, const float& argPayload);
		

private: 
	std::mutex sendMutex;
	zmq::context_t* zmqContext;
	zmq::socket_t* socketPublisher;
	zmq::socket_t* socketSubscriber;
	std::string rcvProtocol;
	std::string sendProtocol;

};
}
