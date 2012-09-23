#include "idgen.h"

/*#include <stdio.h>
#include <strstream>*/

namespace rage {

unsigned int IdGenerator::generateId(const string &str) // use hash function to convert string to int
{
	unsigned int hash = 5381;    
	for(string::const_iterator it = str.begin();it != str.end();it++)
	{
		hash = ((hash << 5) + hash) + (*it); /* hash * 33 + c */
	}                
return hash;
}

/*string Concat(const string &s1, const string &s2) // get name.subname
{
	return s1 + s2;
}

string Subname(const string &s1, const string &s2) // get name.subname
{
	return s1 + string(".") + s2;
}

string Index(const string &str, int i) // get name[i]
{
	char tmp[16];
	sprintf(tmp, "[%i]", i);
return str + string(tmp);
}

string Index(const string& str, int i, int j) // get name[i,j]
{
	char tmp[16];
	sprintf(tmp, "[%i,%i]", i, j);
return str + string(tmp);
}

string Index(const string& str, int i, int j, int k) // get name[i,j,k]
{
	char tmp[16];
	sprintf(tmp, "[%i,%i,%i]", i, j, k);
return str + string(tmp);
}*/

}
