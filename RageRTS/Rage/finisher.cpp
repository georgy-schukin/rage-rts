#include "finisher.h"

namespace fprts
{

/////////////////////////// Finisher ///////////////////////////////
void Finisher::Init()
{
	MyMutex::LockObject lock(f_mutex); 
	alldone = 0;
	alldone_count = 0;
}

void Finisher::SetData(int dn, int size)
{
	MyMutex::LockObject lock(f_mutex); 
	alldone += dn;
	alldone_count++;

	if(alldone_count == size)
	{
		f_cond.Signal(); // wake up
	}
}

void Finisher::SetDataAndWait(int dn, int size)
{
	MyMutex::LockObject lock(f_mutex); 
	alldone += dn;
	alldone_count++;

	if(alldone_count < size)
	{
		f_cond.Wait(f_mutex); // wait
	}	
}

void Finisher::GetData(int &all, int &cnt)
{
	MyMutex::LockObject lock(f_mutex); 
	all = alldone;
	cnt = alldone_count;
}

void Finisher::Wait()
{
	f_cond.Wait(f_mutex); // wait
}

void Finisher::WakeUp()
{
	f_cond.Signal(); // wake up
}

}