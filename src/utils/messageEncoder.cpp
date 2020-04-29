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
	printf(">>  PAYLOAD : \n");

	char c;
	for (size_t i=0; i<(msgSize - PAYLOAD_OFFSET);i++) {
		printf(">>      %3d : ", (i+1));
	 	c = msgData[PAYLOAD_OFFSET+i];
		bool tb[8] = {};
		for(size_t j = 0; j<8; j++) {
			if(c & (1 << j)){
				tb[j]=true;
			}				
			printf("%d", tb[j]); 		
		}
		printf("\n");
	}
	printf("--------------------------- \n");
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
