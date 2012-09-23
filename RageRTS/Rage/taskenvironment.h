#pragma once

#include "types.h"
#include <boost/shared_ptr.hpp>
#include "task.h"
#include "dataobject.h"
#include <list>
#include <map>
#include <vector>
#include <string>
#include <boost/ptr_container/ptr_map.hpp>

using namespace std;

namespace rage {

class TaskEnvironment
{	
protected:
	Task *parent;	
	boost::ptr_map<string, DataObject> dataStorage; // storage for local data
	map<string, DataObject*> datas; // local data + args
	map<string, int> values; // params + consts
	
public:	
	TaskEnvironment(Task *p) : parent(p) {}
	~TaskEnvironment() {}

	void setParent(Task *parent) {
		this->parent = parent;
	}

	Task* getParent() const {
		return parent;
	}

	void addData(const string& name, DataObject *data, bool local = true) {		
		if(local) { // add local data
			data->setName(name); // reset data name
			dataStorage.insert(string(name), data); // add to local storage
		}		
		datas[name] = data; 
	}

	void addValue(const string& name, int value) {
		values[name] = value;
	}

	void removeData(const string& name) {
		dataStorage.erase(name);
		datas.erase(name);
	}

	bool dataExists(const string& name) {
		return (datas.find(name) != datas.end());			
	}

	bool valueExists(const string& name) {
		return (values.find(name) != values.end());
	}

	DataObject* getData(const string& name) {
		map<string, DataObject*>::iterator it = datas.find(name);
		return (it != datas.end()) ? it->second : 0;
	}

	int getValue(const string& name) {
		map<string, int>::iterator it = values.find(name);
		return (it != values.end()) ? it->second : 0;
	}

	void addDatas(const map<string, DataObject*>& src, bool local = true);
	void addValues(const map<string, int>& src);

	void getDatas(map<string, DataObject*>& res) const;
	void getValues(map<string, int>& res) const;

	void copyAllTo(TaskEnvironment *dst) const; // copy all data and vals to env
	//void copyAllFrom(TaskEnvironment *src); // copy all data and vals from env

	//void copyAllData(TaskEnvironment *dst); // copy all data by refs
	//void copyAllValues(TaskEnvironment *dst); // copy all values
		
	/*void OnInit(); // init proc on node (find free and ready cfs, etc.)

	void OnNewDF(const FragmentGraph::DFVertex &dv, DataFragment *df);	 // when add df from another node
	void OnNewDFs(const DFList &dfs); // when add dfs from another nodes
	void OnNewCF(const FragmentGraph::CFVertex &cv); // when add cf from another node
	void OnNewCFs(const CFList &cfs); // when add cfs from another nodes
	void OnNewGraph(const FragmentGraph &graph); // when new vertices (dfs and cfs) arrived

	void OnCFStart(CompFragment *cf); // mark cf as executing
	void OnCFDone(CompFragment *cf, CFDepMap &cf_deps); // mark cf as finished
	void OnCFDepend(const CFDepMap &cf_deps, CFDepMap &remote_cf_deps); // decrease deps for cfs

	void OnDFsMigrate(const FragmentIdSet &df_ids); 
	void OnCFsMigrate(const FragmentIdSet &cf_ids);
	
	void OnSchedule(const list<FragmentId> &cf_ids, list<CompFragment*> &res); // create cfs for scheduled tasks

	void PopDFRequests(FragmentIdSet &req_dfs);

	bool RequestDFs(const FragmentIdSet &df_ids, DFList &dfs, FragmentIdSet &rest);

	bool IsDone(); // check if proc is done	
	bool IsEmpty(); // check if there are no cfs in proc

	FragmentGraph& GetGraph() {return fg;}
	FragmentStorage& GetStorage() {return fs;}
	const FragmentIdSet& GetReadyCFs() const {return ready_cfs;}*/
};

}
