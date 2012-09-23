#pragma once

#include "itasklistener.h"

namespace rage {

class ITaskExecutor
{
public:
	virtual void executeTask(Task *task) = 0;
	virtual void runTask(Task *task) = 0;
	virtual void scheduleTask(Task *task) = 0;

	virtual void addExecListener(ITaskListener *listener) = 0;
};

}
