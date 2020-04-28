#include "messageEncoder.hpp"

namespace dh {


uint32_t MessageEncoder::uuid = 0;	

MessageEncoder::MessageEncoder() {}
MessageEncoder::~MessageEncoder() {}

zmq::message_t MessageEncoder::createMessage(MessageCommand& argMsgCmd, MessageKey& argMsgKey, const xt::xarray<bool>& argSdr) {	
	size_t payloadSize = argSdr.size() >> 3;
	size_t msgSize = PAYLOAD_OFFSET + payloadSize;
	unsigned char msgData[msgSize];
	zmq::message_t msg(msgSize);

	// ID
	uint32_t id = getUuid();
	msgData[ID_OFFSET] = (id >> 24) & 0xFF;
	msgData[ID_OFFSET+1] = (id >> 16) & 0xFF;
	msgData[ID_OFFSET+2] = (id >> 8) & 0xFF;
	msgData[ID_OFFSET+3] = (id) & 0xFF;

	// Command
	msgData[CMD_OFFSET] = (argMsgCmd >> 24) & 0xFF;
	msgData[CMD_OFFSET+1] = (argMsgCmd >> 16) & 0xFF;
	msgData[CMD_OFFSET+2] = (argMsgCmd >> 8) & 0xFF;
	msgData[CMD_OFFSET+3] = (argMsgCmd) & 0xFF;

	// Key
	msgData[KEY_OFFSET] = (argMsgKey >> 24) & 0xFF;
	msgData[KEY_OFFSET+1] = (argMsgKey >> 16) & 0xFF;
	msgData[KEY_OFFSET+2] = (argMsgKey >> 8) & 0xFF;
	msgData[KEY_OFFSET+3] = (argMsgKey) & 0xFF;

	// Payload
	for(int j = 0; j < payloadSize; j++) {
		for (int i=0; i < 8; ++i) {
			if (argSdr[j*8+i]) {
				msgData[PAYLOAD_OFFSET + j] |= 1 << i;
			}
		}
	}
	memcpy(msg.data(), msgData, msgSize);
	return msg;
}


void MessageEncoder::printMessage(unsigned char* argMsg, size_t& argMsgSize) {
	for(size_t i = 0; i < argMsgSize; i++) {
		std::cout << i << ' ' << std::bitset<8>(argMsg[i]) << '\n';	
	}
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
