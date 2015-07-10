#pragma once

#include "Subject.h"
#include "ChessPiece.h"
#include "ChessPieceView.h"
#include "Player.h"
#include "..\VisualMoveRecorder.h"

#define MOVE_FAIL			0
#define MOVE_SUCCESS		1
#define MOVE_FAIL_CHECK		2
#define MOVE_ENDGAME		3

#define STATE_MOVE			0
#define STATE_CAPTURE		1
#define STATE_CASTLING_KS	2
#define STATE_CASTLING_QS	3
#define STATE_NORMAL		4
#define STATE_CHECK			5
#define STATE_CHECKMATE		6
#define STATE_DRAW			7
#define STATE_PROMOTION		8

#define FSTATE_NONE			0
#define FSTATE_PIECE		1		
#define FSTATE_MOVE			2
#define FSTATE_CAPTURE		3
#define FSTATE_CASTLING		4

class ChessBoard : public Subject {
public:
	ChessBoard();
	virtual ~ChessBoard();

	virtual void Init();
	ChessPiece* GetPieceAt(int h, int v){ return mChessBoard[v][h]; }
	ChessPiece* GetPiece(char* name, int plId);
	bool SetPieceAt(ChessPiece* piece, int h, int v);
	void Castling(int h, int v);
	bool isAttackField(int plId, int h, int v);
	Player* getCurrentPlayer() { return (plWhite->IsActive())?plWhite:plBlack; }
	int makeMove(ChessPiece* piece, int h, int v);
	int** getAvailableMoves(ChessPiece* piece);
	bool getFState(ChessPiece* piece, int vP2, int hP2);
	VisualMoveRecorder *getMoveList() { return mrList; }
	bool isNonZeroCountAvailableMoves(int playerId);
	bool decodeSimpleMove(char *inf);
	ChessPiece* getPieceFromCaptured();
	bool Redo();
	bool Undo();

	static int GetBoardSize() { return kBoardSize; }
protected:
	static const int kBoardSize = 8;
	static const int kPieceNumber = 32;
	ChessPiece*** mChessBoard;
	ChessPiece** mCapturedChess;
	ChessPieceView** mChessPieceView;
	Player* plWhite;
	Player* plBlack;
	VisualMoveRecorder *mrList;
};