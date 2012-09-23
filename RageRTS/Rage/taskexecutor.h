#pragma once

#include "itaskexecutorservice.h"
#include "itaskscheduler.h"
#include "execthreadpool.h"
#include "codeargs.h"
#include <list>
#include <queue>
#include <boost/scoped_ptr.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

using namespace std;

namespace rage {

class AtomicTask;

class TaskExecutor : public ITaskExecutorService
{
protected:
	list<ITaskListener*> listeners;
	queue<Task*> newTasks;
	list<Task*> pendingTasks;
	ITaskScheduler *taskScheduler;

	boost::scoped_ptr<ExecThreadPool> execThreadPool;

	boost::thread schedThread;
	boost::mutex schedMutex;
	boost::condition_variable schedCond;

	volatile bool isWorking;

protected:
	bool isTaskReady(Task *task);
	void schedFunc();

	bool startTask(Task *task); // call to start execing task
	void finishTask(Task *task); // call when task is done

public:
	TaskExecutor() {}
	~TaskExecutor() {}

	void executeTask(Task *task); // plan execution of task
	void runTask(Task *task); // execute ready task
	void scheduleTask(Task *task);

	void addExecListener(ITaskListener *listener) {
		listeners.push_back(listener);
	}

	void setTaskScheduler(ITaskScheduler *taskScheduler) {
		this->taskScheduler = taskScheduler;
	}

	void start(int threadsNum);
	void stop();
};

}
