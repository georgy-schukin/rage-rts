#pragma once

#include "codeobject.h"
#include "idgen.h"

#include <boost/ptr_container/ptr_map.hpp>
#include <string>

using namespace std;

namespace rage {

class CodeLibrary // storage of code fragments
{
protected:
	boost::ptr_map<CodeId, CodeObject> codeObjects;

protected:
	void addCode(CodeId codeId, CodeObject *codeObject);
	
public:
	CodeLibrary() {}
	~CodeLibrary() {}

	static CodeId getId(const string& name) { // get id by name
		return IdGenerator::generateId(name);
	}

	template<class T> CodeId add(const string &name) { // add object to library
		CodeId codeId = getId(name);
		if(codeObjects.find(codeId) == codeObjects.end())
			addCode(codeId, new T());
		return codeId;
	}

	CodeObject* get(CodeId id) { // get code object by id
		boost::ptr_map<CodeId, CodeObject>::iterator it = codeObjects.find(id);
		return (it != codeObjects.end()) ? it->second : 0;
	}

	CodeObject* get(const string& name) {
		return get(getId(name));
	}
};

}
