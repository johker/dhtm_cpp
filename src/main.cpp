#include <iostream>

#include "com/zmqConnector.hpp"
#include "com/configurationService.hpp"
#include "com/comInterface.hpp"
#include "utils/logger.hpp"



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

	std::string input;
	std::cout << "Enter messages:";

	while (true) {
		std::getline(std::cin,input);
	}

	return 0;

}

