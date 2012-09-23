#pragma once

#include "task.h"

namespace rage {

class RangedTask : public Task 
{
protected:
	string indexName;
	unsigned int indexBegin;
	unsigned int indexEnd;
	unsigned int indexStep;

public:
	RangedTask() {}
	RangedTask(Task *p, CodeVertex *src) : Task(p, src) {}
	~RangedTask() {}

	Task::Type getType() const {
		return Task::RANGED;
	}

	void setIndexName(const string& name) {
		this->indexName = name;
	}

	const string& getIndexName() const {
		return indexName;
	}

	void setRange(unsigned int begin, unsigned int end, unsigned int step = 1) {
		indexBegin = begin;
		indexEnd = end;
		indexStep = step;
	}

	unsigned int getBegin() const {
		return indexBegin;
	}

	unsigned int getEnd() const {
		return indexEnd;
	}

	unsigned int getStep() const {
		return indexStep;
	}
};

}