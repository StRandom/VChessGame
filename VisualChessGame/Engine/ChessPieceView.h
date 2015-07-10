#pragma once
#include "ChessPiece.h"
#include "Observer.h"

class ChessPieceView : public Observer{
public:
	ChessPieceView(ChessPiece* cp) { mSubject = cp; mSubject->Attach(this); }
	virtual ~ChessPieceView() { mSubject->Detach(this); }

	virtual ChessPiece* getSubject() { return mSubject; }

	virtual void Update(Subject* theChanchedSubject) { if (theChanchedSubject == mSubject) Draw(); }
	virtual void Draw();
private:
	ChessPiece* mSubject;
};