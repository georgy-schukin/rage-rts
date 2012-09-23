#pragma once

//#include <mpi.h>
#include <string>
#include "rtstypes.h"

namespace rts
{

enum EventTag
{
	CF_EXEC = 0,
	DF_SEND,
	DF_RECV
};

class Event
{
protected:
	EventTag tag;
	vector<UInt> params;

public:
	Event() {}
	Event(const EventTag& tg) : tag(tg) {}
	Event(const EventTag& tg, const vector<UInt>& p) : tag(tg), params(p) {}
	~Event() {}

	const EventTag& GetTag() {return tag;}
	const vector<UInt>& Params() {return params;}
};

class TimeEvent : public Event
{
protected:
	double beg_time;
	double end_time;

public:
	TimeEvent() : beg_time(0.0), end_time(0.0) {}
	TimeEvent(const EventTag& tg) : Event(tg), beg_time(0.0), end_time(0.0) {}
	TimeEvent(const EventTag& tg, const vector<UInt>& p) : Event(tg, p), beg_time(0.0), end_time(0.0) {}
	TimeEvent(const EventTag& tg, const double& bt, const double& et) : Event(tg), beg_time(bt), end_time(et) {}
	TimeEvent(const EventTag& tg, const double& bt, const double& et, const vector<UInt>& p) : Event(tg, p), beg_time(bt), end_time(et) {}
	~TimeEvent() {}

//	void SetBegin() {beg_time = MPI_Wtime();}
//	void SetEnd() {end_time = MPI_Wtime();}

	void SetBegin(const double& b_time) {beg_time = b_time;}
	void SetEnd(const double& e_time) {end_time = e_time;}

	const double& GetBegin() {return beg_time;}
	const double& GetEnd() {return end_time;}

	double GetDuration() {return (end_time - beg_time);}
};

class Profiler
{
public:

protected:
	SystemId cnt;
	PtrCollection<Event> events;

public:
	Profiler() : cnt(0) {}
	~Profiler() {}

	SystemId AddEvent(Event* e);
	Event* GetEvent(const SystemId& id) {return events.Get(id);}

	void WriteLogFile(char* filename);
};

}