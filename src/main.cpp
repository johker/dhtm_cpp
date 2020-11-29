#include <iostream>
#include <thread>
#include <chrono>
#include "com/zmqConnector.hpp"
#include "com/configurationService.hpp"
#include "com/comInterface.hpp"
#include "utils/logger.hpp"
#include "htm/htmConstants.hpp"


int main(){
	
	// HTM
	size_t numcat = 2;
	size_t encLen = 256;
	size_t actBits = 2;
	size_t phorizon = 10;
	size_t min = 0;
	size_t max = 100;

	std::shared_ptr<dh::ComInterface> comService = std::make_shared<dh::ZmqConnector>();
	comService->initialize();

	
	dh::ConfigurationService configurationService(comService);
	configurationService.initialize();

	DEBUG("DHTM started");

	uint16_t type;
	uint16_t cmd;
	uint16_t key;
	dh::MessageType msgType;
	float value;
	dh::MessageCommand msgCmd;
	dh::MessageKey msgKey;
 
	while (true) {
		std::cout << "Enter msg type:\n";
		std::cin >> type;
		std::cout << "Enter msg command:\n"; 
		std::cin >> cmd;
		std::cout << "Enter msg key:\n";
		std::cin >> key;
		std::cout << "Enter value:\n";
		std::cin >> value;
		msgType = static_cast<dh::MessageType>(type);
		msgCmd = static_cast<dh::MessageCommand>(cmd);
		msgKey = static_cast<dh::MessageKey>(key);
		dh::ComMessage comMessage(msgType,msgCmd,msgKey,value);
		comService->publish(comMessage);
		std::cout << "Message sent.\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	return 0;
}

