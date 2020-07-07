#pragma once

namespace dh {

class ComInterface {

public: 
	ComInterface() {};
	virtual ~ComInterface() {};

	virtual int initialize() = 0;
	
	virtual void publish(const char* argMessage) = 0;

	virtual int subscribe() = 0;

	virtual void unsubscrbe() = 0;
	
};
}
