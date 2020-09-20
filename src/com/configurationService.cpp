
#include "configurationService.hpp"

#include "../../dhtm_msg/cpp/messageConstants.hpp"
#include "../utils/logger.hpp"

namespace dh {

ConfigurationService::ConfigurationService(std::shared_ptr<ComInterface> argComManager)
	: ItcTask("ConfigurationService"),
	comManager(argComManager)
{
}

ConfigurationService::initialize() {
	subscriptionHandles.push_back(comManager->subscribe(MessageType::CONFIGURATION));
}

bool handleMessageCallback(std::shared_ptr<ComMessage> argComMessage) {
	pushMessage(argComMessage);
	return false;
}
bool handleMessage(std::shared_ptr<ComMessage> argMessage) {
	//TODO: Do sth with message

	DEBUG(sprintf("Message received: T=%d, C=%d, K=%d")); 	
}

