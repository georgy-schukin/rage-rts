#include "messagestorage.h"
#include "exception.h"

namespace rage {

void MessageStorage::alloc(unsigned int size, unsigned int msgSize) {	
	for(unsigned int i = 0;i < size;i++) {
		messages.push_back(boost::shared_ptr<Message>(new Message(messages.size(), msgSize))); // msg id = msg index in vector
		flags.push_back(true);
	}
}

void MessageStorage::clear() {
	messages.clear();
	flags.clear();
}

Message* MessageStorage::getMessage() {
	for(unsigned int i = 0;i < flags.size();i++) { // search free message
		if(flags[i]) {
			flags[i] = false;
			Message *msg = messages[i].get();
				msg->reset();
			return msg;
		}
	}
	boost::shared_ptr<Message> newMessage(new Message(messages.size(), msgDefaultSize)); // create new message
		messages.push_back(newMessage); // add as not free
		flags.push_back(false); // already busy
return newMessage.get();
}

Message* MessageStorage::getMessage(unsigned int id) {
	if(id >= messages.size())
		throw Exception("Wrong message id");	
return messages[id].get();
}

void MessageStorage::freeMessage(Message* msg) {
	if(msg->getId() >= flags.size())
		throw Exception("Wrong message id");	
	flags[msg->getId()] = true; 	
}

void MessageStorage::freeMessage(unsigned int id) {
	if(id >= flags.size())
		throw Exception("Wrong message id");
	flags[id] = true;	
}

}