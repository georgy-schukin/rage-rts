#include "mpicomm.h"
#include "exception.h"

namespace rage {

int MPICommunicator::init(Topology::Type tp) {
    int req = -1;    
    MPI_Init_thread(0, 0, MPI_THREAD_MULTIPLE, &req);
    
    if(req != MPI_THREAD_MULTIPLE) {
		//throw new Exception("Can't get required MPI multithread level");	    
    }	
    
    int rnk, sz;
	MPI_Comm_rank(MPI_COMM_WORLD, &rnk); // get rank
	MPI_Comm_size(MPI_COMM_WORLD, &sz); // get size    

	MPICommunicator::InitMPIComm(tp, rnk, sz, &mpiComm);

	MPI_Comm_rank(mpiComm, &rnk); // get rank
	MPI_Comm_size(mpiComm, &sz); // get size
	rank = rnk;
	size = sz;

	//MPICommunicator::InitNeighbours(tp, rank, size, mpi_comm, neigh_nodes);
return 0;
}

void MPICommunicator::InitMPIComm(Topology::Type tp, int rank, int size, MPI_Comm *comm) {	
	switch(tp) {
		case Topology::ALL_TO_ALL: {				
				MPI_Comm_dup(MPI_COMM_WORLD, comm); // use default comm world
				break;
			}
		case Topology::LATTICE: {
				int dim = size;
				int period = 0;
				MPI_Cart_create(MPI_COMM_WORLD, 1, &dim, &period, 0, comm);
				break;
			}
		case Topology::RING: {
				int dim = size;
				int period = 1;
				MPI_Cart_create(MPI_COMM_WORLD, 1, &dim, &period, 0, comm);
				break;
			}
	}	
}

/*void MPICommunicator::InitNeighbours(Topology::Type tp, int rank, int size, MPI_Comm comm, set<int> &neigh) {	
	switch(tp) {
		case Topology::ALL_TO_ALL: {
				for(int i = 0;i < size;i++) if(rank != i) neigh.insert(i);
				break;
			}
		case Topology::LATTICE:
		case Topology::RING: {
				int src = rank, dest;
				MPI_Cart_shift(comm, 0, 1, &src, &dest);
				if(src != MPI_UNDEFINED) neigh.insert(src);
				if(dest != MPI_UNDEFINED) neigh.insert(dest);
				break;
			}
	}
}*/


int MPICommunicator::finalize() {	
	MPI_Comm_free(&mpiComm);
	MPI_Finalize();
return 0;
}

void MPICommunicator::send(void *data, unsigned int dataSize, int tag, NodeId node) {
	MSL;
	MPI_Send(data, dataSize, MPI_BYTE, node, tag, mpiComm);
}

void MPICommunicator::isend(void *data, unsigned int dataSize, int tag, NodeId node, int& req) {
	MSL;
	req = requestId++;
	MPI_Isend(data, dataSize, MPI_BYTE, node, tag, mpiComm, &requests[req]);
}

void MPICommunicator::recv(void *data, unsigned int dataSize, int tag, NodeId node) {
	MSL;
	MPI_Recv(data, dataSize, MPI_BYTE, node, tag, mpiComm, MPI_STATUS_IGNORE);
}

bool MPICommunicator::check(ICommunicator::Status& status) {
	MSL;
	MPI_Status st;
	int flag = 0;

	MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, mpiComm, &flag, &st); // check for income
	if(flag) {
		status.node = st.MPI_SOURCE;		
		status.size = st.count;
		status.tag =  st.MPI_TAG;
		return true;
	}
return false;
}

bool MPICommunicator::test(int req) {
	MSL;
	if(requests.find(req) != requests.end()) {
		int flg = 0;
		MPI_Test(&requests[req], &flg, MPI_STATUS_IGNORE);
		if(flg) {
			requests.erase(req);
			return true;
		}
	}
return false;
}

/*void MPICommunicator::Barrier() {
	MPI_Barrier(mpi_comm);
}

void MPICommunicator::Allreduce(void *send, void *recv, int data_sz, MPI_Op op) {
	MSL;
	MPI_Allreduce(send, recv, data_sz, MPI_INT, op, mpi_comm);
}

void MPICommunicator::Reduce(void *send, void *recv, int data_sz, MPI_Op op, int node) {
	MSL;
	MPI_Reduce(send, recv, data_sz, MPI_INT, op, node, mpi_comm);
}

void MPICommunicator::Allgather(void *send, void *recv, int data_sz) {
	MSL;
	MPI_Allgather(send, data_sz, MPI_BYTE, recv, data_sz, MPI_BYTE, mpi_comm);
}*/

}
