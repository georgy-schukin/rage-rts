#pragma once

#include "codevertex.h"
#include <boost/scoped_ptr.hpp>

namespace rage {

class CodeObject;

class CodeTree
{
public:
	boost::scoped_ptr<CodeVertex> root;
	CodeObject *parent;

protected:
	friend class CodeLibrary;	

	void processVertices(); // set vertices id and parent
	void processVertex(CodeVertex *v, int& currId);

public:
	CodeTree(CodeObject *p = 0) : parent(p) {}	
	~CodeTree() {}

	void setParent(CodeObject *parent) {
		this->parent = parent;
	}

	CodeObject* getParent() const {
		return parent;
	}

	void setRoot(CodeVertex *rt) {
		this->root.reset(rt);
	}

	CodeVertex* getRoot() const {
		return root.get();
	}
};

}
