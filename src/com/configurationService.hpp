#pragma once

#include "comInterface.hpp"


namespace dh {

class ConfigurationService : 	public ItcTask<zmq::message_t>, 
				public ComHandlerInterface 
{

public: 
	ConfigurationService(std::shared_ptr<ComInterface> argComManager); 	
										
	virtual ~ConfigurationService() {};

	int initialize(); 

private:
	ComInterface comManager; 
	std::vector<int> subscriptionHandles;

};
}
