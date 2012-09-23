#pragma once

#include "codeargs.h"

namespace rage {

class Expression
{
public:
	enum Type 
	{
		BINARY = 0,
		UNARY,
		DATA_ITEM,
		CONST_ITEM
	};

public:
	virtual Type getType() const = 0;
	virtual int evalInt(const CodeArgs &args) = 0;
	virtual bool evalBoolean(const CodeArgs &args) = 0;
	virtual string evalData(const CodeArgs &args) = 0;
};

}
