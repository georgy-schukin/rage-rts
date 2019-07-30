#pragma once

#include "rtstypes.h"

#include <map>

using namespace std;

namespace fprts
{

///////////////////// Control System ///////////////////////
class ControlSystem // cf control
{
public:
	map<FragmentId, IdSet> control; // cf -> set of waiting cfs
	map<FragmentId, IdSet> control_output; // cf -> set of 

public:
	ControlSystem() {}
	~ControlSystem() {}

	void Signal(FragmentId cf_id);
};

}
