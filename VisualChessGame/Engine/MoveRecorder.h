#pragma once

#include "Subject.h"
#include <string>

#define MAX_INFO_SIZE	20

struct SimpleMove{
	int id;
	char info[MAX_INFO_SIZE];
	SimpleMove *next;
	SimpleMove *prev;
};

class MoveRecorder : public Subject{
public:
	MoveRecorder();
	~MoveRecorder();

	void AddSimpleMove(char *inf, bool fEnd);
	bool DeleteLastMove();
	bool DeleteMovesToID(int id);
	void Clear();
	SimpleMove *getSimpleMove(int id);
	SimpleMove *getFirst() { return mFirst; }
	SimpleMove *getLast() { return mLast; }
	int getMoveCount() { return mMoveCount; }
	int getCurrentId() { return mCurrentId; }
	void setCurrentId(int id) { if (id >= 0 && id <= mMoveCount) mCurrentId = id; }
protected:
	SimpleMove *mFirst;
	SimpleMove *mLast;
	int mCurrentId;
	int mMoveCount;
};