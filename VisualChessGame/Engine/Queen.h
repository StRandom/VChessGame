#pragma once

#include "ChessPiece.h"

class Queen : public ChessPiece{
public:
	Queen() : ChessPiece() {}
	Queen(int h, int v) : ChessPiece(h, v) {}
	Queen(int h, int v, int id) : ChessPiece(h, v, id) {}
	virtual ~Queen() {}

	virtual char *getMoveAndCaptureDirections() { return "A8F8D8R8T8B8L8C8"; }
	virtual bool MoveIsLegal(int h, int v);
	virtual char* GetName() { return "QUEEN"; }
};
