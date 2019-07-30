#pragma once

#include "messagestorage.h"
#include "icommunicator.h"
#include <boost/shared_ptr.hpp>

#include <boost/thread/mutex.hpp>
#include <queue>

using namespace std;

namespace rage {

class MessageSystem // system to communicate among nodes with messages
{
protected:
	MessageStorage *storage;
	ICommunicator *communicator;

	queue<pair<unsigned int, NodeId> > tasks; // send tasks
	map<unsigned int, int> access; // num of accesses to message	
	set<unsigned int> free_flg; // ids of messages that were freed
	map<int, unsigned int> isends; // request -> msg id : ongoing isends

	boost::mutex mutex;

public:
	MessageSystem(ICommunicator *comm) : communicator(comm), storage(0) {}
	~MessageSystem() {
		if(storage) delete storage;
	}

	void init(unsigned int size, unsigned int msgSize);

	Message* getMessage(Message::Tag msgTag);
	void freeMessage(Message *msg);

	void send(Message* msg, NodeId node);
	void sendAndFree(Message* msg, NodeId node);

	bool doSend();
	void checkAll();
};

}
