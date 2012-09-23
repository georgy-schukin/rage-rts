#pragma once

#include "types.h"
#include "loadcollector.h"
//#include "fragmentgraph.h"
#include <map>
using namespace std;

namespace fprts {

class FragmentGraph;

class Distributor // distribute dfs and cfs among nodes
{
public:
	enum Type
	{
		RANDOM = 0,
		CYCLIC,
		GREEDY
	};

public:
	typedef struct {
		FragmentIdSet dfs;
		FragmentIdSet cfs;
	} DistributionInfo;
	typedef map<NodeId, Distributor::DistributionInfo> DistributionPlan;

public:
	virtual bool Distribute(const FragmentGraph &graph, const LoadCollector &lc, DistributionPlan &plan) = 0; // get destribution of fragments
};

class RandomDistributor : public Distributor 
{
public:
	RandomDistributor() {}
	~RandomDistributor() {}

	virtual bool Distribute(const FragmentGraph &graph, const LoadCollector &lc, DistributionPlan &plan);
};

class CyclicDistributor : public Distributor
{
public:
	CyclicDistributor() {}
	~CyclicDistributor() {}

	virtual bool Distribute(const FragmentGraph &graph, const LoadCollector &lc, DistributionPlan &plan);
};

class GreedyDistributor : public Distributor
{
public:
	GreedyDistributor() {}
	~GreedyDistributor() {}

	virtual bool Distribute(const FragmentGraph &graph, const LoadCollector &lc, DistributionPlan &plan);
};

/*typedef Map<SystemId, NodeId> DistributionPlan;

class Distributor // class for fragment distribution
{	
public:
	Distributor() {}
	virtual ~Distributor() {}

	int DistributeAll(FragmentProgramGraph* fpg, const UInt& part_num, DistributionPlan& cf_plan); // distribute all cfs in fprts
	int DistributeAll(FragmentProgramGraph* fpg, const UInt& part_num, DistributionPlan& cf_plan, DistributionPlan& df_plan); // distribute all cfs in fprts

	virtual int Distribute(FragmentProgramGraph* fpg, const UInt& part_num, const IdSet& cfs, DistributionPlan& cf_plan) = 0;
	virtual int DistributeDFByCF(FragmentProgramGraph* fpg, const IdSet& dfs, const DistributionPlan& cf_plan, DistributionPlan& df_plan); // distribute df by cf distribution
};

class SimpleCycleDistributor : public Distributor
{
public:
	SimpleCycleDistributor() {}
	virtual ~SimpleCycleDistributor() {}

	virtual int Distribute(FragmentScope* scope, const UInt& part_num, const IdSet& cfs, DistributionPlan& cf_plan);
};

/////////////////////////// Graph ///////////////////////////////////
class GraphDistributor : public Distributor 
{
protected:
	struct GraphData // struct to represent graph
	{
		IdSet graph; // graph
		Map<SystemId, int> id_map; // cf id -> cf index in graph struct

		vector<int> index; // index for edges
		vector<int> edges; // edges
		vector<int> weight_v; // weights of vertexes
		vector<int> weight_e; // weigts of hyperedges
		vector<int> part; // partition		

		int num_v; // num of vertexes
		int num_e; // num of edges
		int num_parts; // num of partitions		
		int num_constr; // num of constraints

		GraphData() : num_v(0), num_e(0), num_parts(0), num_constr(1) {}
		virtual ~GraphData() {}
	};

protected:
	virtual GraphData* CreateInnerData() {return new GraphData();}
	virtual void InitInnerData(FragmentScope* scope, GraphData* data, const UInt& part_num) = 0; // init 
	virtual void ComputePartition(GraphData* data) = 0; // call function to compute partition
	virtual void FreeInnerData(GraphData* data) {if(data) delete data;} // call function to compute partition

public:
	GraphDistributor() {}
	virtual ~GraphDistributor() {}

	virtual int Distribute(FragmentScope* scope, const UInt& part_num, const IdSet& cfs, DistributionPlan& cf_plan);
};

/////////////////////////// Metis Graph ///////////////////////////////////
class MetisGraphDistributor : public GraphDistributor // distibute with Metis
{
protected:
	struct MetisData : public GraphData // data for Metis library (suitable for all Metis functions)
	{		
		vector<int> options; // options	
				
		int num_flag;
		int weight_flag;
		int ub_factor;	
		int edgecut;		
	
		MetisData() : weight_flag(1), num_flag(0) {options.push_back(0);}
		virtual ~MetisData() {}
	};

protected:
	virtual GraphData* CreateInnerData() {return new MetisData();}
	virtual void InitInnerData(FragmentScope* scope, GraphData* data, const UInt& part_num); // init 
	virtual void ComputePartition(GraphData* data); // call function to compute partition	

public:
	MetisGraphDistributor() {}
	virtual ~MetisGraphDistributor() {}	
};

/////////////////////// Patoh Hyper Graph /////////////////////////////////
class PatohHyperGraphDistributor : public GraphDistributor // distibute with Patoh
{
protected:
	struct PatohData : public GraphData // data for Metis library (suitable for all Metis functions)
	{
		PaToH_Parameters args;
		
		vector<int> weight_part; // weight of parts
		vector<float> weight_target;
				
		int cut;
		int use_fixed_cells;
	
		PatohData() : use_fixed_cells(0) {}
		virtual ~PatohData() {}
	};	

protected:
	virtual GraphData* CreateInnerData() {return new PatohData();}
	virtual void InitInnerData(FragmentScope* scope, GraphData* data, const UInt& part_num); // init 
	virtual void ComputePartition(GraphData* data); // call function to compute partition	

public:
	PatohHyperGraphDistributor() {}
	virtual ~PatohHyperGraphDistributor() {}	
};

/////////////////////// Patoh Hyper Graph Layered /////////////////////////////////
/*class PatohHyperGraphLayeredDistributor : public PatohHyperGraphDistributor
{
protected:
	UInt depth; // depth of layer search

protected:
	void DistributeLayers(FragmentProgram* fp, const set<SystemId>& layer_1, const set<SystemId>& layer_2, DistributionPlan& cf_plan);

public:
	PatohHyperGraphLayeredDistributor(const UInt& d = 1) : depth(d) {}
	~PatohHyperGraphLayeredDistributor() {}

	virtual int Distribute(const UInt& part_num, FragmentProgram* fp, DistributionPlan& cf_plan, DistributionPlan& df_plan);
};

/////////////////////// Patoh Hyper Graph Multi Constraint /////////////////////////////////
class PatohHyperGraphMCDistributor : public PatohHyperGraphDistributor
{
protected:	
	virtual void InitInnerData(FragmentScope* scope, GraphData* data, const UInt& part_num); // init 	

public:
	PatohHyperGraphMCDistributor() {}
	virtual ~PatohHyperGraphMCDistributor() {}	
};*/

}
