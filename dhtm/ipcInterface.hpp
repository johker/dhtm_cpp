#pragma once

namespace dh {

class IpcInterface {

public: 
	IpcInterface() {};
	virtual ~ZmqConnector() {};

	virtual int initialize() = 0;
	
	virtual void publish(char* argMessage);
	
};
}
