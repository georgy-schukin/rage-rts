#include "structuredf.h"

///////////////////////// Structured Data Fragment /////////////////////////////
namespace rts
{

UInt StructuredDataFragment::GetSize() const; // get size of data		
{
	UInt sz = 0;
	for(FragmentSet::const_iterator it = fragments.begin();it != fragments.end();it++) 
	{
		sz += ((DataFragment*)it->second)->GetSize();
	}
return sz;
}

/*void StructuredDataFragment::Pack(ReadWriteBuffer* buf) // pack data in buf
{
	for(FragmentSet::const_iterator it = fragments.begin();it != fragments.end();it++) 
	{
		sz += ((DataFragment*)it->second)->Pack(buf);
	}
}

void StructuredDataFragment::Unpack(ReadWriteBuffer* buf) // unpack data from buf
{
	for(FragmentSet::const_iterator it = fragments.begin();it != fragments.end();it++) 
	{
		sz += ((DataFragment*)it->second)->Unpack(buf);
	}
}*/	

void StructuredDataFragment::Init() // init data in fragment at first time
{
	for(FragmentSet::const_iterator it = fragments.begin();it != fragments.end();it++) 
	{
		sz += ((DataFragment*)it->second)->Init();
	}
}

};

}