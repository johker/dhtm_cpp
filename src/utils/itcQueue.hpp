#pragma once
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>

namespace dh {

class ItcQueue {
public:
	ItcQueue();
	virtual ~ItcQueue();
	bool pushMessage(char* argMessage);
	bool wait(char* argResult);
	bool get(char* argResult);
	
private:
	mutable std::mutex queueMutex;
	std::condition_variable condition;
	std::queue<char*> queue;
	std::atomic<bool> done;
};
}
