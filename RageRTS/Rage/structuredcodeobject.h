#pragma once

#include "codeobject.h"
#include "codetree.h"
#include <boost/scoped_ptr.hpp>

namespace rage {

class StructuredCodeObject : public CodeObject // complex structured code fragment (procedure)
{
private:	
	boost::scoped_ptr<CodeTree> codeTree;

protected:
	friend class CodeLibrary;

	void build(CodeLibrary *lib) {
		buildTree(getCodeTree(), lib);
	}

	virtual void buildTree(CodeTree *tree, CodeLibrary *lib) = 0;

public:
	StructuredCodeObject() {
		codeTree.reset(new CodeTree(this));
	}

	~StructuredCodeObject() {}
	
	CodeTree* getCodeTree() const {
		return codeTree.get();
	}

	bool isAtomic() const {return false;}		
};

}
