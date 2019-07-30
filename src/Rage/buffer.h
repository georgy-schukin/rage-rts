#pragma once

#include <stdlib.h>
#include <string.h>
#include <boost/scoped_ptr.hpp>

namespace rage {

class Buffer // buffer for data storage
{
private:
    boost::scoped_ptr<char> data; // data in buffer   
    unsigned int size; // total size of buf (in bytes)       

protected:
	char* getCBuffer() const { // get char data
		return data.get();
	}
    
public:
	Buffer() : size(0) {}

	Buffer(unsigned int sz) : size(0) {
		resize(sz);
	}

	Buffer(void *dt, unsigned int sz) {
		Buffer::Buffer(sz);
		memcpy(getBuffer(), dt, sz);
	}

	Buffer::Buffer(const Buffer& b) {
		Buffer::Buffer(b.getSize());	
		memcpy(getBuffer(), b.getBuffer(), b.getSize());
	}

	Buffer::~Buffer() {}
    	
	void* resize(unsigned int newSize); // resize for new sz

	void clear();

	void* getBuffer() const { // get data
		return (void*)data.get();
	}

    unsigned int getSize() const { // get size of data buf
		return size;
	} 
    
    bool isEmpty() const { // check if buf is empty
		return (size == 0);
	} 
};

}
