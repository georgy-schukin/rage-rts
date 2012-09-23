#pragma once

#include <string>

using namespace std;

namespace rage {

class IdGenerator
{
public:
	static unsigned int generateId(const string &str); // get id from string

	/*static string Concat(const string &s1, const string &s2); // concat
	static string Subname(const string &s1, const string &s2); // get s1.s2

	static string Index(const string &str, int i); // get name[i]
	static string Index(const string &str, int i, int j); // get name[i,j]
	static string Index(const string &str, int i, int j, int k); // get name[i,j,k]*/
};

}
