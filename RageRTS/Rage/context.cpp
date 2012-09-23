#include "context.h"

namespace fprts {

void InputArgContext::Pack(Message &msg) const {	
	msg << (unsigned int)args.size();
	for(vector<InputArgContext::Arg>::const_iterator it = args.begin();it != args.end();it++) 
		msg << (*it).id << (*it).local;		
	msg << params;
}

void InputArgContext::Unpack(Message &msg) {
	unsigned int size;	
	msg >> size;
	args.resize(size);	
	for(unsigned int i = 0;i < size;i++) {
		msg >> args[i].id >> args[i].local;		
	}
	msg >> params;
}

}