#pragma once

#include "compvertex.h"
#include <boost/scoped_ptr.hpp>

namespace rage {

class WhileVertex : public CompVertex
{
protected:			
	boost::scoped_ptr<Expression> condExpr;

public:	
	WhileVertex(Expression *expr) : condExpr(expr) {}	
	~WhileVertex() {}

	virtual CompType getCompType() const {
		return CompVertex::WHILE;
	}	

	Expression* getCondExpr() const {
		return condExpr.get();
	}
};

}
