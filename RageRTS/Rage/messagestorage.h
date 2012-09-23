#pragma once

#include "message.h"
#include <boost/shared_ptr.hpp>

#include <boost/shared_ptr.hpp>
#include <vector>

using namespace std;

namespace rage {

class MessageStorage // storage for messages
{
protected:	
	vector<boost::shared_ptr<Message> > messages;
	vector<bool> flags;
	unsigned int msgDefaultSize;	

public:
	MessageStorage(unsigned int msgSize) : msgDefaultSize(msgSize) {}
	MessageStorage(unsigned int size, unsigned int msgSize) : msgDefaultSize(msgSize) {
		alloc(size, msgSize);
	}
	~MessageStorage() {}

	void alloc(unsigned int size, unsigned int msgSize); // allocate pool of messages
	void clear();

	Message* getMessage(); // alloc free message
	Message* getMessage(unsigned int id); // get msg by id
	void freeMessage(Message* msg); // free message
	void freeMessage(unsigned int id); // free message
};

}
