#include "topology.h"

namespace rage {

Topology::Topology() : type(Topology::ALL_TO_ALL), rank(-1), size(0) {}

Topology::Topology(Topology::Type tp) : type(tp), rank(-1), size(0) {}

Topology::Topology(Topology::Type tp, NodeId rnk, unsigned int sz) : 
	type(tp), rank(rnk), size(sz) {
		neighbours = Topology::GenerateNeighbours(tp, rnk, sz);
}

Topology::Topology(Topology::Type tp, NodeId rnk, unsigned int sz, const set<NodeId> &neigh) : 
	type(tp), rank(rnk), size(sz), neighbours(neigh) {}

void Topology::Init(Topology::Type tp, NodeId rnk, unsigned int sz) {
	type = tp;
	rank = rnk;
	size = sz;
	neighbours = Topology::GenerateNeighbours(tp, rnk, sz);
}

void Topology::Init(Topology::Type tp, NodeId rnk, unsigned int sz, const set<NodeId> &neigh) {
	type = tp;
	rank = rnk;
	size = sz;
	neighbours = neigh;
}

set<NodeId> Topology::GenerateNeighbours(Topology::Type tp, NodeId rnk, unsigned int sz) { // gen neighbours
	set<NodeId> neigh;
	if(sz == 0) return neigh;
	switch(tp) {
		case Topology::ALL_TO_ALL:
			for(unsigned int i = 0;i < sz;i++) 
				if(i != rnk) neigh.insert(i);
			break;
		case Topology::LATTICE: 
			if(rnk > 0) neigh.insert(rnk - 1);
			if(rnk + 1 < sz) neigh.insert(rnk + 1);
			break;
		case Topology::RING:
			neigh.insert((rnk - 1)%sz);
			neigh.insert((rnk + 1)%sz);
			break;								
	}
return neigh;
}

/*Lattice1DTp::Lattice1DTp(NodeId rnk, UInt sz) : Topology(rnk, sz)
{
	if(size > 1)
	{
		if(rank == 0)
		{
			neighbours.resize(1);
			neighbours[0] = rank + 1; // right neighbour
		}
		else if (rank == size - 1)
		{
			neighbours.resize(1);
			neighbours[0] = rank - 1; // left neighbour
		}
		else
		{
			neighbours.resize(2);
			neighbours[0] = rank - 1; // left neighbour
			neighbours[1] = rank + 1; // right neighbour
		}
	}
}*/

}