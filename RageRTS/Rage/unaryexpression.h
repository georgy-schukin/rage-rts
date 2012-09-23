#pragma once

#include "expression.h"
#include <boost/scoped_ptr.hpp>

namespace rage {

class UnaryExpression : public Expression 
{
public:
	enum UnaryOp
	{
		MINUS = 0,	// -
		NOT			// !
	};

protected:
	UnaryOp operation;
	boost::scoped_ptr<Expression> member;

public:
	UnaryExpression(UnaryOp op, Expression *e) : operation(op), member(e) {}		
	~UnaryExpression() {}

	UnaryOp getOperation() const {
		return operation;
	}

	Expression* getMember() const {
		return member.get();
	}

	Type getType() const {
		return Expression::UNARY;
	}
};

}
