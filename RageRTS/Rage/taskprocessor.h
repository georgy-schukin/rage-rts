#pragma once

#include "task.h"
#include "codeargs.h"
#include <list>

using namespace std;

namespace rage {

class BlockVertex;
class CallVertex;
class CondVertex;
class IndexedVertex;
class WhileVertex;
class DataVertex;

class TaskProcessor
{
protected:
	static void processData(DataVertex *v, Task *task, const CodeArgs& args, list<DataObject*>& out);
	static void processCall(CallVertex *v, Task *task, const CodeArgs& args, list<Task*>& out);
	static void processBlock(BlockVertex *v, Task *task, const CodeArgs& args, list<Task*>& out);
	static void processCond(CondVertex *v, Task *task, const CodeArgs& args, list<Task*>& out);
	static void processIndexed(IndexedVertex *v, Task *task, const CodeArgs& args, list<Task*>& out);	
	static void processWhile(WhileVertex *v, Task *task, const CodeArgs& args, list<Task*>& out);

	static void prepareArgs(Task *task, CodeArgs& args);

public:
	static void processTask(Task *task, list<Task*>& tasks, list<DataObject*>& datas); // exec task
};

}
