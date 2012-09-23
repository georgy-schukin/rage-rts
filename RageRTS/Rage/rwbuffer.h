#pragma once

#include "buffer.h"
#include "exception.h"
#include <string>

using namespace std;

namespace rage {

class ReadWriteBuffer : public Buffer // system data buffer with capability to read from/write to
{
protected:
    unsigned int readPos; // curr position in buffer for reading
    unsigned int writePos; // curr position in buffer for writing
    
public:    	
    ReadWriteBuffer() : readPos(0), writePos(0) {}
    ReadWriteBuffer(unsigned int sz) : Buffer(sz), readPos(0), writePos(0) {}
	~ReadWriteBuffer() {}
    
    void setReadPos(unsigned int pos) {
		readPos = pos;
	}

	unsigned int getReadPos() const {
		return readPos;
	}

    void setWritePos(unsigned int pos) {
		writePos = pos;
	}
	
	unsigned int getWritePos() const {
		return writePos;
	}

	void write(void *data, unsigned int dataSize); // write data to buf	
	template<class T> void writeScalar(const T& var);

	void read(void *data, unsigned int dataSize); // read data from buf
	template<class T> void readScalar(T& var);
	template<class T> T readScalar();

	void reset();
};

template<class T>
void ReadWriteBuffer::writeScalar(const T& var) { // write data to buf
	if(writePos + sizeof(T) > getSize()) { // isn't enough space in buffer
		resize((getSize() + sizeof(T)) * 2);	// grow by 2	
	}
	*(T*)((char*)getBuffer() + writePos) = var;
	writePos += sizeof(T);
}

template<class T>
void ReadWriteBuffer::readScalar(T& var) { // read data from buf
	if(readPos + sizeof(T) > getSize())  // error - trying to read outside of buffer
		throw Exception("Buffer read error");
	var = *(T*)(getCBuffer() + readPos);	
	readPos += sizeof(T);
}

template<class T>
T ReadWriteBuffer::readScalar() { // read data from buf
	if(readPos + sizeof(T) > getSize())  // error - trying to read outside of buffer
		throw Exception("Buffer read error");			
	T var = *(T*)(getCBuffer() + readPos);	
	readPos += sizeof(T);
return var;
}

///////////////////////// RW Operators ///////////////////////////////////
ReadWriteBuffer& operator << (ReadWriteBuffer& b, int val);
ReadWriteBuffer& operator << (ReadWriteBuffer& b, unsigned int val);
ReadWriteBuffer& operator << (ReadWriteBuffer& b, float val); 	
ReadWriteBuffer& operator << (ReadWriteBuffer& b, double val); 
ReadWriteBuffer& operator << (ReadWriteBuffer& b, char val);	
ReadWriteBuffer& operator << (ReadWriteBuffer& b, long val); 	
ReadWriteBuffer& operator << (ReadWriteBuffer& b, unsigned long val);
ReadWriteBuffer& operator << (ReadWriteBuffer& b, bool val); 
ReadWriteBuffer& operator << (ReadWriteBuffer& b, const string& val); 	

ReadWriteBuffer& operator >> (ReadWriteBuffer& b, int& val);	
ReadWriteBuffer& operator >> (ReadWriteBuffer& b, unsigned int& val);	
ReadWriteBuffer& operator >> (ReadWriteBuffer& b, float& val);	
ReadWriteBuffer& operator >> (ReadWriteBuffer& b, double& val); 
ReadWriteBuffer& operator >> (ReadWriteBuffer& b, char& val); 
ReadWriteBuffer& operator >> (ReadWriteBuffer& b, long& val); 	
ReadWriteBuffer& operator >> (ReadWriteBuffer& b, unsigned long& val); 
ReadWriteBuffer& operator >> (ReadWriteBuffer& b, bool& val); 	
ReadWriteBuffer& operator >> (ReadWriteBuffer& b, string& val);
	
}
