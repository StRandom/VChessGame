#pragma once

#include "ChessPiece.h"

class King : public ChessPiece{
public:
	King() : ChessPiece() {}
	King(int h, int v) : ChessPiece(h, v) {}
	King(int h, int v, int id) : ChessPiece(h, v, id) {}
	virtual ~King() {}

	virtual char *getMoveAndCaptureDirections() { return "F1A1D1R1C1T1B1L1"; }
	virtual bool MoveIsLegal(int h, int v);
	virtual char* GetName() { return "KING"; }
};
