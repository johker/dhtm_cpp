#include "messageEncoder.hpp"

namespace dh {


uint32_t MessageEncoder::uuid = 0;	

MessageEncoder::MessageEncoder() {}
MessageEncoder::~MessageEncoder() {}

zmq::message_t MessageEncoder::createMessage(const MessageCommand& argMsgCmd, const MessageKey& argMsgKey, const std::bitset<SDR>& argSdr) {	
	size_t payloadSize = SDR >> 3;
	size_t msgSize = PAYLOAD_OFFSET + payloadSize;
	unsigned char msgData[msgSize] = {};
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
	for(int i = 0; i < payloadSize; i++) {
		for (int j=0; j < 8; j++) {
			if (argSdr[i*8+j]) {
				msgData[PAYLOAD_OFFSET + i] |= 1 << j;
			}
		}
	}
	memcpy(msg.data(), msgData, msgSize);
	return msg;
}

MessageCommand MessageEncoder::parseMessageCommand(const unsigned char*& argMsgData){
	uint32_t msgCmd = 
		(uint32_t)argMsgData[CMD_OFFSET] << 24 |
		(uint32_t)argMsgData[CMD_OFFSET+1] << 16 |
		(uint32_t)argMsgData[CMD_OFFSET+2] << 8  |
		(uint32_t)argMsgData[CMD_OFFSET+3];
	return static_cast<MessageCommand>(msgCmd);
}

MessageKey MessageEncoder::parseMessageKey(const unsigned char*& argMsgData){
	uint32_t msgKey = 
		(uint32_t)argMsgData[KEY_OFFSET] << 24 |
		(uint32_t)argMsgData[KEY_OFFSET+1] << 16 |
		(uint32_t)argMsgData[KEY_OFFSET+2] << 8  |
		(uint32_t)argMsgData[KEY_OFFSET+3];
	return static_cast<MessageKey>(msgKey);
}

//std::vector<bool> MessageEncoder::parseSdr(const unsigned char*& argMsgData, const size_t& argMsgSize) {
//	int sdrByteSize = argMsgSize - PAYLOAD_OFFSET;
//	std::vector<bool> sdr(sdrByteSize>>3);
//	for (size_t i=0; i<sdrByteSize; i++) {
//		for(size_t j = 0; j<8; j++) {
//			sdr.push_back(((argMsgData[PAYLOAD_OFFSET+i]>>j) &1));
//		}	
//	}
//	return sdr;
//}

uint32_t MessageEncoder::getUuid() {
	return uuid++;
}

std::bitset<SDR> MessageEncoder::parseSdr(const unsigned char*& argMsgData, const size_t& argMsgSize) {
	size_t sdrByteSize = argMsgSize - PAYLOAD_OFFSET;
	std::bitset<SDR> sdr;
	size_t sdrIdx = 0;
	for (size_t i=0; i<sdrByteSize; i++) {
		for(size_t j = 0; j<8; j++) {
			if(sdrIdx++ > SDR-1) {
				ERROR("Msg exceeds max SDR size: " + std::to_string(sdrByteSize>>3) + " > " + std::to_string(SDR));
				return sdr;
			}
			sdr[sdrIdx] = (argMsgData[PAYLOAD_OFFSET+i]>>j) &1;
		}	
	}
	return sdr;
}



}
