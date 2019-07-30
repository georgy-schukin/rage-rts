#pragma once

#include "loadcollector.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

namespace rage {

class LoadLogger // to write log info in file
{
protected:
	ofstream out; // output stream
public:
	LoadLogger() {}
	LoadLogger(const string &file) {Open(file, false);}
	~LoadLogger() {Close();}

	int Open(const string &file, bool app = false);
	int Close();

	void Log(NodeId node, double time, const LoadCollector::LoadInfo &info);
};

}