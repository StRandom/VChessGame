#include "MoveRecorder.h"

MoveRecorder::MoveRecorder()
{
	mMoveCount = 0;
	mCurrentId = mMoveCount;
	mFirst = nullptr;
	mLast = nullptr;
}

MoveRecorder::~MoveRecorder()
{
	Clear();
}

void MoveRecorder::AddSimpleMove(char *inf, bool fEnd)
{
	if (!fEnd)
		mMoveCount++;
	if (mMoveCount == 1 && !fEnd){
		SimpleMove *move = new SimpleMove;
		move->id = mMoveCount;
		strcpy(move->info, inf);
		move->next = nullptr;
		move->prev = nullptr;
		mLast = move;
		mFirst = move;
	}
	else{
		if (fEnd){
			char chInf[MAX_INFO_SIZE];
			int i = 0;
			while (mLast->info[i] != 0 && mLast->info[i] != 32){
				chInf[i] = mLast->info[i];
				i++;
			}
			chInf[i] = 0;
			strcpy(mLast->info, chInf);
			strcat(mLast->info, " ");
			strcat(mLast->info, inf);
		}
		else{
			SimpleMove *move = new SimpleMove;
			move->id = mMoveCount;
			strcpy(move->info, inf);
			move->prev = mLast;
			mLast->next = move;
			move->next = nullptr;
			mLast = move;
		}
	}
	mCurrentId = mMoveCount;
	Notify();
}

bool MoveRecorder::DeleteLastMove()
{
	if (mMoveCount == 0)
		return false;
	if (mMoveCount == 1){
		delete mLast;
		mLast = nullptr;
		mFirst = nullptr;
		mMoveCount = 0;
		Notify();
		return true;
	}
	mLast = mLast->prev;
	delete mLast->next;
	mLast->next = nullptr;
	mMoveCount--;
	mCurrentId = mMoveCount;
	Notify();
	return true;
}

bool MoveRecorder::DeleteMovesToID(int id)
{
	if (id < 0)
		return false;
	while ((mLast != nullptr) && (mLast->id > id))
		DeleteLastMove();
	mCurrentId = mMoveCount;
	Notify();
	return true;
}

void MoveRecorder::Clear()
{
	DeleteMovesToID(0);
	mCurrentId = mMoveCount;
	Notify();
}

SimpleMove *MoveRecorder::getSimpleMove(int id)
{
	if ((id > mMoveCount) || id <= 0)
		return nullptr;
	SimpleMove *current = mFirst;
	while (current->id != id)
		current = current->next;
	return current;
}