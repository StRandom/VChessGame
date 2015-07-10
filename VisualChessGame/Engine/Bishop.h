#pragma once

#include "ChessPiece.h"

class Bishop : public ChessPiece{
public:
	Bishop() : ChessPiece() {}
	Bishop(int h, int v) : ChessPiece(h, v) {}
	Bishop(int h, int v, int id) : ChessPiece(h, v, id) {}
	virtual ~Bishop() {}
	
	virtual char *getMoveAndCaptureDirections() { return "A8D8C8T8"; }
	virtual bool MoveIsLegal(int h, int v);
	virtual char* GetName() { return "BISHOP"; }
};
