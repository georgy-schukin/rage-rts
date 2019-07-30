#pragma once

#include "task.h"
#include "itaskexecutor.h"
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <vector>
#include <queue>

using namespace std;

namespace rage {

class ExecThreadPool // threads for running atomic tasks
{
protected:
	boost::thread_group execThreads;
	unsigned int threadsNum;
	bool isWorking;

	boost::ptr_vector<boost::mutex> threadMutex;
	vector<queue<Task*> > threadQueue;

	ITaskExecutor *taskExecutor;

protected:
	void init(); 
	void runFunc(int threadNum);

public:
	ExecThreadPool(ITaskExecutor *executor, unsigned int size) : taskExecutor(executor), threadsNum(size) {
		init();
	}
	~ExecThreadPool() {}
	
	void start();
	void stop();

	void run(Task *task, int threadNum = 0);
};

}
