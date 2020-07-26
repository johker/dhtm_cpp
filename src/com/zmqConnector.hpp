#pragma once


#include <thread>
#include <mutex>
#include <queue>
#include <zmq.hpp>

#include "comInterface.hpp"
#include "messageEncoder.hpp"
#include "../utils/itcTask.hpp"


namespace dh {

class ZmqConnector : public ComInterface, public ItcTask<zmq::message_t> {

public: 
	ZmqConnector();
	ZmqConnector(std::string argSendProtocol, std::string argRcvProtocol);
	virtual ~ZmqConnector();

	virtual	int initialize();
	virtual	void publish(const MessageType& argMsgType, const MessageCommand& argMsgCmd, const MessageKey& argMsgKey, const std::bitset<SDR>& argPayload);
	virtual	void publish(const MessageType& argMsgType, const MessageCommand& argMsgCmd, const MessageKey& argMsgKey, const float& argPayload);
		
protected: 
	virtual bool handleMessage(std::shared_ptr<zmq::message_t> argMessage); 


private: 
	std::mutex sendMutex;
	zmq::context_t* zmqContext;
	zmq::socket_t* socketPublisher;
	zmq::socket_t* socketSubscriber;
	std::string recvProtocol;
	std::string sendProtocol;

};
}
