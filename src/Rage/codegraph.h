#pragma once

#include "codefragment.h"
#include "codevertex.h"

#include <map>
#include <set>
//#include <boost/shared_ptr.hpp>

using namespace std;

namespace fprts {

class CodeGraph : public CodeFragment // struct fragment of code represented as graph
{
public:
	typedef map<VertexId, VertexData> DataVertexMap;
	typedef map<VertexId, VertexCall> CallVertexMap;
	typedef map<VertexId, set<VertexId> > ArcMap;
public:	
	DataVertexMap data_vertices;
	CallVertexMap call_vertices;
	//CodeVertexArray vertices; // storage of all vertices
	ArcMap arcs_in, arcs_out; // for each cf: incoming arcs and outcoming arcs
	//set<VertexId> root; // root of graph
protected:
	VertexId id_cnt;
protected:
	VertexId GetNextId();
public:
	CodeGraph() : id_cnt(0) {}
	~CodeGraph() {}
	
	void AddArc(VertexId start, VertexId end);
	//void AddRoot(VertexId rt);	

	VertexId AddDataVertex(DataFragment::Type tp, const vector<int> &params);
	VertexId AddCallVertex(FragmentId code_id, const vector<VertexCall::Arg> &args, unsigned int i_sz, unsigned int o_sz);

	virtual bool IsAtom() const {return false;} // struct fragment
	virtual void Build(const CodeLibrary &lib) = 0; // build code graph
};

}
