#pragma once

#include "types.h"
#include <vector>

using namespace std;

namespace rage {

class CodeLibrary;
class CodeArgs;
class DataObject;

class CodeObject // code entity
{
public:	
	vector<string> paramNames; // names of formal params
	vector<string> argNames; // names of formal args

protected:
	void addArg(const string& name) {
		argNames.push_back(name);
	}

	void addParam(const string& name) {
		paramNames.push_back(name);
	}

	DataObject* getArg(const CodeArgs& args, unsigned int ind);
	int getParam(const CodeArgs& args, unsigned int ind);

protected:
	friend class CodeLibrary;

	virtual void init(CodeLibrary *lib) = 0; // init params, code, etc.	

public:		
	virtual bool isAtomic() const = 0;

	const vector<string>& getArgs() const {
		return argNames;
	}
};

}
