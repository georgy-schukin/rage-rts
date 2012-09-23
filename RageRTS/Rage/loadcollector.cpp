#include "loadcollector.h"
#include <boost/range/adaptor/map.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/foreach.hpp>
#include <algorithm>

namespace rage {

/*void LoadCollector::Init(const Topology &tp) {
	this_node = tp.GetRank();
	set<NodeId> neigh = tp.GetNeighbours();
	neigh.insert(this_node); // add this node	
	for(set<NodeId>::const_iterator it = neigh.begin();it != neigh.end();it++) { // init load info for nodes
		load[*it] = LoadInfo();
	}
}*/

void LoadCollector::SetNodes(const set<NodeId> &nodes) {
	BOOST_FOREACH(NodeId node, nodes) {
		load[node] = LoadInfo();			
	}
}

void LoadCollector::GetNodes(set<NodeId> &nodes) { // get nodes in area
	boost::copy(load | boost::adaptors::map_keys, std::inserter(nodes, nodes.end())); 
}

void LoadCollector::UpdateInfo(NodeId node, const LoadCollector::LoadInfo &info) {
	load[node] = info;
}

}
