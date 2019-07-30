#include "mpicomm.h"
#include "commsystem.h"
#include "execsystem.h"

#include <boost/bind.hpp>
#include <boost/foreach.hpp>

namespace rage {

//MPICommunicator comm;

void CommSystem::init(Topology::Type tp) {
	messageStorage = boost::shared_ptr<MessageStorage>(new MessageStorage(10, 1024));
	//topology.Init(tp, comm.GetRank(), comm.GetSize(), comm.GetNeighbours()); // init topology
}

void CommSystem::finalize() {	
}

void CommSystem::start() {
	isWorking = true;
	sendThread = boost::thread(boost::bind(&CommSystem::sendFunc, this));	
	recvThread = boost::thread(boost::bind(&CommSystem::recvFunc, this));		
}

void CommSystem::stop() {
	isWorking = false; // force stop	
	sendThread.join();
	recvThread.join();
}

void CommSystem::sendFunc() { // func for exec thread
	int c = 0;
	int sleep = 50;
	while(isWorking) { // while system is working and all is not done
	/*	if(ms.DoSend()) { // do some send
			if(c++ > 5) { // check after 5 sends
				c = 0;
				ms.CheckAll();
			}
		} else {
			ms.CheckAll();
			boost::this_thread::sleep(boost::posix_time::millisec(sleep));
		}*/
	}
	//ms.CheckAll();
}

void CommSystem::recvFunc() { // func for exec thread
	int sleep = 50;
//	ICommunicator::Status stat;
	Message msg(0, 1024); // message to recv all data

	while(isWorking) { // while system is working and all is not done
		/*if(comm.CheckAny(stat)) { // recv something
			ReadWriteBuffer& buf = msg;

			if(buf.BufSize() < (unsigned int)stat.size) buf.GrowTo(stat.size); // set buffer to fit income data

			comm.Recv(buf.Buf(), stat.size, stat.tag, stat.rank); // recv data
			
			msg.SetTag((Message::Tag)stat.tag);
			msg.SetReadPos(0);
			OnMessage(&msg);			
		} else {
			boost::this_thread::sleep(boost::posix_time::millisec(sleep));
		}*/
	}	
}

void CommSystem::sendTask(Task *task, NodeId node) {
}

void CommSystem::sendData(DataObject *data, NodeId node) {
}
	
/*void CommSystem::SendDFs(ProcedureId proc_id, const FragmentProcedure::DFList &dfs, NodeId node) { // send dfs to node
	Message* msg = ms.Get(Message::DF); // get buffer for message
		*msg << proc_id << (unsigned int)dfs.size();
	BOOST_FOREACH(const FragmentProcedure::DFList::value_type &el, dfs) {
		*msg << el.first; // pac codevertex
		*msg << (el.second ? true : false);
		if(el.second) *msg << *el.second; // pack df data
	}
	ms.SendAndFree(msg, node); // send
}

void CommSystem::RecvDFs(Message *msg) {
	ProcedureId proc_id;		
	unsigned int num;
	bool df_data;
		*msg >> proc_id >> num;
	FragmentProcedure::DFList dfs(num); // add num values to list
	BOOST_FOREACH(FragmentProcedure::DFList::value_type &el, dfs) {		
		*msg >> el.first;
		*msg >> df_data;
		if(df_data) {
			el.second = DataFragment::New(el.first.type, 0, vector<int>());
			*msg >> *el.second; // unpack df			
		} else {
			el.second = 0;
		}
	}
	exec_system->OnNewDFs(proc_id, dfs);
}

void CommSystem::SendCFs(ProcedureId proc_id, const FragmentProcedure::CFList &cfs, NodeId node) { // send cfs to node
	Message* msg = ms.Get(Message::CF); // get buffer for message
		*msg << proc_id << (unsigned int)cfs.size();
	BOOST_FOREACH(const FragmentProcedure::CFList::value_type &el, cfs) {
		*msg << el; // pac codevertex
	}
	ms.SendAndFree(msg, node); // send
}

void CommSystem::RecvCFs(Message *msg) {
	ProcedureId proc_id;
	unsigned int num;			
		*msg >> proc_id >> num;
	FragmentProcedure::CFList cfs(num); // add num values to list	
	BOOST_FOREACH(FragmentProcedure::CFList::value_type &el, cfs) {
		*msg >> el;
	}
	exec_system->OnNewCFs(proc_id, cfs);
}

void CommSystem::SendGraph(ProcedureId proc_id, const FragmentGraph &graph, Distributor::DistributionPlan &plan, NodeId node) { // send part of graph to node (by distr plan)
	Message *msg = ms.Get(Message::GRAPH);
	const FragmentIdSet &dfs = plan[node].dfs;
	const FragmentIdSet &cfs = plan[node].cfs;
		*msg << proc_id;
		*msg << (unsigned int)dfs.size() << (unsigned int)cfs.size();
	BOOST_FOREACH(FragmentId df_id, dfs) {
		*msg << df_id;
		*msg << graph.dfs.find(df_id)->second;
	}
	BOOST_FOREACH(FragmentId cf_id, cfs) {		
		*msg << cf_id;
		*msg << graph.cfs.find(cf_id)->second;
	}
	ms.SendAndFree(msg, node);
}

void CommSystem::RecvGraph(Message *msg) {
	FragmentGraph graph;
	ProcedureId proc_id;
	FragmentId id;
	unsigned int dfs_num, cfs_num;
		*msg >> proc_id;
		*msg >> dfs_num >> cfs_num;
	for(unsigned int i = 0;i < dfs_num;i++) {
		*msg >> id;
		*msg >> graph.dfs[id];
	}
	for(unsigned int i = 0;i < cfs_num;i++) {
		*msg >> id;
		*msg >> graph.cfs[id];
	}
	exec_system->OnNewGraph(proc_id, graph);
}

void CommSystem::SendDFRequest(ProcedureId proc_id, const FragmentIdSet &df_ids, NodeId src, NodeId node) {
	Message *msg = ms.Get(Message::DF_REQUEST);
		*msg << proc_id;
		*msg << src;
		*msg << df_ids;
	ms.SendAndFree(msg, node);
}

void CommSystem::RecvDFRequest(Message *msg) {
	ProcedureId proc_id;
	NodeId src;
	FragmentIdSet df_ids;
		*msg >> proc_id;
		*msg >> src;
		*msg >> df_ids;
	exec_system->OnDFRequest(proc_id, df_ids, src);
}

void CommSystem::SendDepend(ProcedureId proc_id, const FragmentProcedure::CFDepMap &deps, NodeId node) {
	Message *msg = ms.Get(Message::CF_DEPEND);
		*msg << proc_id;
		*msg << (unsigned int)deps.size();
	BOOST_FOREACH(const FragmentProcedure::CFDepMap::value_type &d, deps) {
		*msg << d.first << d.second;
	}
	ms.SendAndFree(msg, node);
}

void CommSystem::RecvDepend(Message *msg) {
	ProcedureId proc_id;
	FragmentProcedure::CFDepMap deps;
	FragmentId id;
	unsigned int size;
		*msg >> proc_id;
		*msg >> size;
	for(unsigned int i = 0;i < size;i++) {
		*msg >> id;
		*msg >> deps[id];
	}
	exec_system->OnCFDepend(proc_id, deps);
}

void CommSystem::SendDone(ProcedureId proc_id, NodeId src, NodeId node) {
	Message *msg = ms.Get(Message::PROC_DONE);
		*msg << proc_id;
		*msg << src;
	ms.SendAndFree(msg, node);
}

void CommSystem::RecvDone(Message *msg) {
	ProcedureId proc_id;
	NodeId src;
		*msg >> proc_id;
		*msg >> src;
	exec_system->OnProcDone(proc_id, src);
}

void CommSystem::SendLocation(ProcedureId proc_id, const FragmentLocationStorage::LocationNodeMap &loc, bool df, NodeId node) {
	Message *msg = ms.Get(df ? Message::DF_LOCATION : Message::CF_LOCATION);
		*msg << proc_id;
		*msg << (unsigned int)loc.size();
	BOOST_FOREACH(const FragmentLocationStorage::LocationNodeMap::value_type &l, loc) {
		*msg << l.first;
		*msg << l.second;
	}
	ms.SendAndFree(msg, node);
}

void CommSystem::RecvLocation(Message *msg, bool df) {
	ProcedureId proc_id;
	FragmentLocationStorage::LocationNodeMap loc;
	NodeId node;
	unsigned int size;
		*msg >> proc_id;
		*msg >> size;
	for(int i = 0;i < size;i++) {
		*msg >> node;
		*msg >> loc[node];
	}
	df ? exec_system->OnDFLocation(proc_id, loc) : exec_system->OnCFLocation(proc_id, loc);
}

void CommSystem::OnMessage(Message* msg) {
	switch(msg->GetTag()) {
		case Message::DF: RecvDFs(msg); break;
		case Message::CF: RecvCFs(msg); break;		
		case Message::GRAPH: RecvGraph(msg); break;
		case Message::DF_REQUEST: RecvDFRequest(msg); break;
		case Message::CF_DEPEND: RecvDepend(msg); break;	
		case Message::DF_LOCATION: RecvLocation(msg, true); break;
		case Message::CF_LOCATION: RecvLocation(msg, false); break;
		case Message::PROC_DONE: RecvDone(msg); break;
	}
}*/

}