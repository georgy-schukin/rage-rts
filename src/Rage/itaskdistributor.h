#pragma once

#include "task.h"

namespace rage {

class ITaskDistributor
{
public:
	virtual void distributeTask(Task *task) = 0;
};

}
