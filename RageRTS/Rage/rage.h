#pragma once

#include "types.h"
#include "execsystem.h"
#include "commsystem.h"
#include "codelibrary.h"
#include "taskmanager.h"
#include "taskexecutor.h"
#include <boost/scoped_ptr.hpp>

namespace rage {

class Rage
{
protected:	
	boost::scoped_ptr<ICommunicator> communicator;
	boost::scoped_ptr<ExecSystem> execSystem;
	boost::scoped_ptr<CommSystem> commSystem;
	CodeLibrary codeLibrary;

public:
	Rage() {}
	~Rage() {}

	template<class T>
	CodeId registerCode(const string &name); // reg code for call

	void loadProgram(NodeId node, CodeId codeId, vector<int>& params); // load main program for exec

	void init(Topology::Type tp = Topology::ALL_TO_ALL);
	void finalize();	

	void start(int threadsNum);	
	void stop();
};

template<class T>
CodeId Rage::registerCode(const string &name) { // reg code for call
	return codeLibrary.add<T>(name);
}

}
