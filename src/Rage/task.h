#pragma once

#include "types.h"
#include <list>
#include <vector>

using namespace std;

namespace rage {

class CodeVertex;
class TaskEnvironment;

class Task
{
public:
	enum Type
	{
		ATOMIC = 0,		
		RANGED
	};
	enum State
	{
		UNREADY = 0,
		VALIDATED,
		READY,
		RUNNING,
		DONE
	};

protected:
	TaskId taskId;
	Task *parent; // parent task
	CodeVertex *source; // code to exec
	TaskEnvironment *environment; // environment of task	
	Task::State state; // state of task
	unsigned int depCnt;
	list<Task*> depTasks; // dependent tasks
	
public:
	int weight;
	vector<string> dataReqs; // data objects needed to exec
	vector<string> valueReqs; // values needed to exec

public:
	Task() : taskId(0), parent(0), source(0), environment(0), state(Task::UNREADY), depCnt(0) {}
	Task(CodeVertex *src) : taskId(0), parent(0), source(src), environment(0), state(Task::UNREADY), depCnt(0) {}
	Task(Task *p) : taskId(0), parent(p), source(0), environment(0), state(Task::UNREADY), depCnt(0) {
		addDepTask(p);
	}
	Task(Task *p, CodeVertex *src) : taskId(0), parent(p), source(src), environment(0), state(Task::UNREADY), depCnt(0) {
		addDepTask(p);
	}
	Task(Task *p, CodeVertex *src, TaskEnvironment *env) : taskId(0), parent(p), source(src), environment(env), state(Task::UNREADY), depCnt(0) {
		addDepTask(p);
	}
	~Task() {}

	void setId(TaskId taskId) {
		this->taskId = taskId;
	}

	TaskId getId() const {
		return taskId;
	}

	void setSource(CodeVertex *source) {
		this->source = source;
	}

	CodeVertex* getSource() const {
		return source;
	}	

	void setEnvironment(TaskEnvironment *environment) {
		this->environment = environment;
	}

	TaskEnvironment* getEnvironment() const {
		return environment;
	}

	void setParent(Task *parent) {
		this->parent = parent;
	}

	Task* getParent() const {
		return parent;
	}

	void setState(Task::State state) {
		this->state = state;
	}

	Task::State getState() const {
		return state;
	}

	unsigned int changeDependencyCount(int cnt) {
		depCnt += cnt;
		return depCnt;
	}

	unsigned int getDependencyCount() const {
		return depCnt;
	}	

	/*void changeChildrenCount(int cnt) {
		childCnt += cnt;	
	}

	unsigned int getChildrenCount() const {
		return childCnt;
	}*/

	void addDepTask(Task *task) {
		task->changeDependencyCount(1); // inc dep count
		depTasks.push_back(task);
	}

	const list<Task*>& getDepTasks() {
		return depTasks;
	}

	virtual Task::Type getType() const = 0;
};

}
