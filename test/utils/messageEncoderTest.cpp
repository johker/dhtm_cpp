#include "messageEncoderTest.hpp"

namespace dh {

void MessageEncoderTest::SetUp() {}

void MessageEncoderTest::TearDown() {}

TEST_F(MessageEncoderTest, createSdrMessageTest) {
	
	// Arrange
	xt::xarray<bool> testSdr({0,1,0,1,1,1,0,1,1,1,1,1,1,1,1});
	MessageCommand testCmd = MessageCommand::ACK;
	MessageKey testKey = MessageKey::P_ACTBTS;
	std::vector<int> testKeys{-1,0,1,UINT16_MAX};
	std::vector<int> testCmds{-1,0,1,UINT16_MAX};
	
	for(auto& tk : testKeys) {
		for(auto& tc: testCmds) {
			testCmd = (dh::MessageCommand) tc;
			testKey = (dh::MessageKey) tk;

			// Act
			printf("Testing cmd=%d, key=%d, ", testCmd, testKey);
			printf("Payload=");
			for(auto& b : testSdr) {
				printf("%d", b);
			}
			printf("\n");

			zmq::message_t testMsg = MessageEncoder::createMessage(testCmd,testKey,testSdr);
			unsigned char* testMsgData = static_cast<unsigned char*>(testMsg.data());		
			size_t testMsgSize = testMsg.size();
			MessageEncoder::printMessage(testMsg);
			// Assert
			uint32_t createdCmd = 
				(uint32_t)testMsgData[CMD_OFFSET] << 24 |
				(uint32_t)testMsgData[CMD_OFFSET+1] << 16 |
				(uint32_t)testMsgData[CMD_OFFSET+2] << 8  |
				(uint32_t)testMsgData[CMD_OFFSET+3];
			EXPECT_TRUE(testCmd == createdCmd);

			uint32_t createdKey = 
				(uint32_t)testMsgData[KEY_OFFSET] << 24 |
				(uint32_t)testMsgData[KEY_OFFSET+1] << 16 |
				(uint32_t)testMsgData[KEY_OFFSET+2] << 8  |
				(uint32_t)testMsgData[KEY_OFFSET+3];
			EXPECT_TRUE(testKey == createdKey);
			
			for (size_t i=0; i<(testMsgSize - PAYLOAD_OFFSET);i++) {
				for(size_t j = 0; j<8; j++) {
					//printf("sdr = %d, msg = %d\n",testSdr[i*8+j], (testMsgData[PAYLOAD_OFFSET+i]>>j)&1);
					ASSERT_TRUE(testSdr[i*8+j] == ((testMsgData[PAYLOAD_OFFSET+i]>>j) &1));
					}				
			}

	
		}
	}
}

}
