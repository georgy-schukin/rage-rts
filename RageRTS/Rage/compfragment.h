#pragma once

#include "fragment.h"
#include "rwbuffer.h"
#include "rtstypes.h"
#include "context.h"

namespace fprts {

class CompFragment : public Fragment // comp fragment - call of function with args
{
public:
	enum State // states of cf
	{
		NEW = 0,	// added to proc
		FREE,		// deps are satisfied
		READY,		// ready to exec
		SCHED,		// ready and taken by scheduler
		EXEC,		// executing
		DONE		// finished execution
	};

public:	
	FragmentId code_id; // id of code fragment
	//InputArgContext iac; // input args for code fragment
	InputContext ic; // real input (need before exec)
	//State state;
	//unsigned int dep_cnt;
	//FragmentIdSet arcs_out;

protected:
	virtual void Pack(Message &msg); // pack function
	virtual void Unpack(Message &msg); // unpack function

public:
	CompFragment(FragmentId i) : Fragment(i) {}
	CompFragment(FragmentId i, FragmentId code) : Fragment(i), code_id(code) {}
	virtual ~CompFragment() {}

	void SetCodeId(FragmentId id) {code_id = id;}
	//void SetState(State s) {state = s;}
};

class CompFragmentGroup : public CompFragment
{
public:
	pair<FragmentId, FragmentId> range;
	unsigned int size;
public:
	CompFragmentGroup(FragmentId i) : CompFragment(i) {}
	CompFragmentGroup(FragmentId i, FragmentId code) : CompFragment(i, code) {}
	virtual ~CompFragmentGroup() {}
};

}
