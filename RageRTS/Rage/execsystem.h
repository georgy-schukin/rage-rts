#pragma once

#include "codelibrary.h"
#include "itaskexecutor.h"
#include "itaskmanager.h"
#include "taskmanager.h"
#include "taskexecutor.h"
#include "icommsystem.h"
#include <list>
#include <boost/scoped_ptr.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

using namespace std;

namespace rage {

class ExecSystem : public ITaskListener, ICommListener // exec subsystem on a node to run fragments
{
protected:	
	boost::scoped_ptr<ITaskManagerService> taskManager;
	boost::scoped_ptr<ITaskExecutorService> taskExecutor;	
	ICommSystem *commSystem;
	CodeLibrary *codeLibrary;

	//boost::shared_ptr<ExecThreadPool> execThreadPool;
	
	//LoadCollector load_collector;

	//map<ProcedureId, FragmentLocationStorage> fls; // locations	

	volatile bool isWorking;

	//boost::mutex proc_mutex, sched_mutex, tp_mutex, lc_mutex;
	
	boost::thread load_thread;

protected:	
	//void LoadFunc(); // check for completion, gather load info

public:
	void onTaskReady(Task *task);
	void onTaskStart(Task *task);
	void onTaskDone(Task *task);	
	void onTasksSpawn(list<Task*>& tasks);
	void onDatasSpawn(list<DataObject*>& datas);

	void onTaskAdded(Task *task);	
	void onTaskDeleted(Task *task);
	void onTaskMigrated(Task *task);

	void onTaskRecv(Task *task);
	void onDataRecv(DataObject *object);

	//bool IsFinished();

protected:
	friend class Rage;

	void SetCommSystem(ICommSystem *commSystem) {
		this->commSystem = commSystem;
		commSystem->addCommListener(this);
	}	

	/*void setTaskManager(ITaskManager *taskManager) {
		this->taskManager = taskManager;
		taskManager->addManageListener(this);
	}

	void setTaskExecutor(ITaskExecutor *taskExecutor) {
		this->taskExecutor = taskExecutor;
		taskExecutor->addExecListener(this);
	}*/

	void setCodeLibrary(CodeLibrary *codeLibrary) {
		this->codeLibrary = codeLibrary;
	}

public:
	ExecSystem() : isWorking(false) {}
	~ExecSystem() {}

	//void init();
	//void finalyze();

	void start(int threadsNum); // start threads
	void stop(); // wait for completion	

	NodeId thisNode() const;
};

}
