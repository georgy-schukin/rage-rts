#pragma once 

#include "task.h"
#include "codevertex.h"
#include "taskenvironment.h"

namespace rage {

class AtomicTask : public Task
{
public:
	AtomicTask() {}	
	AtomicTask(CodeVertex *src) : Task(src) {}
	AtomicTask(Task *p, CodeVertex *src) : Task(p, src) {}
	AtomicTask(Task *p, CodeVertex *src, TaskEnvironment *env) : Task(p, src, env) {}
	~AtomicTask() {}

	Task::Type getType() const {
		return Task::ATOMIC;
	}
};

}
