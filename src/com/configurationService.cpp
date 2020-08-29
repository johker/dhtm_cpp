
#include "configurationService.hpp"

#include "../../dhtm_msg/cpp/messageConstants.hpp"

namespace dh {

ConfigurationService::ConfigurationService() : ItcTask("ConfigurationService") {
}

ConfigurationService::initialize() {
	subscriptionHandles.push_back(comManager->subscribe(MessageType::CONFIGURATION));
}

