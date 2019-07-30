#include "codetree.h"
#include "compvertex.h"
#include <boost/foreach.hpp>

namespace rage {

void CodeTree::processVertices() {
	int currId = 0;
	processVertex(getRoot(), currId);
}

void CodeTree::processVertex(CodeVertex *v, int& currId) {
	v->setId(currId); // set vertex id
	v->setCodeTree(this); // link vertex to tree
	currId++; // inc id for further vertices

	if(v->getType() == CodeVertex::COMP) { // vertex has children		
		BOOST_FOREACH(CodeVertex *el, ((CompVertex*)v)->getChildren()) {
			processVertex(el, currId); // process children
		}
	}
}

}