#include "rwbuffer.h"

namespace rage {

void ReadWriteBuffer::write(void *data, unsigned int dataSize) { // write data to buf
	if(writePos + dataSize > getSize()) { // isn't enough space in buffer
		resize((getSize() + dataSize) * 2); // grow to larger size
	}
	memcpy((void*)(getCBuffer() + writePos), data, dataSize);
	writePos += dataSize;
}
    
void ReadWriteBuffer::read(void *data, unsigned int dataSize) { // read data from buf
	if(readPos + dataSize > getSize()) // error - trying to read outside of buffer
		throw Exception("Buffer read error");
	memcpy(data, (void*)(getCBuffer() + readPos), dataSize);
	readPos += dataSize;
}

void ReadWriteBuffer::reset() {
	writePos = 0;
	readPos = 0;
}

//////////////////////////// RW Operators /////////////////////////////////
ReadWriteBuffer& operator << (ReadWriteBuffer& b, int val) {
	b.writeScalar<int>(val);
return b;
}

ReadWriteBuffer& operator << (ReadWriteBuffer& b, unsigned int val)  {
	b.writeScalar<unsigned int>(val); 
return b;
}

ReadWriteBuffer& operator << (ReadWriteBuffer& b, float val) {
	b.writeScalar<float>(val); 
return b;
}

ReadWriteBuffer& operator << (ReadWriteBuffer& b, double val) {
	b.writeScalar<double>(val); 
return b;
}

ReadWriteBuffer& operator << (ReadWriteBuffer& b, char val) {
	b.writeScalar<char>(val); 
return b;
}

ReadWriteBuffer& operator << (ReadWriteBuffer& b, long val) {
	b.writeScalar<long>(val); 
return b;
}

ReadWriteBuffer& operator << (ReadWriteBuffer& b, unsigned long val) {
	b.writeScalar<unsigned long>(val); 
return b;
}

ReadWriteBuffer& operator << (ReadWriteBuffer& b, bool val) {
	b.writeScalar<bool>(val); 
return b;
}

ReadWriteBuffer& operator << (ReadWriteBuffer& b, const std::string& val) {	
	unsigned int sz = val.size();
	b << sz;
	b.write((void*)val.c_str(), val.size()*sizeof(char)); 
return b;
}

ReadWriteBuffer& operator >> (ReadWriteBuffer& b, int& val) {
	b.readScalar<int>(val);
return b;
}

ReadWriteBuffer& operator >> (ReadWriteBuffer& b, unsigned int& val) {
	b.readScalar<unsigned int>(val);
return b;
}

ReadWriteBuffer& operator >> (ReadWriteBuffer& b, float& val) {
	b.readScalar<float>(val);
return b;
}

ReadWriteBuffer& operator >> (ReadWriteBuffer& b, double& val) {
	b.readScalar<double>(val);
return b;
}

ReadWriteBuffer& operator >> (ReadWriteBuffer& b, char& val) {
	b.readScalar<char>(val);
return b;
}

ReadWriteBuffer& operator >> (ReadWriteBuffer& b, long& val) {
	b.readScalar<long>(val);
return b;
}

ReadWriteBuffer& operator >> (ReadWriteBuffer& b, unsigned long& val) {
	b.readScalar<unsigned long>(val);
return b;
}

ReadWriteBuffer& operator >> (ReadWriteBuffer& b, bool& val) {
	b.readScalar<bool>(val);
return b;
}

ReadWriteBuffer& operator >> (ReadWriteBuffer& b, std::string& val) {
	unsigned int sz;
		b >> sz;
	unsigned int minSize = (b.getSize() - b.getReadPos()) > sz ?  sz/sizeof(char) : (b.getSize() - b.getReadPos())/sizeof(char);
	char *str = new char[minSize];
		b.read(str, minSize*sizeof(char));
	val = string(str, minSize);
	delete[] str;
return b;
}

}