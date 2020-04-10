#include <iostream>
#include <string>
#include <xtensor/xarray.hpp>
#include <chrono>
#include <thread>
#include <panel.h>
#include <ncursesw/ncurses.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "../tiny_htm/tiny_htm/tiny_htm.hpp"

#include "utils/itcMessage.hpp"
#include "utils/itcQueue.hpp"
#include "utils/logger.hpp"



int main(){
	
	// HTM 
	size_t numcat = 2;
	size_t encLen = 256;
	size_t actBits = 2;
	size_t phorizon = 10; 
	size_t min = 0; 
	size_t max = 100; 

	th::ScalarEncoder scalarEncoder(min, max, encLen, actBits);
	th::CategoryEncoder categoryEncoder(numcat, encLen);
	th::TemporalMemory tm({numcat*4}, 6);
	
	DEBUG("Terminal started");

	return 0;
}

