#pragma once

#include <mpi.h>
#include "icommunicator.h"
#include "topology.h"
#include <map>
#include <set>
#include <boost/thread/mutex.hpp>

// Microsoft MPI - THREAD_MULTIPLE isn't supported
#define MICROMPI 

#ifdef MICROMPI
#define MSL boost::unique_lock<boost::mutex> lock(mutex);
//#define MSU ms_mutex.unlock();
#else
#define MSL ;
//#define MSU ;
#endif

namespace rage {

class MPICommunicator : public ICommunicator // mpi comm
{    
protected:
	volatile int rank;
	volatile int size;

	std::map<int, MPI_Request> requests;
	int requestId;

	std::set<int> neigh_nodes;

	boost::mutex mutex;
	
	MPI_Comm mpiComm; // comm for MPI

protected:
	static void InitMPIComm(Topology::Type tp, int rank, int size, MPI_Comm *comm);
	//static void InitNeighbours(Topology::Type tp, int rank, int size, MPI_Comm comm, set<int> &neigh);
	
public:
	MPICommunicator(Topology::Type tp) : rank(0), size(0), requestId(0) {
		init(tp);
	}
	~MPICommunicator() {
		finalize();
	}

	int getRank() const {
		return rank;
	}

	int getSize() const {
		return size;
	}

	int init(Topology::Type tp = Topology::ALL_TO_ALL);
	int finalize(); 

	void send(void *data, unsigned int dataSize, int tag, NodeId node);
	void isend(void *data, unsigned int dataSize, int tag, NodeId node, int& req);
	void recv(void *data, unsigned int dataSize, int tag, NodeId node);

	bool check(ICommunicator::Status& status);
	bool test(int req);

	/*void Barrier();
	
	void Reduce(void *send, void *recv, int data_sz, MPI_Op op, int node);
	void Allreduce(void *send, void *recv, int data_sz, MPI_Op op);
	void Allgather(void *send, void *recv, int data_sz);*/	

	//const set<int>& GetNeighbours() const {return neigh_nodes;}
};

}
