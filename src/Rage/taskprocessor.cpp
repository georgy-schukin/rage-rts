#include "taskprocessor.h"
#include "code.h"
#include "data.h"
#include "tasks.h"
#include "exception.h"
#include <boost/foreach.hpp>

namespace rage {

void TaskProcessor::processTask(Task *task, list<Task*>& tasks, list<DataObject*>& datas) { // process atomic task
	if(task->getType() != Task::ATOMIC)
		throw Exception("Nonatomic task");

	CodeArgs args;
	prepareArgs(task, args); // get args for task

	CodeVertex *v = task->getSource();
	if(v->getType() == CodeVertex::DATA) { // it's data vertex
		processData((DataVertex*)v, task, args, datas);
	}
	else { // it's comp vertex
		switch(((const CompVertex*)v)->getCompType()) {
			case CompVertex::CALL: 
				processCall((CallVertex*)v, task, args, tasks);
				break;
			case CompVertex::BLOCK: 
				processBlock((BlockVertex*)v, task, args, tasks);
				break;
			case CompVertex::COND: 
				processCond((CondVertex*)v, task, args, tasks);
				break;
			case CompVertex::RANGE: 
				processIndexed((IndexedVertex*)v, task, args, tasks);
				break;
			case CompVertex::WHILE: 
				processWhile((WhileVertex*)v, task, args, tasks);
				break;
			default:
				throw Exception("Unknown task type");
		}
	}
}

void TaskProcessor::processCall(CallVertex *v, Task *task, const CodeArgs &args, list<Task*>& out) {
	unsigned int i = 0;	
	CodeArgs codeArgs;
	CodeObject *code = v->getCodeObject();	
	BOOST_FOREACH(const string& arg, code->getArgs()) {
		codeArgs.setData(arg, args.getData(v->getArg(i++)->evalData(args))); // FIX?!!
	}	
	//v->getArgFunc()(args, codeArgs); // prepare args for code
	if(code->isAtomic()) { // code is atomic
		((AtomicCodeObject*)code)->exec(codeArgs); // exec task		
	} else { // code is structured
		AtomicTask *t = new AtomicTask(task, ((StructuredCodeObject*)code)->getCodeTree()->getRoot());
		t->setEnvironment(new TaskEnvironment(t)); // create new env for call
			map<string, DataObject*> callDatas;
			map<string, int> callValues;
				codeArgs.getDatas(callDatas); // get data from args
				codeArgs.getValues(callValues);
			t->getEnvironment()->addDatas(callDatas); // add data to new environemnt
			t->getEnvironment()->addValues(callValues);
		out.push_back(t);		
	}
}

void TaskProcessor::processData(DataVertex *v, Task *task, const CodeArgs &args, list<DataObject*>& out) {	
	//vector<int> params;	
	//v->getParamFunc()(args, params); // compute params from args
	switch(v->getDataType()) {
		case DataVertex::BLOCK: {
			//if(params.empty())
			//	throw Exception("Need size param for data block");	
			DataObject* data = new DataBlock(v->getDataName(), v->getDataSize());
			data->setEnvironment(task->getEnvironment());
			out.push_back(data);
			//task->getEnvironment()->addData(data->getName(), data);
		}
	}
}

void TaskProcessor::processBlock(BlockVertex *v, Task *task, const CodeArgs &args, list<Task*>& out) {		
	vector<Task*> tasks;
	BOOST_FOREACH(CodeVertex *el, v->getChildren()) { // create tasks for block elems
		tasks.push_back(new AtomicTask(task, el));
	}	

	if(v->getOrderType() == BlockVertex::SEQ) { // prepare seq block
		for(unsigned int i = 0; i < tasks.size() - 1;i++) // set additional dependencies
			tasks[i]->addDepTask(tasks[i + 1]);			
	}		

	out.insert(out.end(), tasks.begin(), tasks.end());
}

void TaskProcessor::processCond(CondVertex *v, Task *task, const CodeArgs &args, list<Task*>& out) {		
	//if(!v->getCondFunc()) 
	//	throw Exception("Empty cond func");
	bool result = v->getCondExpr()->evalBoolean(args); // compute condition
	if(result) { // cond is true
		out.push_back(new AtomicTask(task, v->getChild(0))); // spawn 'if' statement
	} else { // cond is false				
		if(v->getChildrenNum() > 1) { // there is 'else' statement					
			out.push_back(new AtomicTask(task, v->getChild(1)));
		} 
	}
}

void TaskProcessor::processIndexed(IndexedVertex *v, Task *task, const CodeArgs &args, list<Task*>& out) {	
	//if(!v->getCycleFunc()) 
	//	throw Exception("Empty cycle func");
	//vector<int> params;	
	//	v->getCycleFunc()(args, params); // compute params from args
	//if(params.size() < 3) 
	//	throw Exception("Need more range params");
	int begin = v->getBeginExpr()->evalInt(args);
	int end = v->getEndExpr()->evalInt(args);
	int step = v->getStepExpr()->evalInt(args);
	RangedTask *t = new RangedTask(task, v->getChild(0));
		t->setIndexName(v->getIndexName());
		t->setRange(begin, end, step);
	out.push_back(t);
}

void TaskProcessor::processWhile(WhileVertex *v, Task *task, const CodeArgs &args, list<Task*>& out) {	
	//if(!v->getCondFunc()) 
	//	throw Exception("Empty cond func");
	bool result = v->getCondExpr()->evalBoolean(args); // compute condition
	if(result) { // cond is true
		out.push_back(new AtomicTask(task, v->getChild(0))); // spawn while body
	}		
}

void TaskProcessor::prepareArgs(Task *task, CodeArgs& args) {
	TaskEnvironment *env = task->getEnvironment();
	BOOST_FOREACH(const string& name, task->valueReqs) {
		args.setValue(name, env->getValue(name));
	}
	BOOST_FOREACH(const string& name, task->dataReqs) {
		args.setData(name, env->getData(name));
	}
}

}
