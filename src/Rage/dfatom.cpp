#include "dfatom.h"

namespace fprts {

int DFAtomBlock::Create() {
	if(block_size) {
		char *buf = new char[block_size];
		memset(buf, 0, block_size);
		block = boost::shared_array<char>(buf);
		return 0;
	}
return -1;
}

/*bool DFAtomBlock::IsCreated() const {
	return (block_size && block.get());
}*/

void DFAtomBlock::Pack(Message &msg) const { // pack itself to buffer
	Fragment::Pack(msg);
	msg << block_size;	
	msg.Write(block.get(), block_size); // write data if any	
}

void DFAtomBlock::Unpack(Message &msg) { // unpack itself from buffer	
	Fragment::Unpack(msg);
	msg >> block_size;
		Create();
	msg.Read(block.get(), block_size);
}

}

/*template<class T>
class DFScalar : public DataFragment // scalar
{
public:
	T data;

public:
	DFScalar(FragmentDescr* d) : DataFragment(d) {}
	~DFScalar() {}

//	virtual void* GetData() {return &data;}
//	virtual UInt GetSize() const {return sizeof(T);}

	virtual void Pack(ReadWriteBuffer* buf) {buf->Write<T>(data)}
	virtual void Unpack(ReadWriteBuffer* buf) {buf->Read<T>(data);}

	virtual Fragment* Spawn(FragmentDescr* d, ParamArray* params) {return new DFScalar<T>(d);}
	virtual void Copy(DataFragment* df) {data = ((DFScalar<T>*)df)->data;}	
};

class DFBuffer : public DataFragment, public Buffer // linear buffer of data
{
public:
	DFBuffer(FragmentDescr* d) : DataFragment(d) {}
	DFBuffer(FragmentDescr* d, const UInt& sz) : DataFragment(d), Buffer(sz) {}
	~DFBuffer() {}

	//virtual void* GetData() {return GetBuf();}
	//virtual UInt GetSize() const {return GetBufSize();}

	virtual void Pack(ReadWriteBuffer& buf) 
	{
		buf.Write<UInt>(GetBufSize());
		buf.Write(GetBuf(), GetBufSize());
	}
	virtual void Unpack(ReadWriteBuffer& buf) 
	{
		Create(buf.Read<UInt>());
		buf.Read(GetBuf(), GetBufSize());
	}

	virtual DataFragment* Spawn(FragmentDescr* d, ParamArray* params) {return new DFBuffer(d, (*params)[0].Int());}
	virtual void Copy(DataFragment* df) 
	{		
		Create(((DFBuffer*)df)->GetBufSize()); 		
		memcpy(GetBuf(), ((DFBuffer*)df)->GetBuf(), ((DFBuffer*)df)->GetBufSize());
	}	
};

template<class T>
class DFArray1D : public DFBuffer // 1D array of elems of type T
{
protected:
	UInt size;

public:
	DFArray1D() : size(0) {}
	DFArray1D(const UInt& sz) : DFBuffer(sz*sizeof(T)), size(sz) {}
	~DFArray1D() {}

	T* Data() {return (T*)GetBuf();}
	UInt GetSize() const {return size;}

	virtual void Pack(ReadWriteBuffer& buf) 
	{		
		buf << size;
		DFBuffer::Pack(buf);		
	}
	virtual void Unpack(ReadWriteBuffer& buf) 
	{
		buf >> size;
		DFBuffer::Unpack(buf);
	}

	virtual DataFragment* Spawn(vector<int>* params) {return new DFArray1D<T>((*params)[0]);}
	virtual void Copy(DataFragment* df) 
	{		
		size = ((DFArray1D<T>*)df)->GetSize(); 
		DFBuffer::Copy(df);		
	}

	T& operator[](const UInt& ind) {return *(Data() + ind);}
};

template<class T>
class DFArray2D : public DFBuffer // 2D array of elems of type T
{
protected:
	UInt sz1, sz2;

public:
	DFArray2D() : sz1(0), sz2(0) {}
	DFArray2D(const UInt& sz_1, const UInt& sz_2) : DFBuffer(sz_1*sz_2*sizeof(T)), sz1(sz_1), sz2(sz_2) {}
	~DFArray2D() {}

	T* Data() {return (T*)GetBuf();}
	UInt SizeY() const {return sz1;}
	UInt SizeX() const {return sz2;}

	virtual void Pack(ReadWriteBuffer& buf) 
	{
		buf << sz1 << sz2;
		DFBuffer::Pack(buf);
	}
	virtual void Unpack(ReadWriteBuffer& buf) 
	{
		buf >> sz1 >> sz2;
		DFBuffer::Unpack(buf);
	}

	virtual DataFragment* Spawn(vector<int>* params) {return new DFArray2D<T>((*params)[0], (*params)[1]);}
	virtual void Copy(DataFragment* df) 
	{
		sz1 = ((DFArray2D<T>*)df)->SizeY(); 
		sz2 = ((DFArray2D<T>*)df)->SizeX();
		DFBuffer::Copy(df);
	}

	T& Get(const UInt& i, const UInt& j) {return *(Data() + i*size[0] + j);}
};*/
