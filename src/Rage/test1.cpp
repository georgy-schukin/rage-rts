#include "test1.h"
#include <boost/assign/std/vector.hpp>

using namespace boost::assign;

namespace test1 {

void CodeInit::init(CodeLibrary *lib) {
	addArg("num");
}

void CodeInit::exec(const CodeArgs& args) {
	*(int*)getArg(args, 0) = 5;
}

void CodeInc::init(CodeLibrary *lib) {
	addArg("num");
}

void CodeInc::exec(const CodeArgs& args) {	
	*(int*)getArg(args, 0) += 2;
}

void CodePrint::init(CodeLibrary *lib) {
	addArg("num");
}

void CodePrint::exec(const CodeArgs& args) {
	printf("Number: %d\n", *(int*)getArg(args, 0));
}

void Test1::init(CodeLibrary *lib) {
//	addParam("cnt");
	lib->add<CodeInit>("Init");
	lib->add<CodeInc>("Inc");
	lib->add<CodePrint>("Print");
}

void dt_param_func(const CodeArgs& args, vector<int>& out) {
	out.push_back(sizeof(int));
}

void arg_func(const CodeArgs& args, CodeArgs& out) {
	out.setData("num", args.getData("a"));
}

void Test1::buildTree(CodeTree *tree, CodeLibrary *lib) {
	BlockVertex *block = new BlockVertex(BlockVertex::SEQ); // block of seq code
	tree->setRoot(block);

	DataVertex *dt = new DataVertex("a", DataVertex::BLOCK, dt_param_func);	
	CallVertex* c1 = new CallVertex(lib->get("Init"), arg_func);
		c1->addDataReq("a");		
	CallVertex* c2 = new CallVertex(lib->get("Print"), arg_func);
		c2->addDataReq("a");	
	CallVertex* c3 = new CallVertex(lib->get("Inc"), arg_func);
		c3->addDataReq("a");	
	CallVertex* c4 = new CallVertex(lib->get("Print"), arg_func);
		c4->addDataReq("a");		

	block->addChild(dt);
	block->addChild(c1);
	block->addChild(c2);
	block->addChild(c3);	
	block->addChild(c4);	
}

}
