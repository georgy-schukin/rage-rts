#include "code.h"

using namespace rage;

namespace test1 {

class CodeInit : public AtomicCodeObject
{
protected:
	void init(CodeLibrary *lib);

public:
	CodeInit() {}
	~CodeInit() {}
	
	void exec(const CodeArgs& args);
};

class CodeInc : public AtomicCodeObject
{
protected:
	void init(CodeLibrary *lib);

public:
	CodeInc() {}
	~CodeInc() {}
	
	void exec(const CodeArgs& args);
};

class CodePrint : public AtomicCodeObject
{
protected:
	void init(CodeLibrary *lib);

public:
	CodePrint() {}
	~CodePrint() {}
	
	void exec(const CodeArgs& args);
};

class Test1 : public StructuredCodeObject
{
protected:
	void init(CodeLibrary *lib);		
	void buildTree(CodeTree *tree, CodeLibrary *lib);

public:
	Test1() {}
	~Test1() {}	
};

}
