#pragma once

#include "task.h"
#include <list>

using namespace std;

namespace rage {

class DataObject;

class ITaskListener
{
public:		
	virtual void onTaskStart(Task *task) = 0;
	virtual void onTaskDone(Task *task) = 0;	
	virtual void onTasksSpawn(list<Task*>& tasks) = 0;
	virtual void onDatasSpawn(list<DataObject*>& datas) = 0;

	virtual void onTaskAdded(Task *task) = 0;	
	virtual void onTaskReady(Task *task) = 0;	
	virtual void onTaskDeleted(Task *task) = 0;
	virtual void onTaskMigrated(Task *task) = 0;
};

}
