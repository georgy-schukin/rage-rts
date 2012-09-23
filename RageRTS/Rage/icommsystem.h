#pragma once

#include "types.h"
#include "icommlistener.h"

namespace rage {

class ICommSystem
{
public:
	virtual void sendTask(Task *task, NodeId node) = 0;
	virtual void sendData(DataObject *data, NodeId node) = 0;
	virtual void addCommListener(ICommListener *listener) = 0;
};

}
