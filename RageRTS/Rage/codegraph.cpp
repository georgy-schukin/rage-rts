#include "codegraph.h"

namespace fprts {

void CodeGraph::AddArc(VertexId start, VertexId end) {
	arcs_out[start].insert(end);
	arcs_in[end].insert(start);
}

/*void CodeGraph::AddRoot(VertexId rt) {
	root.insert(rt);
}*/

/*CodeVertex* CodeGraph::GetVertex(VertexId id) { // get vertex from graph
	return (id < vertices.size()) ? vertices[id].get() : 0;
}*/

VertexId CodeGraph::AddDataVertex(DataFragment::Type tp, const vector<int> &params) { // create data vertex
	VertexId id = GetNextId();
	VertexData &vd = data_vertices[id];
	vd.SetId(id);
	vd.SetData(tp, params);
return id;
}

VertexId CodeGraph::AddCallVertex(FragmentId code_id, const vector<VertexCall::Arg> &args, unsigned int i_sz, unsigned int o_sz) { // create call vertex
	VertexId id = GetNextId();	
	VertexCall &vc = call_vertices[id];
	vc.SetId(id);
	vc.SetCodeId(code_id);
	vc.SetArgs(args, i_sz, o_sz);
return id;
}

VertexId CodeGraph::GetNextId() {
	return id_cnt++;
}

}