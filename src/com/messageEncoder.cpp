#include "messageEncoder.hpp"

namespace dh {


uint16_t MessageEncoder::uuid = 0;	

MessageEncoder::MessageEncoder() {}
MessageEncoder::~MessageEncoder() {}

zmq::message_t MessageEncoder::createMessage(const MessageType& argMsgType, const MessageCommand& argMsgCmd, const MessageKey& argMsgKey, const std::bitset<SDR>& argPayload) {	
	size_t payloadSize = SDR >> 3;
	size_t msgSize = PAYLOAD_OFFSET + payloadSize;
	unsigned char msgData[msgSize] = {};
	zmq::message_t msg(msgSize);

	// ID
	uint16_t id = getUuid();
	msgData[ID_OFFSET] = (id >> 8) & 0xFF;
	msgData[ID_OFFSET+1] = (id) & 0xFF;

	// Type
	msgData[TYPE_OFFSET] = (argMsgType >> 8) & 0xFF;
	msgData[TYPE_OFFSET+1] = (argMsgType) & 0xFF;

	// Command
	msgData[CMD_OFFSET] = (argMsgCmd >> 8) & 0xFF;
	msgData[CMD_OFFSET+1] = (argMsgCmd) & 0xFF;

	// Key
	msgData[KEY_OFFSET] = (argMsgKey >> 8) & 0xFF;
	msgData[KEY_OFFSET+1] = (argMsgKey) & 0xFF;

	// Payload
	for(int i = 0; i < payloadSize; i++) {
		for (int j=0; j < 8; j++) {
			if (argPayload[i*8+j]) {
				msgData[PAYLOAD_OFFSET + i] |= 1 << j;
			}
		}
	}
	memcpy(msg.data(), msgData, msgSize);
	return msg;
}

zmq::message_t MessageEncoder::createMessage(const MessageType& argMsgType, const MessageCommand& argMsgCmd, const MessageKey& argMsgKey, const float& argPayload) {	
	size_t payloadSize = 4;
	size_t msgSize = PAYLOAD_OFFSET + payloadSize;
	unsigned char msgData[msgSize] = {};
	zmq::message_t msg(msgSize);
	
	// ID
	uint16_t id = getUuid();
	msgData[ID_OFFSET] = (id >> 8) & 0xFF;
	msgData[ID_OFFSET+1] = (id) & 0xFF;
							 
	// Type
	msgData[TYPE_OFFSET] = (argMsgType >> 8) & 0xFF;
	msgData[TYPE_OFFSET+1] = (argMsgType) & 0xFF;
							 
	// Command
	msgData[CMD_OFFSET] = (argMsgCmd >> 8) & 0xFF;
	msgData[CMD_OFFSET+1] = (argMsgCmd) & 0xFF;
							 
	// Key
	msgData[KEY_OFFSET] = (argMsgKey >> 8) & 0xFF;
	msgData[KEY_OFFSET+1] = (argMsgKey) & 0xFF;

	// Payload
	std::uint32_t param;
	std::memcpy(&param, &argPayload, sizeof(argPayload));
	msgData[PAYLOAD_OFFSET] = (param >> 24) & 0xFF;
	msgData[PAYLOAD_OFFSET+1] = (param >> 16) & 0xFF;
	msgData[PAYLOAD_OFFSET+2] = (param >> 8) & 0xFF;
	msgData[PAYLOAD_OFFSET+3] = (param) & 0xFF;

	memcpy(msg.data(), msgData, msgSize);
	return msg;
}

std::string createTopic(const MessageType& argMsgType) {
	std::string topic;
	std::stringstream ss;
        ss << std::dec << std::setw(3) << std::setfill('0') << argMsgType;
	topic = ss.str();
	return topic;
}

float MessageEncoder::parseParameter(const unsigned char*& argMsgData) {
	float f;
	auto b0 = (uint8_t)argMsgData[PAYLOAD_OFFSET];
	auto b1 = (uint8_t)argMsgData[PAYLOAD_OFFSET+1];
	auto b2 = (uint8_t)argMsgData[PAYLOAD_OFFSET+2];
	auto b3 = (uint8_t)argMsgData[PAYLOAD_OFFSET+3];
	unsigned char b[] = {b3, b2, b1, b0};
	memcpy(&f, &b, sizeof(f));
	return f;
}

MessageCommand MessageEncoder::parseMessageCommand(const unsigned char*& argMsgData){
	uint16_t msgCmd = 
		(uint16_t)argMsgData[CMD_OFFSET] << 8  |
		(uint16_t)argMsgData[CMD_OFFSET+1];
	return static_cast<MessageCommand>(msgCmd);
}

MessageKey MessageEncoder::parseMessageKey(const unsigned char*& argMsgData){
	uint16_t msgKey = 
		(uint16_t)argMsgData[KEY_OFFSET] << 8  |
		(uint16_t)argMsgData[KEY_OFFSET+1];
	return static_cast<MessageKey>(msgKey);
}

MessageType MessageEncoder::parseMessageType(const unsigned char*& argMsgData){
	uint16_t msgType = 
		(uint16_t)argMsgData[TYPE_OFFSET] << 8  |
		(uint16_t)argMsgData[TYPE_OFFSET+1];
	return static_cast<MessageType>(msgType);
}

uint16_t MessageEncoder::getUuid() {
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
			sdr[i*8+j] = (argMsgData[PAYLOAD_OFFSET+i]>>j) &1;
		}	
	}
	return sdr;
}

}
