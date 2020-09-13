#include "messageEncoderTest.hpp"

namespace dh {

void MessageEncoderTest::SetUp() {}

void MessageEncoderTest::TearDown() {}

TEST_F(MessageEncoderTest, createSdrMessageTest) {
	
	// Arrange
	MessageType testType;
	MessageCommand testCmd;
	MessageKey testKey;
	std::vector<std::bitset<SDR>> testSdrs;
	std::bitset<SDR> sdr1(std::string("01011101"));			 	// 1 byte
	std::bitset<SDR> sdr2(std::string("0101"));				// 0 bytes
	std::bitset<SDR> sdr3(std::string("0101100101110011"));			// 2 bytes
	testSdrs.push_back(sdr1);
	testSdrs.push_back(sdr2);
	testSdrs.push_back(sdr3);
	std::vector<int> testTypes{-1,0,1,UINT16_MAX};
	std::vector<int> testKeys{-1,0,1,UINT16_MAX};
	std::vector<int> testCmds{-1,0,1,UINT16_MAX};
	
	for(auto& tt : testTypes) {
		for(auto& tk : testKeys) {
			for(auto& tc: testCmds) {
				for(auto& testSdr: testSdrs) {

					testType = (dh::MessageType) tt;
					testCmd = (dh::MessageCommand) tc;
					testKey = (dh::MessageKey) tk;

					// Act
					zmq::message_t testMsg = MessageEncoder::createMessage(testType,testCmd,testKey,testSdr);
					unsigned char* testMsgData = static_cast<unsigned char*>(testMsg.data());		
					size_t testMsgSize = testMsg.size();

					// Assert
					uint16_t createdCmd = 
						(uint16_t)testMsgData[CMD_OFFSET] << 8  |
						(uint16_t)testMsgData[CMD_OFFSET+1];
					EXPECT_EQ(testCmd,createdCmd);

					uint16_t createdType = 
						(uint16_t)testMsgData[TYPE_OFFSET] << 8  |
						(uint16_t)testMsgData[TYPE_OFFSET+1];
					EXPECT_EQ(testCmd,createdCmd);

					uint16_t createdKey = 
						(uint16_t)testMsgData[KEY_OFFSET] << 8  |
						(uint16_t)testMsgData[KEY_OFFSET+1];
					EXPECT_EQ(testKey,createdKey);

					EXPECT_TRUE(testMsgSize - PAYLOAD_OFFSET == SDR >> 3);
					for (size_t i=0; i < 2; i++) {
						for(size_t j = 0; j<8; j++) {
							EXPECT_EQ(testSdr[i*8+j],((testMsgData[PAYLOAD_OFFSET+i]>>j) &1));
						}	
					}
				}	
			}
		}
	}
}

TEST_F(MessageEncoderTest, parseMessageCommandTest) {
	// Arrange
	MessageType testType = MessageType::UNDEFINED; 
	MessageCommand testCmd = MessageCommand::ACK; 
	MessageKey emptyKey; 
	std::bitset<SDR> emptySdr; 
	zmq::message_t testMsg = MessageEncoder::createMessage(testType, testCmd, emptyKey, emptySdr); 
	const unsigned char* testMsgData = static_cast<unsigned char*>(testMsg.data()); 
	// Act
	MessageCommand retCmd = MessageEncoder::parseMessageCommand(testMsgData); 
	// Assert
	EXPECT_EQ(retCmd, testCmd);
}

TEST_F(MessageEncoderTest, parseMessageKeyTest) {
	// Arrange
	MessageType testType = MessageType::UNDEFINED; 
	MessageCommand testCmd = MessageCommand::RESERVED; 
	MessageKey testKey = MessageKey::P_SDRLEN; 
	std::bitset<SDR> emptySdr; 
	zmq::message_t testMsg = MessageEncoder::createMessage(testType, testCmd, testKey, emptySdr); 
	const unsigned char* testMsgData = static_cast<unsigned char*>(testMsg.data()); 
	// Act
	MessageKey retKey = MessageEncoder::parseMessageKey(testMsgData); 
	// Assert
	EXPECT_EQ(retKey,testKey);
}

TEST_F(MessageEncoderTest, parseMessageTypeTest) {
	// Arrange
	MessageType testType = MessageType::DATA; 
	MessageCommand testCmd = MessageCommand::RESERVED; 
	MessageKey testKey = MessageKey::P_SDRLEN; 
	std::bitset<SDR> emptySdr; 
	zmq::message_t testMsg = MessageEncoder::createMessage(testType, testCmd, testKey, emptySdr); 
	const unsigned char* testMsgData = static_cast<unsigned char*>(testMsg.data()); 
	// Act
	MessageType retType = MessageEncoder::parseMessageType(testMsgData); 
	// Assert
	EXPECT_EQ(retType,testType);
}

TEST_F(MessageEncoderTest, parseSdrTest) {
	// Arrange
	MessageType emptyType; 
	MessageCommand emptyCmd; 
	MessageKey emptyKey; 
	std::vector<std::bitset<SDR>> testSdrs;
	std::bitset<SDR> sdr1(std::string("01011101"));			 	// 1 byte
	std::bitset<SDR> sdr2(std::string("0101"));				// 0 bytes
	std::bitset<SDR> sdr3(std::string("0101100101110011"));			// 2 bytes
	std::bitset<SDR> sdr4;
	sdr4[234] = 1;
	testSdrs.push_back(sdr1);
	testSdrs.push_back(sdr2);
	testSdrs.push_back(sdr3);
	testSdrs.push_back(sdr4);
	std::bitset<SDR> retSdr;

	for(auto& testSdr : testSdrs) {
		zmq::message_t testMsg = MessageEncoder::createMessage(emptyType, emptyCmd, emptyKey, testSdr); 
		const unsigned char* testMsgData = static_cast<unsigned char*>(testMsg.data()); 
		size_t testMsgSize = testMsg.size();
		for (size_t i=0; i < 2; i++) {
			for(size_t j = 0; j<8; j++) {
				EXPECT_EQ(testSdr[i*8+j],((testMsgData[PAYLOAD_OFFSET+i]>>j) &1));
			}	
		}
		// Act
		retSdr = MessageEncoder::parseSdr(testMsgData, testMsgSize); 
		// Assert
		size_t retSdrSize = retSdr.size();
		EXPECT_TRUE(retSdrSize == testSdr.size());
		for(size_t i = 0; i<retSdrSize; i++) {
			EXPECT_EQ(retSdr[i],testSdr[i]);
		}
	}
}

TEST_F(MessageEncoderTest, parseParameterTest) {
	// Arrange
	MessageType emptyType; 
	MessageCommand emptyCmd;
	MessageKey emptyKey; 
	std::vector<float> testParams; 
	testParams.push_back(3.45f);
	testParams.push_back(-1223.35);
	float retParam; 

	for(auto& testParam : testParams) {
		zmq::message_t testMsg = MessageEncoder::createMessage(emptyType, emptyCmd, emptyKey, testParam);
		const unsigned char* testMsgData = static_cast<unsigned char*>(testMsg.data()); 
		size_t testMsgSize = testMsg.size();
		// Act 
		retParam = MessageEncoder::parseParameter(testMsgData);
	       	// Assert
		EXPECT_EQ(testParam, retParam); 	
	}











}

}
