#pragma once

#include "types.h"
#include "topology.h"
#include <map>

using namespace std;

namespace rage {

class LoadCollector // gather load info from neighbour nodes
{
public:
	class LoadInfo 
	{
	public:
		int cf_ready; // num of ready cfs on node
		int cf_weight; // total weight of ready cfs on node
		int df_weight; // total weight of current dfs on node
		int cf_done_num; // total num of executed cfs
		int cf_done_weight; // total weight of executed cfs

	public:
		LoadInfo() : cf_ready(0), cf_weight(0), df_weight(0), cf_done_num(0), cf_done_weight(0) {}
		~LoadInfo() {}
	};

protected:
	map<NodeId, LoadCollector::LoadInfo> load; // load on this node and neighbour nodes
	NodeId root_node;

public:
	LoadCollector() {}
	~LoadCollector() {}

	void SetNodes(const set<NodeId> &nodes);
	void GetNodes(set<NodeId> &nodes); // get id of neighbour nodes

	void SetRootNode(NodeId root) {root_node = root;}
	NodeId GetRootNode() const {return root_node;}

	void UpdateInfo(NodeId node, const LoadCollector::LoadInfo &info);
	
	unsigned int GetNodesNum() const {return load.size();}

	LoadCollector::LoadInfo& GetInfo(NodeId node) {return load[node];}
};

}
