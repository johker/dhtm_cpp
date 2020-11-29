
#include "configurationService.hpp"

#include "../../dhtm_msg/cpp/messageConstants.hpp"
#include "../utils/logger.hpp"

namespace dh {

ConfigurationService::ConfigurationService(std::shared_ptr<ComInterface> argComService)
	: ItcTask("ConfigurationService"),
	comService(argComService)
{}
ConfigurationService::~ConfigurationService() {}

int ConfigurationService::initialize() {
	subscriptionHandles.push_back(comService->subscribe(MessageType::CONFIGURATION, this));
	return 0;
}

bool ConfigurationService::handleMessageCallback(std::shared_ptr<ComMessage> argComMessage) {
	pushMessage(argComMessage);
	return false;
}
bool ConfigurationService::handleMessage(std::shared_ptr<ComMessage> argMessage) {
	//TODO: Do sth with message

	std::stringstream ss;
        ss << "Message received: T=" << argMessage->messageType << "C=" << argMessage->messageCommand << "K=" << argMessage->messageKey << "\n";
	DEBUG(ss.str());
	return false;
}
}
