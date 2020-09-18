#include <iostream>

#include "com/zmqConnector.hpp"
#include "utils/logger.hpp"



int main(){
	
	// HTM 
	size_t numcat = 2;
	size_t encLen = 256;
	size_t actBits = 2;
	size_t phorizon = 10; 
	size_t min = 0; 
	size_t max = 100; 

	dh::ZmqConnector zmqConnector; 
	zmqConnector.initialize();
		
	
	DEBUG("DHTM started");

	return 0;
}

