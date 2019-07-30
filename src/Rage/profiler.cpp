#include "profiler.h"
#include <iomanip>

namespace rts
{

SystemId Profiler::AddEvent(Event* e)
{
	SystemId id = cnt++;
	events.Add(id, e);
return id;
}

void Profiler::WriteLogFile(char* file)
{
	ofstream f_out;
	f_out.open(file);
	f_out.precision(12);

	for(PtrCollection<Event>::iterator it = events.begin();it != events.end();it++)
	{
		TimeEvent* e = (TimeEvent*)(it->second);
		f_out << it->first << " " << e->GetTag() << " " << scientific << e->GetBegin() << " " << e->GetEnd() << " " << e->GetDuration() << endl;
	}
	f_out.close();
}

}