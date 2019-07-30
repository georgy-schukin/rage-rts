#pragma once

#include "expression.h"
#include <string>
#include <boost/scoped_ptr.hpp>

using namespace std;

namespace rage {

class ExpressionDataItem : public Expression 
{
protected:	
	string dataName;
	boost::scoped_ptr<Expression> arrayExpr;

public:
	ExpressionDataItem(const string& name) : dataName(name) {
		arrayExpr.reset(0);
	}
	ExpressionDataItem(const string& name, Expression *expr) : dataName(name) {
		arrayExpr.reset(expr);
	}
	~ExpressionDataItem() {}

	const string& getDataName() const {
		return dataName;
	}

	Expression* getArrayExpression() const {
		return arrayExpr.get();
	}

	Type getType() const {
		return Expression::DATA_ITEM;
	}
};

}
