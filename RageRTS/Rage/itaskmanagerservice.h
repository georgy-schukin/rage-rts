#pragma once

#include "itaskmanager.h"

namespace rage {

class ITaskManagerService : public ITaskManager
{
public:
	virtual void start() = 0;
	virtual void stop() = 0;
	virtual bool isEmpty() = 0;
};

}