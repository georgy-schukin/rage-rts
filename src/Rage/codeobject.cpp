#include "codeobject.h"
#include "codeargs.h"
#include "dataobject.h"
#include "exception.h"

namespace rage {

DataObject* CodeObject::getArg(const CodeArgs& args, unsigned int ind) {
	if(ind >= argNames.size())
		throw Exception("Bad argument index");
	return args.getData(argNames[ind]);
}

int CodeObject::getParam(const CodeArgs& args, unsigned int ind) {
	if(ind >= paramNames.size())
		throw Exception("Bad parameter index");
	return args.getValue(paramNames[ind]);
}

}
