#include "mpicomm.h"
#include "messagesystem.h"

#include <list>

namespace rage {

void MessageSystem::init(unsigned int size, unsigned int msgSize) {
	storage = new MessageStorage(size, msgSize);
}

Message* MessageSystem::getMessage(Message::Tag msgTag) {
	boost::unique_lock<boost::mutex> lock(mutex);
	Message *msg = storage->getMessage();
	msg->setTag(msgTag);
	access[msg->getId()] = 0; // init for new message
return msg;
}

void MessageSystem::freeMessage(Message *msg) {
	boost::unique_lock<boost::mutex> lock(mutex);
	unsigned int id = msg->getId();
	if(access[id] == 0) { // msg is not used anymore
		storage->freeMessage(id); // free it
	} else {
		free_flg.insert(id); // set flg to free later
	}
}

void MessageSystem::send(Message *msg, NodeId node) { // send msg
	boost::unique_lock<boost::mutex> lock(mutex);
	unsigned int id = msg->getId();
	tasks.push(pair<unsigned int, NodeId>(id, node)); // push msg in queue to send later
	access[id]++;
}

void MessageSystem::sendAndFree(Message *msg, NodeId node) {
	boost::unique_lock<boost::mutex> lock(mutex);
	unsigned int id = msg->getId();
	tasks.push(pair<unsigned int, NodeId>(id, node)); // push msg in queue to send later
	access[id]++;
	free_flg.insert(id); // set flg to free later
}

bool MessageSystem::doSend() { // do next send task
	boost::unique_lock<boost::mutex> lock(mutex);

	if(tasks.empty()) return false;
	
	unsigned int id = tasks.front().first;
	NodeId node = tasks.front().second;
	tasks.pop();
	
	Message *msg = storage->getMessage(id);	
	int r_id;
		communicator->isend(msg->getBuffer(), msg->getSize(), (int)msg->getTag(), node, r_id); // send
	isends[r_id] = id;
return true;
}

void MessageSystem::checkAll() { // check for finished sends
	boost::unique_lock<boost::mutex> lock(mutex);
	list<int> completed;
	for(map<int, unsigned int>::const_iterator it = isends.begin();it != isends.end();it++) { // for all ongoing isends
		unsigned int id = it->second;
		if(communicator->test(it->first)) { // send is completed
			access[id]--;
			if((access[id] == 0) && (free_flg.find(id) != free_flg.end())) { // msg isn't used anymore and can be freed
				storage->freeMessage(id);
				free_flg.erase(id);
			}			
			completed.push_back(it->first);
		}		
	}
	for(list<int>::const_iterator it = completed.begin();it != completed.end();it++) isends.erase(*it);	
}
}