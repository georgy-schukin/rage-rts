#pragma once

#include "compfragment.h"
#include <queue>
#include <list>

using namespace std;

namespace fprts {

class TaskPool
{
public:
	enum Type 
	{
		SIMPLE = 0
	};
public:
	virtual void Init(int t_num) = 0;
	virtual void Add(int t_num, const list<CompFragment*> &cfs) = 0;
	virtual bool Get(int t_num, list<CompFragment*> &cfs, int max_sz = 1) = 0;
};

class SimpleTaskPool : public TaskPool
{
protected:
	list<CompFragment*> tasks; // single list for all threads
public:
	SimpleTaskPool() {}
	~SimpleTaskPool() {}

	virtual void Init(int t_num) {}
	virtual void Add(int t_num, const list<CompFragment*> &cfs);
	virtual bool Get(int t_num, list<CompFragment*> &cfs, int max_sz = 1);
};

}