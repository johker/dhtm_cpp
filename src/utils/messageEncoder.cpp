#include "messageEncoder.hpp"

namespace dh {


uint32_t MessageEncoder::uuid = 0;	

MessageEncoder::MessageEncoder() {}
MessageEncoder::~MessageEncoder() {}

char* MessageEncoder::createMessage(MessageCommand& argMsgCmd, MessageKey& argMsgKey, const xt::xarray<bool>& argSdr) {	
	size_t payloadSize = argSdr.size() >> 3;
	char bytes[PAYLOAD_OFFSET + payloadSize] = {};
	// ID
	uint32_t id = getUuid();
	bytes[ID_OFFSET] = (id >> 24) & 0xFF;
	bytes[ID_OFFSET+1] = (id >> 16) & 0xFF;
	bytes[ID_OFFSET+2] = (id >> 8) & 0xFF;
	bytes[ID_OFFSET+3] = (id) & 0xFF;

	// Command
	bytes[CMD_OFFSET] = (argMsgCmd >> 8) & 0xFF;
	bytes[CMD_OFFSET+1] = (argMsgCmd) & 0xFF;

	// Key
	bytes[KEY_OFFSET] = (argMsgKey >> 24) & 0xFF;
	bytes[KEY_OFFSET+1] = (argMsgKey >> 16) & 0xFF;
	bytes[KEY_OFFSET+2] = (argMsgKey >> 8) & 0xFF;
	bytes[KEY_OFFSET+3] = (argMsgKey) & 0xFF;

	// Size 
	bytes[SIZE_OFFSET] = (payloadSize >> 8) & 0xFF;
	bytes[SIZE_OFFSET+1] = (payloadSize) & 0xFF;

	// Payload
	for(int j = 0; j < payloadSize; j++) {
		for (int i=0; i < 8; ++i) {
			if (argSdr[j*8+i]) {
				bytes[PAYLOAD_OFFSET + j] |= 1 << i;
			}
		}
	}
	char* msgptr = &bytes[0];
	return msgptr;
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
uint32_t MessageEncoder::getUuid() {
	return uuid++;
}
}
