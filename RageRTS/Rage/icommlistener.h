#pragma once

#include "task.h"
#include "dataobject.h"

namespace rage {

class ICommListener // listener for incoming data
{
public:	
	virtual void onTaskRecv(Task *task) = 0;
	virtual void onDataRecv(DataObject *object) = 0;
	//virtual void onTaskDone(TaskId task);
};

}
