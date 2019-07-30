#include "datablock.h"
#include "exception.h"

namespace rage {

void DataBlock::create() {
	if(dataSize == 0) 
		throw Exception("Empty data block size");
	char *buf = new char[dataSize];
	if(!buf)
		throw Exception("Data block alloc error");
	data.reset(buf);
}

}