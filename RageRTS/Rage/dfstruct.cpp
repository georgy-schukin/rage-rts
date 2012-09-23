#include "dfstruct.h"

namespace fprts {

DataFragment* DFStructArray1D::GetElem(unsigned int ind) {
	return (elems.find(ind) != elems.end()) ? elems[ind] : 0;
}

void DFStructArray1D::AddElem(unsigned int ind, DataFragment *elem) {
	elems[ind] = elem;
}

}

///////////////////////// Structured DF Struct ////////////////////////
/*void StructuredDFStruct::RegisterField(const string& name, Fragment* f) // register field location 
{
	fields.Add(name, f);
}

Fragment* StructuredDFStruct::GetChild(const Param& tag) // get child
{
	if(tag.Type() != Param::STRING) return 0;
	if(!fields.Exists(tag.String()) return 0;
return fields[tag.String()];
}

//////////////////////// Structured Array //////////////////////
template<class T>
class DFStructuredVector : public StructuredDataFragment // vector of fragments
{
protected:	
	typename std::vector<T*> elems;

public:
	DFStructuredVector(bool create_children = true) {}
	DFStructuredVector(const UInt& sz)
	{
		for(UInt i = 0;i < elem_num;i++)
		{
			elems.push_back(new T());
		}
	}
	~DFStructuredVector()
	{
		for(typename std::vector<T*>::iterator it = elems.begin();it != elems.end();it++) // delete elems of vector
		{
			delete (*it);
		}
	}

	//T* Data() {return (T*)GetBuf();}
	UInt GetSize() const {return elems.size();}

	virtual void Pack(ReadWriteBuffer& buf) 
	{		
		buf << elems.size();
		for(typename std::vector<T*>::iterator it = elems.begin();it != elems.end();it++) // delete elems of vector
		{
			(*it)->Pack(buf);
		}
	}
	virtual void Unpack(ReadWriteBuffer& buf) 
	{
		UInt sz;
		buf >> sz;
		for(UInt i = 0;i < sz;i++) // delete elems of vector
		{
			T* elem = new T();
			elem->Unpack(buf);			
			elems.push_back(elem);
		}
	}

	virtual Fragment* Spawn(vector<int>* params = 0) {return new DFStructuredVector<T>((*params)[0]);}
	virtual void Copy(DataFragment* df)
	{	
		DFStructuredVector<T>* src = (DFStructuredVector<T>*)df;
		for(UInt i = 0;i < elems.GetSize();i++) 
		{
			elems[i]->Copy(src[i]);
		}		
	}

	T& operator[](const UInt& ind) {return *(elems[ind]);}

	virtual bool IsStructured() {return true;} // check if it's structured fragment
	virtual bool IsAddable() {return true;} // check if it's structured fragment

	virtual void Expand(FragmentScope* scope, vector<int>* params = 0) // for structured fragments
	{
		for(UInt i = 0;i < elems.size();i++)
		{
			scope->AddDF<T>();
		}
	}

	void AddChild(Fragment* child)
	{
		elems.push_back(child);
	}
};
*/
