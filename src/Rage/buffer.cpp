#include "buffer.h"
#include "exception.h"

namespace rage {
    
void* Buffer::resize(unsigned int newSize) { // get mem for buffer
	if(newSize == 0) { // resize to zero - clear
		clear();
	} else {
		char* buf = new char[newSize]; // get memory
		if(!buf)
			throw Exception("Buffer alloc error");
		if(data.get() && size)
			memcpy(buf, data.get(), size); // copy old to new
		data.reset(buf); // reset to new
		size = newSize;
	}
return data.get();
}

void Buffer::clear() {
	data.reset(0);
	size = 0;
}

}
