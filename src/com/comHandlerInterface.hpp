#pragma once 

#include "../../dhtm_msg/cpp/messageConstants.hpp"
#include "comInterface.hpp"

namespace dh {

class ComHandlerInterface {

public:
	ComHandlerInterface(); 
	
	virtual ~ComHandlerInterface();

	virtual void handleMessageCallback(const ComMessage& argComMessage) = 0; 

};

}
