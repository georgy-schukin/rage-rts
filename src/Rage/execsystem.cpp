#include "execsystem.h"
#include "commsystem.h"
#include "codelibrary.h"
//#include <boost/lambda/lambda.hpp>
//#include <boost/bind.hpp>
//#include <boost/range/adaptor/map.hpp>
//#include <boost/range/algorithm/copy.hpp>
#include <boost/foreach.hpp>
//#include <algorithm>

namespace rage {	

void ExecSystem::start(int threadsNum) {
	taskManager.reset(new TaskManager());
	taskExecutor.reset(new TaskExecutor());	

	taskExecutor->addExecListener(this);
	taskManager->addManageListener(this);

	isWorking = true;
	taskManager->start();
	taskExecutor->start(threadsNum);
}

void ExecSystem::stop() {	
	isWorking = false;
	taskManager->stop();
	taskExecutor->stop();
}

void ExecSystem::onTaskReady(Task *task) { // task is ready 
	taskExecutor->scheduleTask(task); // sched to run it on exec thread
}

void ExecSystem::onTaskStart(Task *task) {
}

void ExecSystem::onTaskDone(Task *task) { // when task is finished	
	taskManager->removeTask(task); // delete task
}

void ExecSystem::onTasksSpawn(list<Task*>& tasks) { // new tasks are spawned by executor
	taskManager->addTasks(tasks); // pass them to manager
}

void ExecSystem::onDatasSpawn(list<DataObject*>& datas) {
	taskManager->addDatas(datas);
}

void ExecSystem::onTaskAdded(Task *task) { // task is added to manager
	taskExecutor->executeTask(task); // pass it to executor
}

void ExecSystem::onTaskDeleted(Task *task) {
}

void ExecSystem::onTaskMigrated(Task *task) {
}

void ExecSystem::onTaskRecv(Task *task) {
	taskManager->addTask(task);
}

void ExecSystem::onDataRecv(DataObject *object) {
}

/*bool ExecSystem::IsFinished() {
return true;
}*/

}
 