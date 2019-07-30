#include "taskexecutor.h"
#include "tasks.h"
#include "code.h"
#include <boost/foreach.hpp>
#include "taskprocessor.h"
#include "exception.h"
#include <iostream>

using namespace std;

namespace rage {

void TaskExecutor::start(int threadsNum) {
	isWorking = true;

	schedThread = boost::thread(boost::bind(&TaskExecutor::schedFunc, this)); // start sched thread

	execThreadPool.reset(new ExecThreadPool(this, threadsNum)); // create pool of exec threads
	execThreadPool->start(); // start exec threads
}

void TaskExecutor::stop() {
	isWorking = false;
	schedCond.notify_one();
	schedThread.join();
	execThreadPool->stop();	
}

void TaskExecutor::executeTask(Task *task) {
	boost::unique_lock<boost::mutex> lock(schedMutex);
	newTasks.push(task);
	schedCond.notify_one();
}

void TaskExecutor::runTask(Task *task) {
	try {
		if(task->getType() == Task::ATOMIC) {		
			if(startTask(task)) {
				finishTask(task);
			}
		}
	}
	catch (Exception e) {
		cerr << "Error: " << e.getMessage() << endl;
	}
}

bool TaskExecutor::startTask(Task *task) {			
	task->setState(Task::RUNNING);

	BOOST_FOREACH(ITaskListener *l, listeners) 
		l->onTaskStart(task);

	list<Task*> newTasks;
	list<DataObject*> newDatas;

	TaskProcessor::processTask(task, newTasks, newDatas); // task exec

	if(newDatas.size() > 0) {
		BOOST_FOREACH(ITaskListener *l, listeners) 
			l->onDatasSpawn(newDatas);
	}
	if(newTasks.size() > 0) { // new tasks were spawned
		BOOST_FOREACH(ITaskListener *l, listeners) 
			l->onTasksSpawn(newTasks);
		return false;
	} else  // no new tasks
		return true;	
return false;
}

void TaskExecutor::finishTask(Task *task) {
	task->setState(Task::DONE);
	BOOST_FOREACH(Task *t, task->getDepTasks()) { // for each task that depends from finished task
		if(t->changeDependencyCount(-1) == 0) { // if all deps are satisfied
			if(t->getState() == Task::RUNNING) { // this task is running already
				finishTask(t); // finish it too
			} else if(isTaskReady(t)) { // task is not runnng, we can run it now
				BOOST_FOREACH(ITaskListener *l, listeners) 
					l->onTaskReady(t);	
			}
		}
	}
	BOOST_FOREACH(ITaskListener *l, listeners) 
		l->onTaskDone(task);	
}

void TaskExecutor::scheduleTask(Task *task) {
	execThreadPool->run(task); // SIMPLE SCHED
}

bool TaskExecutor::isTaskReady(Task *task) {
	if(task->getDependencyCount() > 0) return false; // there are unsatisfied dependencies
	TaskEnvironment *env = task->getEnvironment();
	BOOST_FOREACH(const string& name, task->dataReqs) { // check for data ready
		if(!env->dataExists(name)) return false;
	}
	BOOST_FOREACH(const string& name, task->valueReqs) { // check for param ready
		if(!env->valueExists(name)) return false;
	}
return true;
}

void TaskExecutor::schedFunc() {
	bool allIsDone = false;
	while(isWorking || !allIsDone) {
		boost::unique_lock<boost::mutex> lock(schedMutex);
		if(!newTasks.empty()) {	
			Task *task = newTasks.front();
			newTasks.pop();
			lock.unlock(); // release queue lock 
			if(isTaskReady(task)) { // if task is ready
				BOOST_FOREACH(ITaskListener *l, listeners) 
					l->onTaskReady(task);
			} else {
				//pendingTasks.push_back(task); // add to pending
			}
		} else if(isWorking) {
			schedCond.wait(lock);
		}
		allIsDone = newTasks.empty();
	}
}

}
