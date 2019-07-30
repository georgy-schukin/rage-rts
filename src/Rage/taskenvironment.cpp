#include "taskenvironment.h"
#include <boost/foreach.hpp>

namespace rage {

void TaskEnvironment::addDatas(const map<string, DataObject*>& src, bool local) {
	typedef map<string, DataObject*>::value_type ValType;
	BOOST_FOREACH(const ValType& v, src) {
		addData(v.first, v.second, local);
	}
}

void TaskEnvironment::addValues(const map<string, int>& src) {
	typedef map<string, int>::value_type ValType;
	BOOST_FOREACH(const ValType& v, src) {
		addValue(v.first, v.second);
	}
}

void TaskEnvironment::getDatas(map<string, DataObject*>& res) const {
	res = datas;
}

void TaskEnvironment::getValues(map<string, int>& res) const {
	res = values;
}

void TaskEnvironment::copyAllTo(TaskEnvironment *dst) const {	
	typedef map<string, DataObject*>::value_type DValType;
	typedef map<string, int>::value_type VValType;
	BOOST_FOREACH(const DValType& v, datas) {
		dst->addData(v.first, v.second, false);
	}
	BOOST_FOREACH(const VValType& v, values) {
		dst->addValue(v.first, v.second);
	}
}

/*void TaskEnvironment::copyAllValues(TaskEnvironment *dst) {
	typedef map<string, int> smap;
	BOOST_FOREACH(const smap::value_type& v, locals) {
		dst->addValue(v.first, v.second);
	}
}*/

/*bool FragmentProcedure::IsFree(const FragmentGraph::CFVertex &cv) {
	return (cv.dep_cnt == 0);
}

bool FragmentProcedure::IsReady(const FragmentGraph::CFVertex &cv, FragmentIdSet &req_dfs) { // check if all args for cf are ready
	if(cv.dep_cnt > 0) return false; // cf is not free	
	bool res = true;
	BOOST_FOREACH(const InputArgContext::Arg &arg, cv.iac.args) {
		if(arg.local) // arg is local df
		{			
			if(fg.dfs.find(arg.id) == fg.dfs.end()) { // there is no required df on node
				res = false; // not ready
				req_dfs.insert(arg.id);
			}
		} else { // arg is from input
		}
	}
return res;
}

bool FragmentProcedure::CheckCF(const FragmentGraph::CFVertex &cv) { // check if all args for cf are ready
	if(IsFree(cv)) { // is free
		FragmentIdSet req_dfs;
		if(IsReady(cv, req_dfs)) { // is ready
			ready_cfs.insert(cv.id); // add to ready
			return true;
		} else {
		//	free_cfs.insert(cv.id);
			BOOST_FOREACH(FragmentId df_id, req_dfs) {
				if(required_dfs.find(df_id) == required_dfs.end()) {// new request
					dfs_requests.insert(df_id); // add to requests
				}
				required_dfs[df_id].insert(cv.id); // add req info
			}			
		}
	}
return false;
}

void FragmentProcedure::InitInputContext(InputContext &cf_ic, const InputArgContext &cf_iac) {
	//cf_ic.input_sz = cf_iac.input_sz;
	cf_ic.params = cf_iac.params; // direct copy
	BOOST_FOREACH(const InputArgContext::Arg &arg, cf_iac.args) {
		if(arg.local) // arg is local df
		{	
			if(!fs.ExistsDF(arg.id)) { // create df
				FragmentGraph::DFVertex &dv = fg.dfs[arg.id];
				DataFragment *df = DataFragment::New(dv.type, dv.id, dv.params);
				df->SetParent(this);
				fs.AddDF(df);
			}
			cf_ic.args.push_back(fs.GetDF(arg.id)); // get local df
		} else { // arg is from input
			cf_ic.args.push_back(ic.args[arg.id]); // get arg from proc input
		}
	}
}

void FragmentProcedure::OnInit() {
	boost::unique_lock<boost::mutex> lock(p_mutex);	
	BOOST_FOREACH(const FragmentGraph::CFMap::value_type &cv, fg.cfs) { // check all existing cfs		
		CheckCF(cv.second); // check if free or ready	
	}
}

void FragmentProcedure::OnNewDF(const FragmentGraph::DFVertex &dv, DataFragment *df) {
	boost::unique_lock<boost::mutex> lock(p_mutex);	
	df->SetParent(this);
	if(df) fs.AddDF(df); // store df data
	FragmentId df_id = dv.id;
	fg.dfs[df_id] = dv; // add to graph
	if(required_dfs.find(df_id) != required_dfs.end()) { // this df is required
		BOOST_FOREACH(FragmentId cf_id, required_dfs[df_id]) // for cfs awaiting this df	
			CheckCF(fg.cfs[cf_id]); // check if some cfs are ready now
		required_dfs.erase(dv.id); // df is here - erase request
	}
}

void FragmentProcedure::OnNewDFs(const DFList &dfs) {
	boost::unique_lock<boost::mutex> lock(p_mutex);	
	BOOST_FOREACH(const DFList::value_type &el, dfs) {	// add dfs
		FragmentId df_id = el.first.id;
		fg.dfs[df_id] = el.first; // add to graph
		if(el.second) {
			el.second->SetParent(this);
			fs.AddDF(el.second);
		}
	}
	BOOST_FOREACH(const DFList::value_type &el, dfs) {	// check for required dfs
		FragmentId df_id = el.first.id;
		if(required_dfs.find(df_id) != required_dfs.end()) { // this df is required
			BOOST_FOREACH(FragmentId cf_id, required_dfs[df_id]) // for cfs awaiting this df	
				CheckCF(fg.cfs[cf_id]); // check if some cfs are ready now
			required_dfs.erase(df_id); // df is here - erase request
		}
	}
}

void FragmentProcedure::OnNewCFs(const CFList &cfs) {	
	boost::unique_lock<boost::mutex> lock(p_mutex);	
	BOOST_FOREACH(const CFList::value_type &el, cfs) {	// add cfs	
		FragmentGraph::CFVertex &cv = fg.cfs[el.id] = el;		
		CheckCF(cv); // check for ready
	}
}

void FragmentProcedure::OnNewGraph(const FragmentGraph &graph) {
	boost::unique_lock<boost::mutex> lock(p_mutex);	
	FragmentIdSet cfs_to_check;
	BOOST_FOREACH(const FragmentGraph::DFMap::value_type &dv, graph.dfs) {
		FragmentId df_id = dv.first;
		fg.dfs[df_id] = dv.second;
		if(required_dfs.find(df_id) != required_dfs.end()) {
			cfs_to_check.insert(required_dfs[df_id].begin(), required_dfs[df_id].end());
			required_dfs.erase(df_id);
		}
	}
	BOOST_FOREACH(FragmentId cf_id, cfs_to_check) { // check prev cfs
		CheckCF(fg.cfs[cf_id]);
	}
	BOOST_FOREACH(const FragmentGraph::CFMap::value_type &cv, graph.cfs) { // add and check new cfs
		fg.cfs[cv.first] = cv.second;
		CheckCF(fg.cfs[cv.first]);
	}
}

void FragmentProcedure::OnCFStart(CompFragment *cf) { // mark cf as executing		
	boost::unique_lock<boost::mutex> lock(p_mutex);		
	FragmentGraph::CFVertex &cv = fg.cfs[cf->GetId()];
	InitInputContext(cf->ic, cv.iac); // init args	
}

void FragmentProcedure::OnCFDone(CompFragment *cf, CFDepMap &cf_deps) { // mark cf as finished
	boost::unique_lock<boost::mutex> lock(p_mutex);		
	const FragmentId cf_id = cf->GetId();
	const FragmentIdSet &next = fg.cfs.find(cf_id)->second.next;
	BOOST_FOREACH(FragmentId next_id, next) { // for outcoming arcs
		cf_deps[next_id]++; // add to deps info
	}
	fs.RemoveCF(cf_id); // erase cf
	fg.cfs.erase(cf_id); // erase graph codevertex
	//printf("Rem : %d\n", fg.cfs.size());
}

void FragmentProcedure::OnCFDepend(const CFDepMap &cf_deps, CFDepMap &remote_cf_deps) { // decrease cd dependencies count
	boost::unique_lock<boost::mutex> lock(p_mutex);		
	BOOST_FOREACH(const CFDepMap::value_type &d, cf_deps) { 
		FragmentGraph::CFMap::iterator itv = fg.cfs.find(d.first);
		if(itv != fg.cfs.end()) { // fragment is on this node
			FragmentGraph::CFVertex &next = itv->second;
			next.dep_cnt -= d.second;
			CheckCF(next);
		} else { // fragment is not on this node
			remote_cf_deps[d.first] += d.second;
		}
	}
}

void FragmentProcedure::OnSchedule(const list<FragmentId> &cf_ids, list<CompFragment*> &res) { // create cfs for scheduled tasks
	boost::unique_lock<boost::mutex> lock(p_mutex);		
	BOOST_FOREACH(FragmentId cf_id, cf_ids) {
		FragmentGraph::CFVertex &cv = fg.cfs[cf_id]; // get cf codevertex
		CompFragment *cf = new CompFragment(cf_id, cv.code_id); // create cf
		cf->SetParent(this);
		fs.AddCF(cf); // add to storage	
		res.push_back(cf);
		ready_cfs.erase(cf_id);
		//free_cfs.erase(cf_id);
	}
}

bool FragmentProcedure::RequestDFs(const FragmentIdSet &df_ids, DFList &dfs, FragmentIdSet &rest) { // get required dfs
	boost::unique_lock<boost::mutex> lock(p_mutex);		
	bool flg = true;
	BOOST_FOREACH(FragmentId df_id, df_ids) {		
		if(fg.dfs.find(df_id) != fg.dfs.end()) { // df is on node
			dfs.push_back(DFList::value_type(fg.dfs[df_id], fs.GetDF(df_id))); // add codevertex and df data
		} else {
			flg = false;
			rest.insert(df_id); // df is not found
		}
	}
return flg;
}

void FragmentProcedure::PopDFRequests(FragmentIdSet &req_df_ids) { // get curr requests for df
	boost::unique_lock<boost::mutex> lock(p_mutex);		
	req_df_ids.insert(dfs_requests.begin(), dfs_requests.end()); // pop all current requests
	dfs_requests.clear(); // clear current requests
}

bool FragmentProcedure::IsDone() { // check if proc is done
	boost::unique_lock<boost::mutex> lock(p_mutex);	
	return fg.cfs.empty();
}

bool FragmentProcedure::IsEmpty() { // check if proc is empty
	boost::unique_lock<boost::mutex> lock(p_mutex);	
	return fg.cfs.empty() && fg.dfs.empty();
}*/

}
