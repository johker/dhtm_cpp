#include "itcQueue.hpp"

namespace dh {

ItcQueue::ItcQueue() {
	done = false;
}

virtual ItcQueue::~ItcQueue() {
	done = true;
	condition.notify_all();
}
bool ItcQueue::pushMessage(char* argMessage) {
	if(done) {
		return false;
	}
	std::lock_guard<std::mutex> guard(queueMutex);
	queue.push(argMessage);
	condition.notify_one();
	return true;
}
bool ItcQueue::wait(char* argResult) {
	std::unique_lock<decltype(queueMutex)> lock(queueMutex);
	char* message;
	while(!done) {
		if(queue.size()) {
			message = queue.front(); 
			queue.pop();
			argResult = message; 
			return true;
		}
		condition.wait(lock);
	}
	return false;
}
bool ItcQueue::get(char* argResult) {
	std::unique_lock<decltype(queueMutex)> lock(queueMutex);
	char* message;
	if(queue.size()) {
		message = queue.front();
		queue.pop();
		*argResult = message;
		return true;
	}
	return false;
}
}
