#pragma once

#include "Subject.h"

/**
 *           Move and Capture Directions
 *    A       Forward (F)      D
 * Left(L)                 Right (R)
 *    C        Back (B)        T
 *  K - move direction for Knight
 */

class ChessPiece : public Subject {
public:
	ChessPiece() : mMoveCount(0), mHPosition(-1), mVPosition(-1), mfHasMoved(false), mfCaptured(false) { playerId = 0; }
	ChessPiece(int h, int v) : mMoveCount(0), mHPosition(h), mVPosition(v), mfHasMoved(false), mfCaptured(false) { playerId = 0; }
	ChessPiece(int h, int v, int id) :mMoveCount(0), mHPosition(h), mVPosition(v), mfHasMoved(false), mfCaptured(false) { playerId = id; }
	virtual ~ChessPiece() {}
	
	int GetHPosition() { return mHPosition; }
	int GetVPosition() { return mVPosition; }
	bool Move(int h, int v);
	bool HasMoved() { return (mMoveCount != 0); }
	void SetMoved(bool fm) { mfHasMoved = fm; }
	int getMoveCount() { return mMoveCount; }
	void setMoveCount(int mc) { mMoveCount = mc; }
	bool HasCaptured() { return mfCaptured; }
	void SetCapruted(bool bc) { mfCaptured = bc; }
	int getPlayerId() { return playerId; }
	void setPlayerId(int id) { playerId = id; }
	virtual char *getMoveAndCaptureDirections() { return ""; }

	virtual bool MoveIsLegal(int h, int v) { return true; };
	virtual char* GetName() { return ""; };
protected:
	int mMoveCount;
	int playerId;
	int mHPosition;
	int mVPosition;
	bool mfHasMoved;
	bool mfCaptured;
};