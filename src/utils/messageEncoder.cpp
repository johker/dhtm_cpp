#include "messageEncoder.hpp"

namespace dh {


uint32_t MessageEncoder::uuid = 0;	

MessageEncoder::MessageEncoder() {}
MessageEncoder::~MessageEncoder() {}

zmq::message_t MessageEncoder::createMessage(const MessageCommand& argMsgCmd, const MessageKey& argMsgKey, const xt::xarray<bool>& argSdr) {	
	size_t payloadSize = argSdr.size() >> 3;
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

MessageCommand MessageEncoder::parseMessageCommand(const zmq::message_t& argMsg){
	//TODO Implementation
	MessageCommand msgCmd = MessageCommand::ACK;
	return msgCmd;
}



void MessageEncoder::printMessage(zmq::message_t& argMsg) {
	unsigned char* msgData = static_cast<unsigned char*>(argMsg.data());		
	size_t msgSize = argMsg.size();

	uint32_t msgId = 
		(uint32_t)msgData[ID_OFFSET] << 24 |
		(uint32_t)msgData[ID_OFFSET+1] << 16 |
		(uint32_t)msgData[ID_OFFSET+2] << 8  |
		(uint32_t)msgData[ID_OFFSET+3];
	
	uint32_t msgCmd = 
		(uint32_t)msgData[CMD_OFFSET] << 24 |
		(uint32_t)msgData[CMD_OFFSET+1] << 16 |
		(uint32_t)msgData[CMD_OFFSET+2] << 8  |
		(uint32_t)msgData[CMD_OFFSET+3];

	uint32_t msgKey = 
	       	(uint32_t)msgData[KEY_OFFSET] << 24 |
		(uint32_t)msgData[KEY_OFFSET+1] << 16 |
		(uint32_t)msgData[KEY_OFFSET+2] << 8  |
		(uint32_t)msgData[KEY_OFFSET+3];

	printf("--------------------------- \n");
	printf(">>   MSG ID : %d\n", msgId);
	printf(">>      CMD : %d\n", msgCmd);
	printf(">>      KEY : %d\n", msgKey);
	size_t payloadSize = msgSize - PAYLOAD_OFFSET;
	printf(">>  PAYLOAD : %d B\n", payloadSize );

	char c;
	for (size_t i=0; i<payloadSize;i++) {
		printf(">>      %3d : ", (i+1));
	 	c = msgData[PAYLOAD_OFFSET+i];
		for(size_t j = 0; j<8; j++) {
			printf("%d", (msgData[PAYLOAD_OFFSET+i]>>j)&1); 		
		}
		printf("\n");
	}
	printf("--------------------------- \n");
}

// MessageEncoder::decode(const char* argMessage) {
//	// TODO: 
//	// Read SDR Length
//	// Read Active bits and write to xarray
//	
//	char c;
//	for (int i = 0; i < 8; ++i) {
//		bool is_set = c & (1 << i);
//	//	std::out << "Bit " << i << ": " << is_set << '\n';
//	}
//}
uint32_t MessageEncoder::getUuid() {
	return uuid++;
}
}
