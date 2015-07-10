#pragma once

#include "ChessPiece.h"

class Pawn : public ChessPiece{
public:
	Pawn() : ChessPiece() {}
	Pawn(int h, int v) : ChessPiece(h, v) {}
	Pawn(int h, int v, int id) : ChessPiece(h, v, id) {}
	virtual ~Pawn() {}
	
	virtual char *getMoveAndCaptureDirections() { return (mfHasMoved)?"F1S0D1A1":"F1F2S0D1A1"; }
	bool MoveIsLegal(int h, int v);
	char* GetName() { return "PAWN"; }
};
