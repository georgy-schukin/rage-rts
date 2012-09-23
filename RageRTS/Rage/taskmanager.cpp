#include "taskmanager.h"	
#include "exception.h"
#include "code.h"
#include <boost/foreach.hpp>

namespace rage {

void TaskManager::addTask(Task *task) {
	boost::unique_lock<boost::mutex> lock(queueMutex);
	newTasks.push(task); // add to queue to process
	queueCond.notify_one();
}

void TaskManager::addTasks(list<Task*>& tasks) {
	boost::unique_lock<boost::mutex> lock(queueMutex);
	BOOST_FOREACH(Task *task, tasks) { // for each new task		
		newTasks.push(task); // add to queue to process
	}
	queueCond.notify_one();
}

void TaskManager::removeTask(Task *task) {
	boost::unique_lock<boost::mutex> lock(queueMutex);
	taskEnvironments.erase(task);
	taskStorage.erase(task); // destroy task	
}

void TaskManager::addData(DataObject *data) {
	boost::unique_lock<boost::mutex> lock(envMutex);
	data->getEnvironment()->addData(data->getName(), data);
}

void TaskManager::addDatas(list<DataObject*>& datas) {
	boost::unique_lock<boost::mutex> lock(envMutex);
	BOOST_FOREACH(DataObject *data, datas) {
		data->getEnvironment()->addData(data->getName(), data);
	}
}

void TaskManager::removeData(DataObject *data) {
	boost::unique_lock<boost::mutex> lock(envMutex);	
	data->getEnvironment()->removeData(string(data->getName()));
}

void TaskManager::start() {
	isWorking = true;
	manageThread = boost::thread(boost::bind(&TaskManager::manageFunc, this)); // start manage thread
}

void TaskManager::stop() {
	isWorking = false;
	queueCond.notify_one();
	manageThread.join();
}

void TaskManager::manageFunc() {
	bool allIsDone = false;
	while(isWorking || !allIsDone) {				
		boost::unique_lock<boost::mutex> lock(queueMutex);
		if(!newTasks.empty()) {			
			Task *task = newTasks.front();			
			processNewTask(task); // add task to storage, etc
			BOOST_FOREACH(ITaskListener *l, listeners) {
				l->onTaskAdded(task);	// inform about new task		
			}
			newTasks.pop();
		}
		else if(isWorking) {
			queueCond.wait(lock);
		}
		allIsDone = newTasks.empty() && taskStorage.empty();
	}
}

void TaskManager::processNewTask(Task *task) {	
	taskStorage.insert(task, task); // put task to storage	

	CodeVertex *v = task->getSource();
	if(v->getType() == CodeVertex::COMP) {
		if(((CompVertex*)v)->getCompType() == CompVertex::BLOCK) { // it's block
			task->setEnvironment(new TaskEnvironment(task)); // create new env for block
			if(task->getParent()) { // copy data from parent env
				task->getParent()->getEnvironment()->copyAllTo(task->getEnvironment());				
			}
		}
	}

	if(!task->getEnvironment()) { // task without env
		if(!task->getParent()) { // task without parent
			task->setEnvironment(new TaskEnvironment(task)); // create brand new env
		} else {
			task->setEnvironment(task->getParent()->getEnvironment()); // link to parent env
		}
	}
		

	Task *src = task->getEnvironment()->getParent(); // get env's parent
	if(taskEnvironments.find(src) == taskEnvironments.end()) { // detect new env
		taskEnvironments.insert(src, task->getEnvironment()); // add env
	}	

	task->dataReqs = v->getDataReqs();
	task->valueReqs = v->getValueReqs();
}

}
