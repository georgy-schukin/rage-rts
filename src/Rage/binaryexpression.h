#pragma once

#include "expression.h"
#include <boost/scoped_ptr.hpp>

namespace rage {

class BinaryExpression : public Expression 
{
public:
	enum BinaryOp
	{
		PLUS = 0,	// +
		MINUS,		// -
		MULT,		// *
		DIV,		// /
		EQ,			// ==
		NEQ,		// !=
		LT,			// <
		LE,			// <=
		GT,			// >
		GE,			// >=
		AND,		// &&
		OR			// ||
	};

protected:
	BinaryOp operation;
	boost::scoped_ptr<Expression> first, second;

public:
	BinaryExpression(BinaryOp op, Expression *f, Expression *s) : operation(op), first(f), second(s) {}		
	~BinaryExpression() {}

	BinaryOp getOperation() const {
		return operation;
	}

	Expression* getFirstMember() const {
		return first.get();
	}

	Expression* getSecondMember() const {
		return second.get();
	}

	Type getType() const {
		return Expression::BINARY;
	}
};

}
