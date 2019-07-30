#pragma once

#include "compvertex.h"

namespace rage {

class BlockVertex : public CompVertex
{
protected:	
	OrderType orderType;

public:	
	BlockVertex() : orderType(CompVertex::SEQ) {}
	BlockVertex(OrderType order) : orderType(order) {}	
	~BlockVertex() {}

	virtual CompType getCompType() const {
		return CompVertex::BLOCK;
	}

	void setOrderType(OrderType orderType) {
		this->orderType = orderType;
	}

	OrderType getOrderType() const {
		return orderType;
	}
};

}
