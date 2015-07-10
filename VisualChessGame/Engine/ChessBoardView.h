#pragma once

#include <iostream>
#include "..\VisualChessBoard.h"

#define STR_PLAYER_WHITE	"White"
#define STR_PLAYER_BLACK	"Black"

#define STR_STATE_ONGOING	"Ongoing"
#define STR_STATE_CHECK		"Check"
#define STR_STATE_PRE_GAME	"Pre-Game"
#define STR_STATE_MATE		"Mate"
#define STR_STATE_DRAW		"Draw"

class ChessBoardView : public Observer{
public:
	ChessBoardView(VisualChessBoard* chb) { mSubject = chb; mSubject->Attach(this); }
	virtual ~ChessBoardView() { mSubject->Detach(this); }

	virtual void Update(Subject* theChanchedSubject) { if (theChanchedSubject == mSubject) Draw(); }
	virtual void Draw();
private:
	VisualChessBoard* mSubject;
};
