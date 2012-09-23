#pragma once

#include <boost/date_time/posix_time/posix_time.hpp>

class Timer
{
protected:
	boost::posix_time::ptime time;

public:
	Timer() {}
	~Timer() {}

	void start() {		
		time = boost::posix_time::microsec_clock::universal_time();
	}

	double stop() {		
		boost::posix_time::time_period p(time, boost::posix_time::microsec_clock::universal_time());
		double res = double(p.length().total_microseconds())/1000000.0;
		return res;
	}
};