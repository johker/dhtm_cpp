#include "messageEncoderTest.hpp"

namespace dh {

void MessageEncoderTest::SetUp() {}

void MessageEncoderTest::TearDown() {}

TEST_F(MessageEncoderTest, createSdrMessageTest ) {
	
	// Arrange
	xt::xarray<bool> testSdr({1,1,1,1,1,1,1,1});
	MessageCommand testCmd = MessageCommand::ACK;
	MessageKey testKey = MessageKey::P_ACTBTS;
	std::vector<int> testKeys{-1,0,1000,UINT16_MAX};
	
	// Act
	for(auto& tk : testKeys) {
		testKey = (dh::MessageKey) tk;
		printf("Testing key %d\n", testKey);
		unsigned char* testMsg = nullptr;
		size_t testMsgSize = 0;
		MessageEncoder::createMessage(testCmd,testKey,testSdr,&testMsg,testMsgSize);
		
		uint32_t createdKey = 
	       		(uint32_t)testMsg[KEY_OFFSET] << 24 |
			(uint32_t)testMsg[KEY_OFFSET+1] << 16 |
			(uint32_t)testMsg[KEY_OFFSET+2] << 8  |
			(uint32_t)testMsg[KEY_OFFSET+3];

		printf("testKey = %d, createdKey = %d \n", testKey, createdKey);
	
		// Assert
		// EXPECT_EQ(testKey, createdKey);
		EXPECT_TRUE(testKey == createdKey);
	}
}

}
