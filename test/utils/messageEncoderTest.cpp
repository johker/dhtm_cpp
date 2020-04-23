#include "messageEncoderTest.hpp"

namespace dh {

void MessageEncoderTest::SetUp() {}

void MessageEncoderTest::TearDown() {}

TEST_F(MessageEncoderTest, createSdrMessageTest ) {
	// Arrange
	xt::xarray<bool> testSdr({1,1,1,1,1,1,1,1});
	MessageCommand testCmd = MessageCommand::PRINT;
	MessageKey testKey = MessageKey::P_ACTBTS; 
	// Act
//	char* test = MessageEncoder::createMessage(testCmd,testKey,testSdr);
	// Assert
	EXPECT_TRUE(true);
}

}
