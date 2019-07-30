#include "compvertex.h"
#include <boost/foreach.hpp>

namespace rage {

void CompVertex::addChild(CodeVertex *vertex) {
	childrenStorage.push_back(vertex);	
	children.push_back(vertex);
	vertex->setParent(this);
}

}
