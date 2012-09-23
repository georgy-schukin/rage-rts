#include "mpicomm.h"
#include "rage.h"
#include "tasks.h"
#include "code.h"

namespace rage {

void Rage::init(Topology::Type tp) {
	//comm_system.SetExecSystem(&exec_system);

	//exec_system.SetCommSystem(&comm_system);
	//exec_system.SetCodeLibrary(&code_lib);
	//exec_system.SetScheduler(&sched);
	//exec_system.SetDistributor(&distr);

	//comm_system.Init(tp); // init communicator
	//exec_system.Init();
	communicator.reset(new MPICommunicator(tp));	

	execSystem.reset(new ExecSystem());
	commSystem.reset(new CommSystem());	
		
	execSystem->SetCommSystem(commSystem.get());
	execSystem->setCodeLibrary(&codeLibrary);

	commSystem->setCommunicator(communicator.get());
	commSystem->addCommListener(execSystem.get());
}

void Rage::start(int threadsNum) {
	execSystem->start(threadsNum); // start exec threads
	commSystem->start(); // start comm threads	
}

void Rage::stop() {
	execSystem->stop(); // wait for stop
	commSystem->stop(); // stop comm
}

void Rage::finalize() {	
	//comm_system.Finalize();
	//exec_system.Finalyze();
}

void Rage::loadProgram(NodeId node, CodeId codeId, vector<int>& params) { // load main program for exec
	NodeId thisNode = commSystem->getCommunicator()->getRank();
	if(node == thisNode) {
		CodeObject *code = codeLibrary.get(codeId);
		if(code->isAtomic())
			throw Exception("Only structured code objects are allowed for loading");
		list<Task*> tasks;
		tasks.push_back(new AtomicTask(((StructuredCodeObject*)code)->getCodeTree()->getRoot()));
		execSystem->onTasksSpawn(tasks);
	}
}

}
