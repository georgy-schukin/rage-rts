#include "statcollector.h"

namespace fprts {
}

/*void StatCollector::Add(const StatInfo &s, bool own)
{
	MyMutex::LockObject lock(stat_mutex);
	if(own) done--;
	
	curr.tasks_num++; // num of tasks
	curr.mem_load += s.mem; // set amount of comsumed mem	
	curr.tasks_comp_weight += s.comp; // comp weight of tasks
}

void StatCollector::Add(const vector<StatInfo> &s, bool own)
{
	MyMutex::LockObject lock(stat_mutex);
	if(own) done -= s.size();
	
	curr.tasks_num += s.size(); // num of tasks

	for(vector<StatInfo>::const_iterator it = s.begin();it != s.end();it++)
	{
		curr.mem_load += (*it).mem; // set amount of comsumed mem	
		curr.tasks_comp_weight += (*it).comp; // comp weight of tasks
	}
}

void StatCollector::Release(const StatInfo &s, bool finished)
{
	MyMutex::LockObject lock(stat_mutex);
	if(finished) done++;
	
	curr.tasks_num--; // num of tasks
	curr.mem_load -= s.mem; // set amount of comsumed mem	
	curr.tasks_comp_weight -= s.comp; // comp weight of tasks
}

void StatCollector::Release(const vector<StatInfo> &s, bool finished)
{
	MyMutex::LockObject lock(stat_mutex);
	if(finished) done += s.size();
	
	curr.tasks_num -= s.size(); // num of tasks

	for(vector<StatInfo>::const_iterator it = s.begin();it != s.end();it++)
	{
		curr.mem_load -= (*it).mem; // set amount of comsumed mem	
		curr.tasks_comp_weight -= (*it).comp; // comp weight of tasks
	}
}

void StatCollector::GetData(StatData &res)
{
	MyMutex::LockObject lock(stat_mutex);
	res = curr;
}

void StatCollector::GetDone(int &res)
{
	MyMutex::LockObject lock(stat_mutex);
	res = done;
}

/*void StatCollector::Init(const UInt& t_num)
{
	curr_load.resize(t_num);
}

UInt StatCollector::GetCurrTotalLoad() const
{
	UInt load = 0;
	for(vector<UInt>::const_iterator it = curr_load.begin();it != curr_load.end();it++) 
	{
		load += *it;
	}
return load;
}*/
 