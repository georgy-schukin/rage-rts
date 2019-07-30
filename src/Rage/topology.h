#pragma once

#include "types.h"
#include <set>

using namespace std;

namespace rage {

class Topology // topology info on the node
{
public:
	enum Type 
	{
		ALL_TO_ALL = 0,
		LATTICE,
		RING
	};

protected:
	Topology::Type type;
	NodeId rank; // id of this node
	unsigned int size; // total num of nodes in topology	
	set<NodeId> neighbours; // ids of neigh nodes	

public:
	Topology();
	Topology(Topology::Type tp);
	Topology(Topology::Type tp, NodeId rnk, unsigned int sz);
	Topology(Topology::Type tp, NodeId rnk, unsigned int sz, const set<NodeId> &neigh); 
	~Topology() {}

	/*void SetType(Topology::Type tp) {type = tp;}
	void SetRank(NodeId rnk) {rank = rnk;}
	void SetSize(unsigned int sz) {size = sz;}*/
	void SetNeighbours(const set<NodeId> &neigh) {neighbours = neigh;}

	void Init(Topology::Type tp, NodeId rnk, unsigned int sz);
	void Init(Topology::Type tp, NodeId rnk, unsigned int sz, const set<NodeId> &neigh);
	
	Topology::Type GetType() const {return type;}
	NodeId GetRank() const {return rank;}
	unsigned int GetSize() const {return size;}	
	const set<NodeId>& GetNeighbours() const {return neighbours;}

	static set<NodeId> GenerateNeighbours(Topology::Type tp, NodeId rnk, unsigned int sz); // gen neighbours by type, rank and size
};

}
