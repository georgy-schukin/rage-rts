#pragma once

#include "types.h"
#include <string>

using namespace std;

namespace rage {

class TaskEnvironment;

class DataObject
{
public:
	enum Type
	{
		ATOMIC = 0,
		STRUCT,
		ARRAY
	};

protected:	
	DataId dataId;
	string dataName; // name of data in environment
	TaskEnvironment *environment; // parent environment

public:
	DataObject() : dataId(0), dataName("") {}
	DataObject(const string& name) : dataName(name), dataId(0) {}
	~DataObject() {}	

	void setId(DataId dataId) {
		this->dataId = dataId;
	}

	DataId getId() const {
		return dataId;
	}

	void setEnvironment(TaskEnvironment *env) {
		this->environment = env;
	}

	TaskEnvironment* getEnvironment() const {
		return environment;
	}

	void setName(const string& name) {
		this->dataName = name;
	}

	const string& getName() const {
		return dataName;
	}

	virtual DataObject::Type getType() const = 0;
	virtual void* getData() const = 0;
	virtual void create() = 0;
};

}
