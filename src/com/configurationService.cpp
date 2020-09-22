
#include "configurationService.hpp"

#include "../../dhtm_msg/cpp/messageConstants.hpp"
#include "../utils/logger.hpp"

namespace dh {

ConfigurationService::ConfigurationService(std::shared_ptr<ComInterface> argComManager)
	: ItcTask("ConfigurationService"),
	comManager(argComManager)
{}
ConfigurationService::~ConfigurationService() {}

ConfigurationService::initialize() {
	subscriptionHandles.push_back(comService->subscribe(MessageType::CONFIGURATION));
}

bool ConfigurationService::handleMessageCallback(std::shared_ptr<ComMessage> argComMessage) {
	pushMessage(argComMessage);
	return false;
}
bool ConfigurationService::handleMessage(std::shared_ptr<ComMessage> argMessage) {
	//TODO: Do sth with message

	DEBUG(sprintf("Message received: T=%d, C=%d, K=%d")); 	
	return false;
}

