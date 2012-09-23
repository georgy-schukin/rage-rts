#include "loadlogger.h"
#include <sstream>
#include <iomanip>

namespace rage {

int LoadLogger::Open(const string &file, bool app) {
	if(out.is_open()) out.close(); // close stream if open
		out.open(file.c_str(), ios::out | (app ? ios::app : ios::trunc));
	if(!out.is_open()) return -1;
return 0;
}

int LoadLogger::Close() {
	if(!out.is_open()) return -1;
		out.close();
return 0;
}

void LoadLogger::Log(NodeId node, double time, const LoadCollector::LoadInfo &info) {
	std::stringstream out_s;
	out_s << fixed << time << " : ";
	out_s << node << " : ";	
	out << out_s.str() << endl;
}

}