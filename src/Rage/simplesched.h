#pragma once

#include "scheduler.h"

#include <queue>

using namespace std;

namespace fprts
{

/////////////////////// Simple Scheduler ////////////////////////////////////////
class SimpleScheduler : public Scheduler
{
protected:
	queue<CFAtom*> ready_cfs; // ready atomic cfs

	MyMutex sched_mutex;

public:
	SimpleScheduler() {}
	~SimpleScheduler() {}

	virtual void Init(UInt thread_num = 1);
	virtual void Add(CFAtom *cf);
	virtual bool ScheduleNext(CFAtom **cf, UInt thread_id = 0);
};

//////////////////////// Single Queue ///////////////////////////////////////////
/*class SingleQueueScheduler : public Scheduler // Scheduler with one shared queue for fragments
{
protected:
	SchedulerQueue sched_queue;

public:
	SingleQueueScheduler(FragmentScope* s) : Scheduler(s) {}
	virtual ~SingleQueueScheduler() {}

	virtual int ScheduleCF(const FragmentId& cf_id); // add ready fragment to exec        
    virtual FragmentId GetNextCF(const UInt& t_id = 0); // get next fragment for execution	

	virtual bool IsEmpty(const UInt& t_id = 0) {return sched_queue.empty();}
};

//////////////////////// Single Queue Prior ///////////////////////////////////////////
class SingleQueuePriorScheduler : public SingleQueueScheduler // Scheduler with one shared queue for fragments with priority check
{
public:
	SingleQueuePriorScheduler(FragmentScope* s) : SingleQueueScheduler(s) {}
	virtual ~SingleQueuePriorScheduler() {}

	virtual int ScheduleCF(const FragmentId& cf_id); // add ready fragment to exec        
};

//////////////////////// Multi Queue ///////////////////////////////////////////
class MultiQueueScheduler : public Scheduler // Scheduler with separate queue for each exec thread
{
protected:
	Map<UInt, SchedulerQueue> sched_queues;
	Map<UInt, UInt> t_load_curr; // curr weight in threads
	Map<UInt, UInt> t_load_done; // weight of all done fragments
	Map<UInt, UInt> cf_exec_now; // weight of cf executing now

	//UInt t_min; // id of thread with min load

protected:
	UInt GetMinLoadQueue(); // get thread with min load

public:
	MultiQueueScheduler(FragmentScope* s) : Scheduler(s) {}
	virtual ~MultiQueueScheduler() {}

	//virtual void Init(const UInt& t_num = 1);
	virtual UInt AddThread(); // register exec thread for scheduler	

	virtual int ScheduleCF(const FragmentId& cf_id) = 0; // add ready fragment to exec        

    virtual FragmentId GetNextCF(const UInt& t_id = 0) = 0; // get next fragment for execution
	virtual void MarkDone(const FragmentId& cf_id, const UInt& t_id = 0) {}

	virtual bool IsEmpty(const UInt& t_id = 0) {return sched_queue[t_id].empty();}
};

//////////////////////// Multi Queue Prior ///////////////////////////////////////////
class MultiQueuePriorScheduler : public MultiQueueScheduler // Scheduler with separate queue for each exec thread
{
public:
	MultiQueuePriorScheduler(FragmentScope* s) : MultiQueueScheduler(s) {}
	virtual ~MultiQueuePriorScheduler() {}

	virtual int ScheduleCF(const FragmentId& cf_id); // add ready fragment to exec        
};

//////////////////////// Branch ///////////////////////////////////////////
class BranchScheduler : public MultiQueueScheduler // Scheduler with branch detection
{
protected:	
	Map<UInt, IdSet> recommended;
	bool strict_mode;

protected:
	void RecommendAll(CompFragment* f, const UInt& t_id); // recommend all children of f
	bool IsRecommended(const FragmentId& cf_id, UInt& t_id);

public:
	BranchScheduler(RunTimeSystem* parent, const bool& strict = false) : MultiQueueScheduler(parent), strict_mode(strict) {}
	virtual ~BranchScheduler() {}	

	virtual int Schedule(CompFragment* f); // add ready fragment to exec        
    //virtual CompFragment* GetNext(const UInt& t_id = 0); // get next fragment for execution
	//virtual void MarkDone(CompFragment* f, const UInt& t_id = 0);       
};

//////////////////////// Hyper Graph ///////////////////////////////////////////
class HyperGraphScheduler : public BranchScheduler // Scheduler with branch detection
{
public:
	HyperGraphScheduler(RunTimeSystem* parent) : BranchScheduler(parent) {}
	virtual ~HyperGraphScheduler() {}	

	virtual void Init(const UInt& t_num = 1);

	virtual int Schedule(CompFragment* f); // add ready fragment to exec        
};

class HyperGraphPriorScheduler : public HyperGraphScheduler // Scheduler with branch detection
{
public:
	HyperGraphPriorScheduler(RunTimeSystem* parent) : HyperGraphScheduler(parent) {}
	virtual ~HyperGraphPriorScheduler() {}	

	virtual int Schedule(CompFragment* f); // add ready fragment to exec        
};*/

}
