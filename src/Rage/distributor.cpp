#include "distributor.h"
#include "fragmentgraph.h"

namespace fprts {

bool RandomDistributor::Distribute(const FragmentGraph &graph, const LoadCollector &lc, DistributionPlan &plan) { // random distribution
	unsigned int sz = lc.GetNodesNum();
	for(FragmentGraph::DFMap::const_iterator it = graph.dfs.begin();it != graph.dfs.end();it++) {
		plan[rand() % sz].dfs.insert(it->first);
	}
	for(FragmentGraph::CFMap::const_iterator it = graph.cfs.begin();it != graph.cfs.end();it++) {
		plan[rand() % sz].cfs.insert(it->first);
	}
return true;
}

bool CyclicDistributor::Distribute(const FragmentGraph &graph, const LoadCollector &lc, DistributionPlan &plan) { // cyclic distribution
	unsigned int sz = lc.GetNodesNum();
	int n = 0;
	for(FragmentGraph::DFMap::const_iterator it = graph.dfs.begin();it != graph.dfs.end();it++) {
		plan[(n++) % sz].dfs.insert(it->first);
	}
	n = 0;
	for(FragmentGraph::CFMap::const_iterator it = graph.cfs.begin();it != graph.cfs.end();it++) {
		plan[(n++) % sz].cfs.insert(it->first);
	}
return true;
}

bool GreedyDistributor::Distribute(const FragmentGraph &graph, const LoadCollector &lc, DistributionPlan &plan) { // place all on one node
	NodeId rank = lc.GetRootNode();
	for(FragmentGraph::DFMap::const_iterator it = graph.dfs.begin();it != graph.dfs.end();it++) {
		plan[rank].dfs.insert(it->first);
	}
	for(FragmentGraph::CFMap::const_iterator it = graph.cfs.begin();it != graph.cfs.end();it++) {
		plan[rank].cfs.insert(it->first);
	}
return true;
}

}

