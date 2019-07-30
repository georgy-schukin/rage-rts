#pragma once

#include <string>

using namespace std;

namespace rage {

class Exception
{
protected:
	string message;

public:
	Exception(const string& msg) : message(msg) {}
	~Exception() {}

	const string& getMessage() const {
		return message;
	}
};

}