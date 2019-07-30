#include "message.h"

namespace rage {

/*Message& operator << (Message& msg, const ProcedureId& id) {
	msg << id.first << id.second;
return msg;
}

Message& operator >> (Message& msg, ProcedureId& id) {
	msg >> id.first >> id.second;
return msg;
}*/

/*Message& operator << (Message &msg, const FragmentIdSet &ids) {
	unsigned int size = ids.size();
		msg << size;
	for(FragmentIdSet::const_iterator it = ids.begin();it != ids.end();it++) {
		msg << *it;
	}
return msg;
}

Message& operator >> (Message &msg, FragmentIdSet &ids) {
	unsigned int size;
	FragmentId id;
		msg >> size;
	for(unsigned int i = 0;i < size;i++) {
		msg >> id;
		ids.insert(id);
	}
return msg;
}*/

Message& operator << (Message& msg, const vector<int>& v) {	
	msg.writeScalar<unsigned int>(v.size());
	for(vector<int>::const_iterator it = v.begin();it != v.end();it++) {
		msg.writeScalar<int>(*it);
	}
return msg;
}

Message& operator >> (Message& msg, vector<int>& v) {
	unsigned int size = msg.readScalar<unsigned int>();			
	for(unsigned int i = 0;i < size;i++) {
		v.push_back(msg.readScalar<int>());
	}
return msg;
}

}
