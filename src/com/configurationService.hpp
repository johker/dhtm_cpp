#pragma once

#include "comInterface.hpp"
#include "comHandlerInterface.hpp"


namespace dh {

class ConfigurationService {

public: 
	ConfigurationService(std::shared_ptr<ComInterface> argComInterface) : 	public ItcTask<zmq::message_t>, 
										public ComHandlerInterface;
	virtual ~ConfigurationService() {};

	int initialize(); 

private:
	ComInterface comManager; 
	std::vector<int> subscriptionHandles;

};
}
