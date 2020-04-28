#include "messageEncoderTest.hpp"

namespace dh {

void MessageEncoderTest::SetUp() {}

void MessageEncoderTest::TearDown() {}

TEST_F(MessageEncoderTest, createSdrMessageTest) {
	
	// Arrange
	xt::xarray<bool> testSdr({0,1,0,1,0,1,1,1});
	MessageCommand testCmd = MessageCommand::ACK;
	MessageKey testKey = MessageKey::P_ACTBTS;
	std::vector<int> testKeys{UINT16_MAX};
	
	// Act
	for(auto& tk : testKeys) {
		testKey = (dh::MessageKey) tk;
		printf("Testing key %d\n", testKey);
		zmq::message_t testMsg = MessageEncoder::createMessage(testCmd,testKey,testSdr);
		
		//uint32_t createdKey = 
	       	//	(uint32_t)testMsg.data()[KEY_OFFSET] << 24 |
		//	(uint32_t)testMsg.data()[KEY_OFFSET+1] << 16 |
		//	(uint32_t)testMsg.data()[KEY_OFFSET+2] << 8  |
		//	(uint32_t)testMsg.data()[KEY_OFFSET+3];
		//
		//unsigned char c = testMsg.data()[PAYLOAD_OFFSET];
		//bool tb[8] = {};
		//for(size_t j = 0; j<8; j++) {
		//	if(c & (1 << j)){
		//		tb[j]=true;
		//	}				
		//	printf("tb[%d] = %d\n", j, tb[j]); 		
		//}
		////MessageEncoder::printMessage(testMsg, testMsgSize);
		//printf("testKey = %d, createdKey = %d \n", testKey, createdKey);
	
		//// Assert
		//// EXPECT_EQ(testKey, createdKey);
		//EXPECT_TRUE(testKey == createdKey);
	}
}

TEST_F(MessageEncoderTest, printMessageTest) {
	size_t testMsgSize = 1;
	unsigned char testMsg[testMsgSize+1] = {};
	for(int i=0; i<8; i++) {
		testMsg[0] |= 1 << i;
	}
	testMsg[testMsgSize-1] = '\0'; 	
	std::bitset<8> x(testMsg[0]);
	std::cout << x << '\n';
	//	MessageEncoder::printMessage(&testMsg);
}
}
