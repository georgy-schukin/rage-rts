#pragma once

#include "rtstypes.h"
#include "fragmentgraph.h"

#include <map>
using namespace std;

namespace fprts {

class Scheduler // class to plan execution of ready fragments
{
public:
	typedef map<int, list<FragmentId> > SchedulePlan;
	enum Type
	{
		SIMPLE = 0
	};
public:
	virtual void Schedule(const FragmentGraph &graph, const FragmentIdSet &ready, Scheduler::SchedulePlan &plan) = 0;
};

class SimpleScheduler : public Scheduler
{
public:
	SimpleScheduler() {}
	~SimpleScheduler() {}

	virtual void Schedule(const FragmentGraph &graph, const FragmentIdSet &ready, Scheduler::SchedulePlan &plan);
};

}
