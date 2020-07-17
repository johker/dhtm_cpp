#pragma once

#include <atomic>
#include <condition_variable>
#include <string>
#include <thread>
#include <mutex>
#include <queue>

namespace dh {

template <class T>
class ItcTask {

public: 
	virtual ~ItcTask() {
		stopItcTask();
	}
	bool pushMessage(std::shared_ptr<T> argMessage) {
		//TODO Prevent message overflow / diagnostics
		messageQueue.push(argMessage);
		messageQueuedCondition.notify_one();
		return true;
	}

protected:
	explicit ItcTask(std::string argItcTaskName){

	}
	virtual bool handleMessage(std::shared_ptr<T> argMessage) = 0;
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

private: 
	static int worker(ItcTask* argItcTask) {
		do {
			{
				std::unique_lock<std::mutex> lock(argItcTask->messageQueueMutex);
				if(argItcTask->messageQueue.size() == 0) {
					argItcTask->messageQueuedCondition.wait(lock);
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
			argItcTask->messageQueue = std::queue<std::shared_ptr<T>>();
		}
		return 0;
	}
	std::atomic<bool> done; 
	std::unique_ptr<std::thread> workerThread; 
	mutable std::mutex messageQueueMutex;
	std::queue<std::shared_ptr<T>> messageQueue;
	std::condition_variable messageQueuedCondition;
};
}

