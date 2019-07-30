#pragma once

#include "task.h"

namespace rage {

class ITaskScheduler
{
public:
	//virtual void addTask(Task *task) = 0;
	//virtual void removeTask(Task *task) = 0;
	virtual void schedule(Task *task) = 0;
};

}
