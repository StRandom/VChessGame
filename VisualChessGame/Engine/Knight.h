#pragma once

#include "ChessPiece.h"

class Knight : public ChessPiece{
public:
	Knight() : ChessPiece() {}
	Knight(int h, int v) : ChessPiece(h, v) {}
	Knight(int h, int v, int id) : ChessPiece(h, v, id) {}
	virtual ~Knight() {}

	virtual char *getMoveAndCaptureDirections() { return "K1"; }
	virtual bool MoveIsLegal(int h, int v);
	virtual char* GetName() { return "KNIGHT"; }
};
