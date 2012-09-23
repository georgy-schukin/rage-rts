#pragma once

#include <vector>
#include <map>
#include <string>
#include <list>

using namespace std;

namespace rage {

class DataObject;

class CodeArgs
{
protected:
	map<string, int> values;
	map<string, DataObject*> datas;

public:
	CodeArgs() {}
	~CodeArgs() {}

	void setValue(const string& name, int value) {
		values[name] = value;
	}

	void setData(const string& name, DataObject *data) {
		datas[name] = data;
	}

	int getValue(const string& name) const {
		return values.find(name)->second;
	}

	DataObject* getData(const string& name) const {
		return datas.find(name)->second;
	}

	void getDatas(map<string, DataObject*>& res) const {
		res = datas;
	}

	void getValues(map<string, int>& res) const {
		res = values;
	}
};

}
