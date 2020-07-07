#pragma once

#include <gtest/gtest.h>

#include "../../src/com/messageEncoder.hpp"

namespace dh {

class MessageEncoderTest : public testing::Test {

public:
	virtual void SetUp() override;
	virtual void TearDown() override;
};

}
