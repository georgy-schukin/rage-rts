#pragma once

#include "dataobject.h"
#include <boost/scoped_ptr.hpp>

namespace rage {

class DataBlock : public DataObject
{
protected:
	boost::scoped_ptr<char> data;
	unsigned int dataSize;

public:	
	DataBlock(unsigned int size) : dataSize(size) {}
	DataBlock(const string& name, unsigned int size) : DataObject(name), dataSize(size) {}
	~DataBlock() {}

	DataObject::Type getType() const {
		return DataObject::ATOMIC;
	}

	void* getData() const {
		return (void*)data.get();
	}

	unsigned int getDataSize() const {
		return dataSize;
	}	

	void create();
};

}
