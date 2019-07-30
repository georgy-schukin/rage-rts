#pragma once

#include "codevertex.h"
#include <vector>
#include <string>
#include <boost/scoped_ptr.hpp>

using namespace std;

namespace rage {

class DataVertex : public CodeVertex
{
public:
	enum DataType
	{
		BLOCK = 0,
		OBJECT,
		STRUCT,
		ARRAY
	};

protected:
	DataType dataType;	
	unsigned int dataSize;
	string dataName; // name of data var
	boost::scoped_ptr<Expression> arrayExpr;
	//ValuesFunc valuesFunc;

public:
	//DataVertex() : dataType(DataVertex::BLOCK) {}
	//DataVertex(DataType tp) : dataType(tp), valuesFunc(0) {}
	DataVertex(const string& n, DataType tp, unsigned int dSize) : dataName(n), dataType(tp), dataSize(dSize) {}
	DataVertex(const string& n, DataType tp, unsigned int dSize, Expression *aExpr) : dataName(n), dataType(tp), dataSize(dSize), arrayExpr(aExpr) {}
	//DataVertex(const string& n, DataType tp, ValuesFunc vFunc) : dataName(n), dataType(tp), valuesFunc(vFunc) {}
	~DataVertex() {}

	virtual CodeVertex::Type getType() const {
		return CodeVertex::DATA;
	}

	/*void setDataType(DataType type) {
		this->dataType = type;
	}*/
	
	DataType getDataType() const {
		return dataType;
	}

	/*void setDataName(const string& name) {
		this->dataName = name;
	}*/

	const string& getDataName() const {
		return dataName;
	}

	unsigned int getDataSize() const {
		return dataSize;
	}

	Expression* getArrayExpr() const {
		return arrayExpr.get();
	}

	/*void setParamFunc(ValuesFunc func) {
		this->valuesFunc = func;
	}

	ValuesFunc getParamFunc() const {
		return valuesFunc;
	}*/
};

}
