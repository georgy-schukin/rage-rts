#pragma once

#include "itaskmanagerservice.h"
//#include "itaskexecutor.h"
#include "taskenvironment.h"

#include <list>
#include <map>
#include <queue>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/ptr_container/ptr_map.hpp>

using namespace std;

namespace rage {

class Procedure;

class TaskManager : public ITaskManagerService
{
protected:		
	boost::ptr_map<Task*, TaskEnvironment> taskEnvironments; // envs for tasks
	boost::ptr_map<Task*, Task> taskStorage; // task storage
	list<ITaskListener*> listeners;	
	//ITaskExecutor *taskExecutor;

	queue<Task*> newTasks; // newly added tasks			

	boost::thread manageThread;
	boost::mutex queueMutex, envMutex;
	boost::condition_variable queueCond;

	volatile bool isWorking;

protected:
	void manageFunc();
	void processNewTask(Task *task);	

public:
	TaskManager() {}
	~TaskManager() {}

	void addTask(Task *task);
	void addTasks(list<Task*>& tasks);
	void removeTask(Task *task);
	void addData(DataObject *data);
	void addDatas(list<DataObject*>& datas);
	void removeData(DataObject *data);
	//void decDepend(Task *task, int cnt);

	void start();
	void stop();

	bool isEmpty() {
		return taskStorage.empty();
	}

	void addManageListener(ITaskListener *listener) {
		listeners.push_back(listener);
	}	
};

}
 