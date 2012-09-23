#pragma once

#include "codeobject.h"
#include "codeargs.h"

namespace rage {

class AtomicCodeObject : public CodeObject // atom code fragment - call of C++ procedure
{
protected:
	//CodeObject::ExecFunc execFunc;

public:
	bool isAtomic() const {
		return true;
	}

	virtual void exec(const CodeArgs& args) = 0; // code to exec
};

}
