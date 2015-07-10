#include "ChessPiece.h"

bool ChessPiece::Move(int h, int v)
{
	if (!MoveIsLegal(h, v))
		return false;

	if (!mfHasMoved)
		mfHasMoved = true;
	mMoveCount++;
	mHPosition = h;
	mVPosition = v;
	return true;
}