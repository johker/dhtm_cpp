#include "itcTask.hpp"

namespace dh {

ItcTask::~ItcTask() {
	stopItcTask();
}
explicit ItcTask::ItcTask(std::string argItcTaskName){
		
}
bool startItcTask() {
	done = false; 
	std::lock_guard<std::mutex> guard(messageQueueMutex);
	workerThread = new std::thread(ItcTask::worker, this);
	std::this_thread::sleep_for(std::chrono::milliseconds(5));
	return true;
}
bool stopItcTask() {
	if(!workerThread) {
		return true;
	}
	done = true;
	messageQueuedCondition.notify_one();
	workerThread->join();
	workerThread = nullptr;
	std::unique_lock<std::mutex> lock(messageQueueMutex);
	while(messageQueue.size()) 
	{
		messageQueue.pop(); 
	}
	return true;
}
bool ItcTask::pushMessage(char* argMessage) {
	//TODO Prevent message overflow / diagnostics
	messageQueue.push(argMessage);
	messageQueuedCondition.notify_one();
	return true;
}
static int worker(ItcTask argItcTask) {
	do {
		{
			std::unique_lock<std::mutex> lock(argItcTask->messageQueueMutex);
			if(argItcTask->messageQueue.size() == 0) {
				messageQueuedCondition.wait(lock);
			}
		}
		char* message = nullptr;
		{
			std::unique_lock<std::mutex> lock(argItcTask->messageQueueMutex);
			if(argItcTask->messageQueue.size() > 0) {
				message = argItcTask->messageQueue.front();
				argItcTask->messageQueue.pop();

			}
		}

		if(message != nullptr) {
			argItcTask->handleMessage(message);
		}

	} while (!argItcTask->done);	

	{
		std::unique_lock<std::mutex> lock(argItcTask->messageQueueMutex); 
		argItcTask->messageQueue = std::queue<char*>();
	}
	return 0;
}
}
