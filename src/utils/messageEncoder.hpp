#pragma once

namespace dh {

class MessageEncoder {

public: 
	MessageEncoder();
	virtual ~MessageEncoder();

	static void encode(const char* argMessage);
	static void decode(const char* argMessage);
};
}
