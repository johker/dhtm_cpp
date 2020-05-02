#include "messageEncoderTest.hpp"

namespace dh {

void MessageEncoderTest::SetUp() {}

void MessageEncoderTest::TearDown() {}

TEST_F(MessageEncoderTest, createSdrMessageTest) {
	
	// Arrange
	MessageCommand testCmd;
	MessageKey testKey;
	std::vector<xt::xarray<bool>> testSdrs;
	xt::xarray<bool> sdr1({0,1,0,1,1,1,0,1});			 	// 1 byte
	xt::xarray<bool> sdr2({0,1,0,1,});					// 0 bytes
	xt::xarray<bool> sdr3({0,1,0,1,1,0,0,1,0,1,1,1,0,0,1,1});		// 2 bytes
	testSdrs.push_back(sdr1);
	testSdrs.push_back(sdr2);
	testSdrs.push_back(sdr3);
	std::vector<int> testKeys{-1,0,1,UINT16_MAX};
	std::vector<int> testCmds{-1,0,1,UINT16_MAX};
	
	for(auto& tk : testKeys) {
		for(auto& tc: testCmds) {
			for(auto& testSdr: testSdrs) {

				testCmd = (dh::MessageCommand) tc;
				testKey = (dh::MessageKey) tk;

				// Act
				zmq::message_t testMsg = MessageEncoder::createMessage(testCmd,testKey,testSdr);
				unsigned char* testMsgData = static_cast<unsigned char*>(testMsg.data());		
				size_t testMsgSize = testMsg.size();

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

				EXPECT_TRUE(testMsgSize - PAYLOAD_OFFSET == testSdr.size()>>3);
				for (size_t i=0; i<(testMsgSize - PAYLOAD_OFFSET);i++) {
					for(size_t j = 0; j<8; j++) {
						EXPECT_TRUE(testSdr[i*8+j] == ((testMsgData[PAYLOAD_OFFSET+i]>>j) &1));
						}	
				}
			}	
		}
	}
}
TEST_F(MessageEncoderTest, parseMessageCommandTest) {
	// Arrange
	MessageCommand testCmd = MessageCommand::ACK; 
	MessageKey emptyKey; 
	xt::xarray<bool> emptySdr; 
	zmq::message_t testMsg = MessageEncoder::createMessage(testCmd, emptyKey, emptySdr); 
	unsigned char* testMsgData = static_cast<unsigned char*>(testMsg.data()); 
	// Act
	MessageCommand retCmd = MessageEncoder::parseMessageCommand(testMsgData); 
	// Assert
	EXPECT_TRUE(retCmd == testCmd);
}

}
