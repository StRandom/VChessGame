#pragma once

#include "ChessPiece.h"

class Rook : public ChessPiece{
public:
	Rook() : ChessPiece() {}
	Rook(int h, int v) : ChessPiece(h, v) {}
	Rook(int h, int v, int id) : ChessPiece(h, v, id) {}
	virtual ~Rook() {}

	virtual char *getMoveAndCaptureDirections() { return "F8R8B8L8"; }
	virtual bool MoveIsLegal(int h, int v);
	virtual char* GetName() { return "ROOK"; }
};
