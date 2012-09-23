#include "execthreadpool.h"
#include <boost/bind.hpp>

namespace rage {

void ExecThreadPool::init() {
	for(unsigned int i = 0;i < threadsNum;i++) {
		threadMutex.push_back(new boost::mutex());
		threadQueue.push_back(queue<Task*>());
	}
}

void ExecThreadPool::start() {
	isWorking = true;
	for(unsigned int i = 0;i < threadsNum;i++) { 
		execThreads.create_thread(boost::bind(&ExecThreadPool::runFunc, this, i)); // start threads
	}
}

void ExecThreadPool::stop() {
	isWorking = false;
	execThreads.join_all(); // wait for all exec threads to stop
}

void ExecThreadPool::run(Task *task, int threadNum) {
	boost::unique_lock<boost::mutex> lock(threadMutex[threadNum]);
	threadQueue[threadNum].push(task); // add to thread queue
}

void ExecThreadPool::runFunc(int threadNum) {
	boost::mutex& mutex = threadMutex[threadNum];
	queue<Task*>& queue = threadQueue[threadNum];

	while(isWorking) {		
		Task *task = 0;
		mutex.lock();				
			if(!queue.empty()) {
				task = queue.front(); // get task from thread queue
				queue.pop();
			}
		mutex.unlock();				
		if(task) {
			taskExecutor->runTask(task); // run task
		} else {
			boost::this_thread::sleep(boost::posix_time::millisec(100)); // sleep
		}
	}
}

}
