#pragma once

#include "expression.h"
#include <string>
#include <boost/scoped_ptr.hpp>

using namespace std;

namespace rage {

class ExpressionConstItem : public Expression 
{
public:
	enum ConstType
	{
		INT = 0
	};

protected:	
	union {
		int int_val;
	} value;	
	ConstType constType;
	
public:
	ExpressionConstItem(int val) : constType(INT) {
		value.int_val = val;
	}

	ConstType getConstType() const {
		return constType;
	}

	template<class T> T getValue() {
		switch(constType) {
			case INT: return value.int_val;
		}
	}

	Type getType() const {
		return Expression::CONST_ITEM;
	}
};

}
