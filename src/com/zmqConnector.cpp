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

void ZmqConnector::publish(const ComMessage& argComMessage) {
	zmq::message_t message; 
	if(argComMessage.messageKey > MSG_KEY_DIV) {	
		message = MessageEncoder::createMessage(argComMessage.messageType, argComMessage.messageCommand, argComMessage.messageKey, argComMessage.sdr);
	} else {
		 message = MessageEncoder::createMessage(argComMessage.messageType, argComMessage.messageCommand, argComMessage.messageKey, argComMessage.parameter);
	}
	send(message, argComMessage.messageType);
}

void ZmqConnector::send(zmq::message_t& argMessage, const MessageType& argMsgType) {
	std::lock_guard<std::mutex> mutexLock(sendMutex);
	std::string topic = MessageEncoder::createTopic(argMsgType);
	zmq::message_t rx_topic(topic.length());
	memcpy(rx_topic.data(), topic.c_str(), topic.length());
	socketPublisher->send(rx_topic, zmq::send_flags::sndmore);
	socketPublisher->send(argMessage, zmq::send_flags::none);
}

int ZmqConnector::subscribe(const MessageType& argMsgType, ComHandlerInterface* argComHandler) {
	std::lock_guard<std::mutex> mutexLock(subscriberMutex);
	std::string topic = MessageEncoder::createTopic(argMsgType);
	ZmqSubscriber subscriber; 
	subscriber.subscriptionId = subscriptionId++;
	subscriber.messageType = argMsgType;
	subscriber.comHandler = argComHandler;
	subscriptions.push_back(subscriber);
	socketSubscriber->setsockopt(ZMQ_SUBSCRIBE, topic.c_str(), topic.length());
	return subscriptionId;
}

void ZmqConnector::unsubscribe(const int& argSubscriptionId) {
	std::lock_guard<std::mutex> mutexLock(subscriberMutex);
	for(auto it = subscriptions.begin(); it!= subscriptions.end(); ++it) {
		if((*it).subscriptionId == argSubscriptionId) {
			std::string topic = MessageEncoder::createTopic((*it).messageType);
			socketSubscriber->setsockopt(ZMQ_UNSUBSCRIBE, topic.c_str(), topic.length());
			subscriptions.erase(it);
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
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
				continue;
			}
			zmq::message_t rx_msg; 
			socketSubscriber->recv(&rx_msg, 0);
			//TODO: Parse MessageType
			const unsigned char* msgData = static_cast<unsigned char*>(rx_msg.data()); 
			MessageType rcvMsgType = MessageEncoder::parseMessageType(msgData);
			MessageCommand rcvMsgCmd = MessageEncoder::parseMessageCommand(msgData);
			MessageKey rcvMsgKey = MessageEncoder::parseMessageKey(msgData);

			for(auto& subscriber : subscriptions) {
				if(subscriber.messageType == rcvMsgType) {
					if(rcvMsgKey > MSG_KEY_DIV) {	
						// Message Payload = SDR
						std::bitset<SDR> rcvSdr = MessageEncoder::parseSdr(msgData, rx_msg.size());
						std::shared_ptr<ComMessage> comMessage = std::make_shared<ComMessage>(rcvMsgType, rcvMsgCmd, rcvMsgKey, rcvSdr);
						subscriber.comHandler->handleMessageCallback(comMessage);

					} else {
						// Message Payload = Parameter
						const float rcvParameter = MessageEncoder::parseParameter(msgData);
						std::shared_ptr<ComMessage> comMessage = std::make_shared<ComMessage>(rcvMsgType, rcvMsgCmd, rcvMsgKey, rcvParameter);
						subscriber.comHandler->handleMessageCallback(comMessage);
					}
				}
							
			}
		}
	}
	return false;
}

}
