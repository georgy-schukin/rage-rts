#pragma once

#include "itaskexecutor.h"

namespace rage {

class ITaskExecutorService : public ITaskExecutor
{
public:
	virtual void start(int threadsNum) = 0;
	virtual void stop() = 0;
};

}