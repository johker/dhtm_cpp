#include <string>
#include <zmq.hpp>

int main()
{
	printf("0mq broker started\n");
	zmq::context_t context_1(1);
	zmq::context_t context_2(1);

	const char* publishConnection = "tcp://*:5555";  // Sending messages to Subrcibers
	const char* subcribeConnection = "tcp://*:6000"; // Receiving messages from Publishers

	zmq::socket_t socketPublish(context_1, ZMQ_PUB);
	socketPublish.bind(publishConnection);

	zmq::socket_t sockSubscribe(context_2, ZMQ_SUB);
	sockSubscribe.bind(subcribeConnection);
	sockSubscribe.setsockopt(ZMQ_SUBSCRIBE, "", 0);

	printf("0mq broker ready\n");
	zmq::proxy(static_cast<void*>(sockSubscribe), static_cast
			<void*>(socketPublish), nullptr);

	printf("0mq broker terminated\n");

	return 0;
}

