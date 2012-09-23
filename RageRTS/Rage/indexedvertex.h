#pragma once

#include "compvertex.h"
#include <boost/scoped_ptr.hpp>

namespace rage {

class IndexedVertex : public CompVertex
{
protected:	
	OrderType orderType;
	string indexName;	
	boost::scoped_ptr<Expression> beginExpr, endExpr, stepExpr;

public:	
	IndexedVertex(const string& iName, OrderType oType, Expression *bExpr, Expression *eExpr, Expression *sExpr) : 
	  indexName(iName), orderType(oType), beginExpr(bExpr), endExpr(eExpr), stepExpr(sExpr) {} 
	~IndexedVertex() {}

	virtual CompType getCompType() const {
		return CompVertex::RANGE;
	}	

	/*void setOrderType(OrderType orderType) {
		this->orderType = orderType;
	}*/

	OrderType getOrderType() const {
		return orderType;
	}

	/*void setIndexName(const string& name) {
		this->indexName = name;
	}*/

	const string& getIndexName() const {
		return indexName;
	}

	Expression* getBeginExpr() const {
		return beginExpr.get();
	}

	Expression* getEndExpr() const {
		return endExpr.get();
	}

	Expression* getStepExpr() const {
		return stepExpr.get();
	}
};

}
