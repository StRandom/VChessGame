#pragma once

#include <iostream>
#include "..\VisualMoveRecorder.h"

class ChessHistoryView : public Observer{
public:
	ChessHistoryView(VisualMoveRecorder* chb);
	virtual ~ChessHistoryView();

	virtual void Update(Subject* theChanchedSubject) { if (theChanchedSubject == mSubject) Draw(); }
	virtual void Draw();
private:
	VisualMoveRecorder* mSubject;
};
