#pragma once

#include <set>

namespace rage {

//typedef unsigned int FragmentId; // type of fragments id in RTS
typedef int NodeId; // type of node id in RTS
typedef unsigned int TreeId;
typedef unsigned int VertexId;
typedef unsigned int CodeId;
typedef unsigned int TaskId;
typedef unsigned int DataId;

//typedef std::pair<NodeId, unsigned int> ProcedureId;
class ProcedureId
{
public:
	NodeId nodeId;
	unsigned int id;

public:
	ProcedureId() : nodeId(0), id(0) {}
	ProcedureId(NodeId nId, unsigned int i) : nodeId(nId), id(i) {}
	ProcedureId(const ProcedureId &pId) : nodeId(pId.nodeId), id(pId.id) {}
	~ProcedureId() {}
};
//typedef std::set<FragmentId> FragmentIdSet;

}
