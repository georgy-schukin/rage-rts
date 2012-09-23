#pragma once

#include "rtstypes.h"

#include <vector>
//#include <boost/thread.hpp>

namespace fprts {

class StatCollector // collector of various info about system
{
/*public:
	struct StatInfo
	{
		int mem; // mem weight
		int comp; // comp weight

		StatInfo(int m, int c) : mem(m), comp(c) {}
		~StatInfo() {}
	};
	struct StatData
	{
		int mem_load; // amount of consumed memory
		int max_mem_load; // max memory 
	
		int tasks_num; // num of ready tasks
		int tasks_mem_weight; // data weight
		int tasks_comp_weight; // potential comp weight

		StatData() : tasks_num(0), mem_load(0), max_mem_load(0), tasks_mem_weight(0), tasks_comp_weight(0) {}
		~StatData() {}
	};

protected:
	StatData curr;

	int done; // num of done tasks
	
	//boost::mutex stat_mutex;

public:
	StatCollector() : done(0) {}
	~StatCollector() {}

	void Add(const StatInfo &s, bool own = true); 
	void Add(const vector<StatInfo> &s, bool own = true); 

	void Release(const StatInfo &s, bool finished = true); 
	void Release(const vector<StatInfo> &s, bool finished = true); 

	void GetData(StatData &res);
	void GetDone(int &res);

	/*void Init(const UInt& t_num);
	void SetCurrLoad(const UInt& t_id, const UInt& load = 1) {curr_load[t_id] = load;}
	void IncCurrLoad(const UInt& t_id, const UInt& load = 1) {curr_load[t_id] += load;}
	void DecCurrLoad(const UInt& t_id, const UInt& load = 1) {curr_load[t_id] -= load;}
	UInt GetCurrLoad(const UInt& t_id) const {return curr_load[t_id];}
	UInt GetCurrTotalLoad() const;*/
};

}