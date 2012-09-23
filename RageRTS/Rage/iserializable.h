#pragma once

#include "message.h"

namespace rage {

class ISerializable // interface for serialization
{
protected:
	virtual void pack(Message& msg) const = 0; // pack itself to buffer
	virtual void unpack(Message& msg) = 0; // unpack itself from buffer

public:
	friend Message& operator << (Message &msg, const ISerializable &obj) { // pack operator
		obj.pack(msg);
		return msg;
	} 

	friend Message& operator >> (Message &msg, ISerializable &obj) { // unpack operator 
		obj.unpack(msg);
		return msg;
	} 
};

}
