#pragma once

#include "types.h"
#include "icommunicator.h"
#include "icommsystem.h"
#include "messagestorage.h"
#include "topology.h"
#include <boost/shared_ptr.hpp>
#include <list>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

using namespace std;

namespace rage {

class Task;
class DataObject;

class CommSystem : public ICommSystem // high-level system for send/recv fragments and other info between nodes
{
protected:
	ICommunicator *communicator;
	boost::shared_ptr<MessageStorage> messageStorage;	

	boost::thread sendThread, recvThread;
	boost::mutex msMutex;

	volatile bool isWorking;

	Topology topology;

	list<ICommListener*> commListeners;

protected:
	void sendFunc();
	void recvFunc();

	void onMessage(Message *msg);	

public:
	CommSystem() : isWorking(false) {}
	~CommSystem() {}

	void setCommunicator(ICommunicator *communicator) {
		this->communicator = communicator;
	}

	ICommunicator* getCommunicator() const {
		return communicator;
	}

	void addCommListener(ICommListener *listener) {
		commListeners.push_back(listener);
	}

	void sendTask(Task *task, NodeId node);
	void sendData(DataObject *data, NodeId node);	
	
	void init(Topology::Type tp); // init comm, etc
	void finalize(); // finalize comm, etc

	void start();
	void stop();
};

}
