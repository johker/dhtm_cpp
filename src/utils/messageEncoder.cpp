#include "messageEncoder.hpp"

namespace dh {


uint32_t MessageEncoder::uuid = 0;	

MessageEncoder::MessageEncoder() {}
MessageEncoder::~MessageEncoder() {}

bool MessageEncoder::createMessage(MessageCommand& argMsgCmd, MessageKey& argMsgKey, const xt::xarray<bool>& argSdr, unsigned char** retMsg, size_t& retMsgSize) {	
	size_t payloadSize = argSdr.size() >> 3;
	retMsgSize = PAYLOAD_OFFSET + payloadSize;
	unsigned char msg[retMsgSize] = {};

	// ID
	uint32_t id = getUuid();
	msg[ID_OFFSET] = (id >> 24) & 0xFF;
	msg[ID_OFFSET+1] = (id >> 16) & 0xFF;
	msg[ID_OFFSET+2] = (id >> 8) & 0xFF;
	msg[ID_OFFSET+3] = (id) & 0xFF;

	// Command
	msg[CMD_OFFSET] = (argMsgCmd >> 8) & 0xFF;
	msg[CMD_OFFSET+1] = (argMsgCmd) & 0xFF;

	// Key
	msg[KEY_OFFSET] = (argMsgKey >> 24) & 0xFF;
	msg[KEY_OFFSET+1] = (argMsgKey >> 16) & 0xFF;
	msg[KEY_OFFSET+2] = (argMsgKey >> 8) & 0xFF;
	msg[KEY_OFFSET+3] = (argMsgKey) & 0xFF;

	// Payload
	for(int j = 0; j < payloadSize; j++) {
		for (int i=0; i < 8; ++i) {
			if (argSdr[j*8+i]) {
				msg[PAYLOAD_OFFSET + j] |= 1 << i;
			}
		}
	}
	*retMsg = &msg[0];
	return false;
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
