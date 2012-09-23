#include "scheduler.h"

namespace fprts {

void SimpleScheduler::Schedule(const FragmentGraph &graph, const FragmentIdSet &ready, Scheduler::SchedulePlan &plan) { // simple sched - assign all ready on one thread
	plan[0].insert(plan[0].end(), ready.begin(), ready.end());
}

/*void ExecQueue::PushWithPrior(CompFragment* f)
{
	ExecQueue::iterator it = begin();
	while((it != end()) && ((*it)->priority > f->priority)) it++;
	insert(it, f);
}

/////////////////////////// Single Queue ///////////////////////////////
int SingleQueueScheduler::ScheduleCF(const FragmentId& cf_id) // add ready fragment to exec
{
	sched_queue.Push(cf_id);
return 0;
}

FragmentId SingleQueueScheduler::GetNextCF(const UInt& t_id) // get next fragment for execution
{
	if(!sched_queue.empty())
	{
		FragmentId cf_id = sched_queue.front();
		exec_queue.Pop();
		return cf_id;
	}
return 0;
}

/////////////////////////// Single Queue Prior ///////////////////////////////
int SingleQueuePriorScheduler::Schedule(CompFragment* f) // add ready fragment to exec
{
	exec_queue.PushWithPrior(f);
return 0;
}

/////////////////////////// Multi Queue ///////////////////////////////
void MultiQueueScheduler::Init(const UInt& t_num)
{
	for(UInt i = 0;i < t_num;i++) 
	{
		t_load_curr[i] = 0;
		t_load_done[i] = 0;
	}	
}

UInt MultiQueueScheduler::GetMinLoadQueue()
{
	Map<UInt, UInt>::iterator it = t_load_curr.begin();
	UInt min = it->first;
	it++;
	for(;it != t_load_curr.end();it++) // search queue with min weight
	{
		if(it->second < t_load_curr[min]) min = it->first;
	}
return min;
}

int MultiQueueScheduler::Schedule(CompFragment *f)
{
	UInt t_min = GetMinLoadQueue();
	exec_queue[t_min].Push(f);	
	t_load_curr[t_min] += f->weight;
return 0;
}

CompFragment* MultiQueueScheduler::GetNext(const UInt& t_id) // get next fragment for execution
{	
	if(!exec_queue[t_id].empty())
	{
		CompFragment* f = exec_queue[t_id].front();
		exec_queue[t_id].Pop();
		return f;
	}
return 0;
}

void MultiQueueScheduler::MarkDone(CompFragment* f, const UInt& t_id) // get next fragment for execution
{
	t_load_done[t_id] += f->weight;	
	t_load_curr[t_id] -= f->weight;
}

/////////////////////////// Multi Queue Prior ///////////////////////////////
int MultiQueuePriorScheduler::Schedule(CompFragment *f)
{
	UInt t_min = GetMinLoadQueue();
	exec_queue[t_min].PushWithPrior(f);	
	t_load_curr[t_min] += f->weight;
return 0;
}

/////////////////////////// Branch ////////////////////////////////
void BranchScheduler::RecommendAll(CompFragment* f, const UInt& t_id)
{
	recommended[t_id].insert(f->connected_cfs.begin(), f->connected_cfs.end());
}

bool BranchScheduler::IsRecommended(const FragmentId& cf_id, UInt& t_id)
{	
	for(Map<UInt, IdSet>::const_iterator it = recommended.begin();it != recommended.end();it++)
	{
		if(it->second.find(cf_id) != it->second.end()) // find among recommended
		{
			t_id = it->first; // find thread
			return true;
		}		
	}
return false;
}

int BranchScheduler::Schedule(CompFragment *f)
{
	UInt t_id;
	if(strict_mode) // look for recommended queue first
	{		
		if(!IsRecommended(f->GetDescr()->GetId(), t_id)) // if not recommended - use min weight queue
		{
			t_id = GetMinLoadQueue();
		}
	}
	else // balance between weight and recommendation
	{
		if(!IsRecommended(f->GetDescr()->GetId(), t_id)) // if not recommended - use min weight queue
		{
			t_id = GetMinLoadQueue();
		}
		else
		{
			UInt t_min = GetMinLoadQueue();
			if(t_id != t_min)
			{
				if(float(t_load_curr[t_id])/float(t_load_curr[t_min] + 1e-5) > 1.5) // load of recommended queue is too big
				{
					t_id = t_min; // change to min loaded queue
				}
			}
		}
	}

	exec_queue[t_id].Push(f);
	RecommendAll(f, t_id); // add recommendation
	t_load_curr[t_id] += f->weight;	
return 0;
}

/////////////////////////// Hyper Graph ////////////////////////////////
void HyperGraphScheduler::Init(const UInt& t_num)
{
	BranchScheduler::Init(t_num);
	
	PatohHyperGraphMCDistributor d;
	DistributionPlan cf_plan;
	    IdSet cfs;
	    ((FPRTS*)fprts)->GetCurrCfs(cfs);
	d.Distribute((FPRTS*)fprts, t_num, cfs, cf_plan); // distribute between threads

	for(DistributionPlan::const_iterator it = cf_plan.begin();it != cf_plan.end();it++)
	{
		recommended[it->second].insert(it->first);
		//cout << "Recommend cf " << it->first << " for exec thread " << it->second << endl;
	}
}

int HyperGraphScheduler::Schedule(CompFragment *f)
{
	UInt t_id;
	if(!IsRecommended(f->GetDescr()->GetId(), t_id))
	{
		t_id = GetMinLoadQueue();
	}
	//cout << "Add cf " << f->GetDescr()->GetId() << " in " << t_id << endl;
	exec_queue[t_id].Push(f);	
	t_load_curr[t_id] += f->weight;	
return 0;
}

/////////////////////////// Hyper Graph Prior ////////////////////////////////
int HyperGraphPriorScheduler::Schedule(CompFragment *f)
{
	UInt t_id;
	if(!IsRecommended(f->GetDescr()->GetId(), t_id))
	{
		t_id = GetMinLoadQueue();
	}
	//cout << "Add cf " << f->GetDescr()->GetId() << " in " << t_id << endl;
	exec_queue[t_id].PushWithPrior(f);	
	t_load_curr[t_id] += f->weight;	
return 0;
}*/

}
