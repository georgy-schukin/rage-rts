#pragma once

#include "codevertex.h"
#include <boost/ptr_container/ptr_vector.hpp>

namespace rage {

class CompVertex : public CodeVertex
{
public:
	enum CompType
	{
		BLOCK = 0,
		RANGE,
		WHILE,
		COND,
		CALL
	};

	enum OrderType
	{
		SEQ = 0,
		PAR,
		EXCLUSIVE,
		REDUCTION
	};

private:
	boost::ptr_vector<CodeVertex> childrenStorage;
	vector<CodeVertex*> children;

public:
	CompVertex() {}
	CompVertex(CodeVertex *p) : CodeVertex(p) {}
	~CompVertex() {}

	virtual CodeVertex::Type getType() const {
		return CodeVertex::COMP;
	}		

	unsigned int getChildrenNum() const {
		return children.size();
	}

	CodeVertex* getChild(unsigned int ind) const {
		return children[ind];
	}	

	const vector<CodeVertex*>& getChildren() const {
		return children;
	}	

	void addChild(CodeVertex *vertex);

	virtual CompType getCompType() const = 0;
};

}