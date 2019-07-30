#pragma once

#include "itasklistener.h"
#include "dataobject.h"

namespace rage {

class ITaskManager
{
public:
	virtual void addTask(Task *task) = 0;
	virtual void addTasks(list<Task*>& tasks) = 0;
	virtual void removeTask(Task *task) = 0;
	virtual void addData(DataObject *data) = 0;
	virtual void addDatas(list<DataObject*>& datas) = 0;
	virtual void removeData(DataObject *data) = 0;
	//virtual void decDepend(Task *task, int cnt); 

	virtual void addManageListener(ITaskListener *listener) = 0;
};

}
