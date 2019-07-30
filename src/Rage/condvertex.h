#pragma once

#include "compvertex.h"
#include <boost/scoped_ptr.hpp>

namespace rage {

class CondVertex : public CompVertex
{
protected:	
	boost::scoped_ptr<Expression> condExpr;	

public:		
	CondVertex(Expression *expr) : condExpr(expr) {}
	~CondVertex() {}

	virtual CompType getCompType() const {
		return CompVertex::COND;
	}	

	Expression* getCondExpr() const {
		return condExpr.get();
	}
};

}
