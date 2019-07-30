#pragma once

#include "types.h"
#include <boost/shared_ptr.hpp>
#include "codeargs.h"
#include "expression.h"

namespace rage {

class CodeTree;

class CodeVertex // codevertex in code tree
{
public:
	typedef bool(*BooleanFunc)(const CodeArgs& args); // get bool values from args
	typedef int(*IntFunc)(const CodeArgs& args); // get int value from args
	typedef void(*ValuesFunc)(const CodeArgs& args, vector<int>& values); // get new values from args
	typedef void(*ArgsFunc)(const CodeArgs& args, CodeArgs& out); // get new values from args

public:
	enum Type
	{	
		DATA = 0,
		COMP		
	};

protected:	
	VertexId id;
	CodeVertex *parent;	// parent vertex
	//CodeVertex *next; // next in chain
	CodeTree *codeTree; // host tree
	vector<string> valueReqs; // need these values
	vector<string> dataReqs; // need these data objects

public:
	CodeVertex() : parent(0), id(0) {}
	CodeVertex(CodeVertex *p) : parent(p), id(0) {}
	~CodeVertex() {}

	void setParent(CodeVertex *parent) {
		this->parent = parent;
	}

	CodeVertex* getParent() const {
		return parent;
	}	

	void setId(VertexId id) {
		this->id = id;
	}

	VertexId getId() const {
		return id;
	}

	void setCodeTree(CodeTree *codeTree) {
		this->codeTree = codeTree;
	}

	CodeTree* getCodeTree() const {
		return codeTree;
	}

	void addDataReq(const string& name) {
		dataReqs.push_back(name);
	}

	void addValueReq(const string& name) {
		valueReqs.push_back(name);
	}

	const vector<string>& getDataReqs() const {
		return dataReqs;
	}

	const vector<string>& getValueReqs() const {
		return valueReqs;
	}

	virtual CodeVertex::Type getType() const = 0;	
};

}
