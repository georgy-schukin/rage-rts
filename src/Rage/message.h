#pragma once

#include "types.h"
#include "rwbuffer.h"

#include <vector>

using namespace std;

namespace rage {

class Message : public ReadWriteBuffer // message - buffer of data
{
public:
	enum Tag
	{
		NONE = 0,
		TASK,			// send dfs
		DATA/*,			// send cfs
		GRAPH,	
		CF_DEPEND,
		PROC_DONE,
		DF_LOCATION,
		CF_LOCATION,
		DF_REQUEST*/
	};

protected:	
	unsigned int msgId; // some id of message
    Message::Tag msgTag; // tag of message

public:    
    Message() : msgId(0), msgTag(Message::NONE) {}	
	Message(unsigned int id, unsigned int size) : msgId(id), msgTag(Message::NONE) {
		resize(size);
	}    		
    ~Message() {}    
	
	void setId(unsigned int id) {
		msgId = id;
	}

	unsigned int getId() const {
		return msgId;
	}	

	void setTag(Message::Tag tag) {
		msgTag = tag;
	} 	
	
	Message::Tag getTag() const {
		return msgTag;
	}
};

//Message& operator << (Message& msg, const ProcedureId& id);
//Message& operator >> (Message& msg, ProcedureId& id);

//Message& operator << (Message& msg, const FragmentIdSet &ids);
//Message& operator >> (Message& msg, FragmentIdSet &ids);

Message& operator << (Message& msg, const vector<int>& v);
Message& operator >> (Message& msg, vector<int>& v);

}
