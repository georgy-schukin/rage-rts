#include "taskpool.h"

namespace fprts {

void SimpleTaskPool::Add(int t_num, const list<CompFragment*> &cfs) {
	tasks.insert(tasks.end(), cfs.begin(), cfs.end());
}

bool SimpleTaskPool::Get(int t_num, list<CompFragment*> &cfs, int max_sz) {
	if(tasks.empty()) return false;
	for(int i = 0;!tasks.empty() && (i < max_sz);i++) {
		cfs.push_back(tasks.front());
		tasks.pop_front();
	}
return true;
}

}