
#include "configurationService.hpp"

#include "../../dhtm_msg/cpp/messageConstants.hpp"

namespace dh {

ConfigurationService::ConfigurationService(std::shared_ptr<ComInterface> argComManager) 
	: ItcTask("ConfigurationService"), 
	comManager(argComManager)
							
{
}

ConfigurationService::initialize() {
	subscriptionHandles.push_back(comManager->subscribe(MessageType::CONFIGURATION));
}

