#include "messageEncoderTest.hpp"

namespace dh {

void MessageEncoderTest::SetUp() {}

void MessageEncoderTest::TearDown() {}

TEST_F(MessageEncoderTest, createSdrMessageTest) {
	
	// Arrange
	xt::xarray<bool> testSdr({0,1,0,1,0,1,0,1});
	MessageCommand testCmd = MessageCommand::ACK;
	MessageKey testKey = MessageKey::P_ACTBTS;
	std::vector<int> testKeys{-1,0,1,UINT16_MAX};
	
	for(auto& tk : testKeys) {
		testKey = (dh::MessageKey) tk;

		// Act
		printf("Testing key %d\n", testKey);
		zmq::message_t testMsg = MessageEncoder::createMessage(testCmd,testKey,testSdr);
		unsigned char* testMsgData = static_cast<unsigned char*>(testMsg.data());		
		size_t testMsgSize = testMsg.size();
		MessageEncoder::printMessage(testMsg);
		// Assert
		uint32_t createdKey = 
	       		(uint32_t)testMsgData[KEY_OFFSET] << 24 |
			(uint32_t)testMsgData[KEY_OFFSET+1] << 16 |
			(uint32_t)testMsgData[KEY_OFFSET+2] << 8  |
			(uint32_t)testMsgData[KEY_OFFSET+3];
		EXPECT_TRUE(testKey == createdKey);
		
		char c;
		for (size_t i=0; i<(testMsgSize - PAYLOAD_OFFSET);i++) {
			c = testMsgData[PAYLOAD_OFFSET+i];

			bool tb[8] = {};
			for(size_t j = 0; j<8; j++) {
				if(c & (1 << j)){
					tb[j]=true;
				}				
				printf("i= %d, j = %d, msgIdx = %d, tb=%d, sdr=%d\n",i,j,(i*8+j),tb[j],testSdr[i*8+j]);
				//ASSERT_TRUE(testSdr[i*8+j] == tb[j]);
			}

		}
		printf("testKey = %d, createdKey = %d \n", testKey, createdKey);
	
	}
}

}
