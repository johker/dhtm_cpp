#include "messageEncoder.hpp"

namespace dh {

MessageEncoder::MessageEncoder() {}
MessageEncoder::~MessageEncoder() {}

void MessageEncoder::encode(const char* argMessage) {

}
void MessageEncoder::decode(const char* argMessage) {
	// TODO: 
	// Read SDR Length
	// Read Active bits and write to xarray
	
	char c;
	for (int i = 0; i < 8; ++i) {
		bool is_set = c & (1 << i);
	//	std::out << "Bit " << i << ": " << is_set << '\n';
	}
}
}
