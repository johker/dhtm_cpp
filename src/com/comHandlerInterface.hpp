#pragma once 

namespace dh {

class ComHandlerInterface {

public:
	ComHandlerInterface(); 
	
	virtual ComHandlerInterface();

	virtual void handleMessageCallback(const MessageType& argMsgType, const MessageCommand& argMsgCmd, const MessageKey& argMsgKey, const std::bitset<SDR>& argPayload) = 0; 
	virtual void handleMessageCallback(const MessageType& argMsgType, const MessageCommand& argMsgCmd, const MessageKey& argMsgKey, const float& argPayload) = 0; 
	


}

}