/*extern "C" void METIS_PartGraphRecursive(int*, int*, int*, int*, int*, int*, int*, int*, int*, int*, int*);
extern "C" void METIS_PartGraphVKway(int*, int*, int*, int*, int*, int*, int*, int*, int*, int*, int*);
extern "C" void METIS_PartGraphKway(int*, int*, int*, int*, int*, int*, int*, int*, int*, int*, int*);

namespace rts
{
///////////////////////////////////// Distributor /////////////////////////////////////////////////////////
int Distributor::DistributeDFByCF(FragmentScope* scope, const IdSet& dfs, const DistributionPlan& cf_plan, DistributionPlan& df_plan)
{
	for(IdSet::const_iterator it = dfs.begin();it != dfs.end();it++) // for each df
	{
		Map<NodeId, UInt> load;
		for(IdSet::const_iterator it2 = fp->init_send[*it].begin();it2 != fp->init_send[*it].end();it2++) // look cf locations
		{
			load[cf_plan.Get(*it2)]++;
		}
		
		if(!load.empty())
		{
		    Map<NodeId, UInt>::const_iterator it2 = load.begin();
		    NodeId max_load_node = it2->first;
		    UInt max_load = it2->second;
		    it2++;

		    for(;it2 != load.end();it2++) // search max load node
		    {
			if(it2->second > max_load) 
			{
				max_load_node = it2->first;
				max_load = it2->second;
			}
		    }
		    df_plan[*it] = max_load_node;
		}
		//else df_plan[*it] = 0;
	}
return 0;
}

int Distributor::DistributeAll(BaseFragmentProgram* fp, const UInt& part_num, DistributionPlan& cf_plan) // distributed all cfs in system
{
	if(part_num == 1) // there is one node - place all on it
	{
	    for(CFCollection::const_iterator it = fp->cfs.begin();it != fp->cfs.end();it++) cf_plan[it->first] = 0;
	}
	else
	{
	    IdSet cfs;
		fp->cfs.GetKeys(cfs); // get all cfs
	    Distribute(fp, part_num, cfs, cf_plan);
	}
return 0;
}

int Distributor::DistributeAll(BaseFragmentProgram* fp, const UInt& part_num, DistributionPlan& cf_plan, DistributionPlan& df_plan) // distributed all cfs in system
{
	if(part_num == 1) // there is one node - place all on it
	{
	    for(CFCollection::const_iterator it = fp->cfs.begin();it != fp->cfs.end();it++) cf_plan[it->first] = 0;
	    for(DFCollection::const_iterator it = fp->dfs.begin();it != fp->dfs.end();it++) df_plan[it->first] = 0;	    
	}
	else
	{
	    IdSet cfs, dfs;
		fp->dfs.GetKeys(dfs); // get all dfs
		fp->cfs.GetKeys(cfs); // get all cfs
    	    Distribute(fp, part_num, cfs, cf_plan);
	    DistributeDFByCF(fp, dfs, cf_plan, df_plan);
	}
return 0;
}


/////////////////////////////////// Simple Cycle //////////////////////////////////////////////////
int SimpleCycleDistributor::Distribute(BaseFragmentProgram* fp, const UInt& part_num, const IdSet& cfs, DistributionPlan& cf_plan)
{
	UInt curr_node = 0;
	UInt size = part_num;

	for(IdSet::const_iterator it = cfs.begin();it != cfs.end();it++) // distr cf
	{	
			cf_plan[*it] = curr_node;			
			curr_node = (curr_node + 1)%size;	
	}
return 0;
}

//////////////////////////////// Graph //////////////////////////////////////////////////////////
int GraphDistributor::Distribute(BaseFragmentProgram* fp, const UInt& part_num, const IdSet& cfs, DistributionPlan& cf_plan)
{	
	if(part_num == 1) // there is one node - place all on it
	{
	    for(IdSet::const_iterator it = cfs.begin();it != cfs.end();it++) cf_plan[*it] = 0;
	    return 0;
	}
	
	GraphData* data = CreateInnerData();

	data->graph = cfs;

	data->num_v = data->graph.size(); // set num of cfs	
	data->part.resize(data->num_v); // location for each cf

	data->num_parts = part_num; // set num of partitions to num of nodes		

	int tmp = 0;
	for(IdSet::const_iterator it = data->graph.begin();it != data->graph.end();it++, tmp++) // cf id -> index
	{
		data->id_map[*it] = tmp;
		data->part[tmp] = -1;
	}	

	InitInnerData(fp, data, part_num); // init some inner data

	ComputePartition(data); // use some function to compute cf partition
	
	for(IdSet::const_iterator it = data->graph.begin();it != data->graph.end();it++, tmp++) cf_plan[*it] = data->part[data->id_map[*it]];

	FreeInnerData(data); // free temp data
return 0;
}

//////////////////////////////// Metis Graph //////////////////////////////////////////////////////////
void MetisGraphDistributor::InitInnerData(BaseFragmentProgram* fp, GraphData* dt, const UInt& part_num)
{	
	MetisData* data = (MetisData*)dt;

	data->weight_v.resize(data->num_v*data->num_constr); // weight for each cf
	data->index.push_back(0);
	
	int tmp = 0, last = 0;

	for(IdSet::const_iterator it = data->graph.begin();it != data->graph.end();it++, tmp++) // each cf as codevertex
	{
		CompFragment* cf = fp->cfs[*it];
		data->weight_v[tmp*data->num_constr] = cf->weight;	// set codevertex weight			

		int cnt = 1;		
		for(IdSet::const_iterator it2 = cf->edges.begin();it2 != cf->edges.end();it2++) // look for connected cfs
		{
			if(data->graph.find(*it2) != data->graph.end()) // cf is in curr graph
			{
				data->edges.push_back(data->id_map[*it2]); // form edge
				data->weight_e.push_back(1);
				cnt++;
			}
		}
		last += cnt;
		data->index.push_back(last);
	}	
}

void MetisGraphDistributor::ComputePartition(GraphData* dt)
{
	MetisData* data = (MetisData*)dt;
    data->weight_flag = 3;
	METIS_PartGraphKway(
		&data->num_v,
		&(data->index[0]),
		&(data->edges[0]),
		&(data->weight_v[0]),		
		&(data->weight_e[0]),
		&data->weight_flag,
		&data->num_flag,
		&data->num_parts,		
		&(data->options[0]),
		&data->edgecut,
		&(data->part[0]));
}


//////////////////////////////// Patoh Hyper Graph //////////////////////////////////////////////////////////
void PatohHyperGraphDistributor::InitInnerData(BaseFragmentProgram* fp, GraphData* dt, const UInt& part_num) // init data (add to already exsited)
{
	PatohData* data = (PatohData*)dt;
	PaToH_Initialize_Parameters(&data->args, PATOH_CONPART, PATOH_SUGPARAM_DEFAULT);

	data->weight_v.resize(data->num_v*data->num_constr); // weight for each cf
	data->args._k = part_num; // set num of partitions to num of nodes

	data->weight_part.resize(data->args._k*data->num_constr);
//	data->weight_target.resize(data->args._k);

	data->index.push_back(0);

	int tmp = 0, last = 0;

	for(IdSet::const_iterator it = data->graph.begin();it != data->graph.end();it++, tmp++) // each cf as codevertex
	{
		CompFragment* cf = fp->cfs[*it];
		data->weight_v[tmp*data->num_constr] = cf->weight;	// set codevertex weight	

		for(Map<SystemId, IdSet>::const_iterator it2 = cf->output_connection.begin();it2 != cf->output_connection.end();it2++) // make hyperedge for each output df
		{			
			data->edges.push_back(data->id_map[*it]); // add codevertex
			int cnt = 1;
			for(IdSet::const_iterator it3 = it2->second.begin();it3 != it2->second.end();it3++) // for each connected cf
			{
				if(data->graph.find(*it3) != data->graph.end())
				{
					data->edges.push_back(data->id_map[*it3]); // form hyperedge - add connected vertexes
					cnt++;
				}
			}
			data->weight_e.push_back(fp->dfs.Get(it2->first)->GetSize()*cnt);
			last += cnt;
			data->index.push_back(last);
		}
	}
	data->num_e = data->index.size() - 1;
}

void PatohHyperGraphDistributor::ComputePartition(GraphData* dt)
{   
	PatohData* data = (PatohData*)dt;
	PaToH_Alloc(&data->args, data->num_v, data->num_e, data->num_constr, &(data->weight_v[0]), &(data->weight_e[0]), &(data->index[0]), &(data->edges[0]));

	PaToH_Part(
		&data->args,
		data->num_v, 
		data->num_e, 
		data->num_constr, 
		data->use_fixed_cells, 
		&(data->weight_v[0]),		
		&(data->weight_e[0]),
		&(data->index[0]),
		&(data->edges[0]),
		NULL,
		//&(data->weight_target[0]),
		&(data->part[0]),
		&(data->weight_part[0]),		
		&data->cut);

	PaToH_Free();
}

//////////////////////////////// Patoh Hyper Graph Layred //////////////////////////////////////////////////////////
/*int PatohHyperGraphLayeredDistributor::Distribute(const UInt& part_num, FragmentProgram* fp, DistributionPlan& cf_plan, DistributionPlan& df_plan)
{
	set<SystemId> cf_layer;
	set<SystemId> cfs;
	
	UInt size = part_num;

	GetFreeCF(fp, cf_layer); // insert first free layer
	cfs.insert(cf_layer.begin(), cf_layer.end());

	for(UInt i = 1;i < depth;i++)
	{
		set<SystemId> cf_next_layer;
		GetNextCF(fp, cf_layer, cf_next_layer);	
		cf_layer = cf_next_layer;
		cfs.insert(cf_layer.begin(), cf_layer.end());
	}

	do
	{
		//cfs.insert(cf_layer.begin(), cf_layer.end());
		PatohData dt;
		InitPatohData(part_num, fp, cfs, dt);
		int i = 0;
		for(set<SystemId>::const_iterator it = cfs.begin();it != cfs.end();it++, i++) // make cf plan
		{
			if(cf_plan.Exists(*it)) data->part[i] = cf_plan.Get(*it);
		}
		data->use_fixed_cells = 1;
		ComputePartition(dt);
		i = 0;
		for(set<SystemId>::const_iterator it = cfs.begin();it != cfs.end();it++, i++) // make cf plan
		{
			cf_plan[*it] = data->part[i];		
		}
		for(UInt k = 0;k < depth;k++)
		{
			set<SystemId> cf_next_layer;
			GetNextCF(fp, cf_layer, cf_next_layer);	
			cf_layer = cf_next_layer;
			cfs.insert(cf_layer.begin(), cf_layer.end());
		}
	}
	while(!cf_layer.empty());
		DistributeDFByCF(fp, cf_plan, df_plan);
return 0;
}

///////////////////////////////////// Hyper Graph MC ///////////////////////////////////////////////
void PatohHyperGraphMCDistributor::InitInnerData(BaseFragmentProgram* fp, GraphData* dt, const UInt& part_num) // init data (add to already exsited)
{
	dt->num_constr = 2;
	PatohHyperGraphDistributor::InitInnerData(fp, dt, part_num);

	
	for(IdSet::const_iterator it = dt->graph.begin();it != dt->graph.end();it++) // each cf as codevertex
	{	
		dt->weight_v[dt->id_map[*it]*dt->num_constr + 1] = fp->cfs[*it]->order_weight;	// add order weight to constraints
	}
	for(vector<int>::iterator it = dt->weight_e.begin();it != dt->weight_e.end();it++) *it = 1; // set net weight to 1
}*/
