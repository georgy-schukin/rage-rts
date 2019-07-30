#pragma once

#include "types.h"

namespace rage {

class ICommunicator // communicator interface
{
public:
	struct Status
	{
		unsigned int size;
		int tag;		
		NodeId node;	
	};

public:
	virtual int getRank() const = 0;
	virtual int getSize() const = 0;
	virtual void send(void *data, unsigned int dataSize, int tag, NodeId node) = 0;
	virtual void isend(void *data, unsigned int dataSize, int tag, NodeId node, int& req) = 0;
	virtual void recv(void *data, unsigned int dataSize, int tag, NodeId node) = 0;
	virtual bool check(ICommunicator::Status& status) = 0;
	virtual bool test(int req) = 0;
};

}