#pragma once

#include "compvertex.h"
#include <vector>
#include <boost/ptr_container/ptr_vector.hpp>

namespace rage {

class CodeObject;

class CallVertex : public CompVertex
{
protected:
	CodeObject *code; // code to call
	boost::ptr_vector<Expression> args; // args (as expressions)
	//ArgsFunc argFunc; // func to prepare args

public:		
	//CallVertex() : code(0) {}
	CallVertex(CodeObject *ob) : code(ob) {}	
	//CallVertex(CodeObject *ob, ArgsFunc aFunc) : code(ob), argFunc(aFunc) {}
	~CallVertex() {}

	virtual CompType getCompType() const {
		return CompVertex::CALL;
	}

	void setCodeObject(CodeObject *code) {
		this->code = code;
	}

	CodeObject* getCodeObject() const {
		return code;
	}

	/*void setArgFunc(ArgsFunc func) {
		this->argFunc = func;
	}

	ArgsFunc getArgFunc() const {
		return argFunc;
	}*/

	void addArg(Expression *expr) {
		args.push_back(expr);
	}

	unsigned int getArgsNum() const {
		return args.size();
	}

	Expression* getArg(unsigned int index) {
		return &(args.at(index));
	}
};

}
