#pragma once

#include "rtstypes.h"

#include <map>

using namespace std;

namespace fprts
{

//////////////////////// Location System //////////////////////////////
class LocationSystem // system to locate structured df
{
public:
	map<FragmentId, set<NodeId> > location; // location of fragment
	map<FragmentId, set<NodeId> > watcher_location; // location of fragment watcher
};

}
