#pragma once

#include <string>
#include <thread>
#include <mutex>
#include <queue>

namespace dh {

class ItcTask {

public: 
	virtual	~ItcTask();
	bool ItcTask::pushMessage(char* argMessage);
	virtual bool handleMessage(char* argMessage) = 0;

protected:
	explicit ItcTask::ItcTask(std::string argItcTaskName);
	bool startItcTask();
	bool stopItcTask();
	bool pushMessage(char* argMessage);

private: 
	std::atomic<bool> done; 
	std::unique_ptr<std::thread> workerThread; 
	mutable std::mutex messageQueueMutex;
	std::queue<char*> messageQueue;
	std::condition_variable messageQueuedCondition;
	static int worker(ItcTask argItcTask);
	
};
}

