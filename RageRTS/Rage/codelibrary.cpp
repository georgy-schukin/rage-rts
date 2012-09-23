#include "codelibrary.h"
#include "structuredcodeobject.h"

namespace rage {

void CodeLibrary::addCode(CodeId codeId, CodeObject *codeObject) {
	codeObjects.insert(codeId, codeObject);
	codeObject->init(this); // init object (args, etc)
	if(!codeObject->isAtomic()) {
		((StructuredCodeObject*)codeObject)->build(this); // build code tree for structured object
		((StructuredCodeObject*)codeObject)->getCodeTree()->processVertices(); // process vertices in code tree
	}
}

}
