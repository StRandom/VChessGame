#include "ChessBoard.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include <iostream>

ChessBoard::ChessBoard()
{
	mrList = new VisualMoveRecorder();
	mChessBoard = new ChessPiece**[kBoardSize];
	for (int i = 0; i < kBoardSize; i++)
		mChessBoard[i] = new ChessPiece*[kBoardSize];

	for (int i = 0; i < kBoardSize; i++)
		for (int j = 0; j < kBoardSize; j++)
			mChessBoard[i][j] = nullptr;

	mCapturedChess = new ChessPiece*[kPieceNumber];
	for (int i = 0; i < kPieceNumber; i++)
		mCapturedChess[i] = nullptr;

	mChessPieceView = new ChessPieceView*[kPieceNumber];
	plWhite = new Player("Mr. White", PLAYER_WHITE);
	plBlack = new Player("Mr. Black", PLAYER_BLACK);
	plWhite->SetActive(true);
}

void ChessBoard::Init()
{
	for (int i = 0; i < kBoardSize; i++){
		mChessBoard[1][i] = new Pawn(i, 1, PLAYER_BLACK);
		mChessBoard[6][i] = new Pawn(i, 6, PLAYER_WHITE);
		mChessPieceView[2*i] = new ChessPieceView(mChessBoard[1][i]);
		mChessPieceView[2*i+1] = new  ChessPieceView(mChessBoard[6][i]);
	}
	mChessBoard[0][0] = new Rook(0, 0, PLAYER_BLACK);
	mChessBoard[7][0] = new Rook(0, 7, PLAYER_WHITE);
	mChessBoard[0][7] = new Rook(7, 0, PLAYER_BLACK);
	mChessBoard[7][7] = new Rook(7, 7, PLAYER_WHITE);
	mChessPieceView[2 * kBoardSize] = new ChessPieceView(mChessBoard[0][0]);
	mChessPieceView[2 * kBoardSize + 1] = new  ChessPieceView(mChessBoard[7][0]);
	mChessPieceView[2 * kBoardSize + 2] = new ChessPieceView(mChessBoard[0][7]);
	mChessPieceView[2 * kBoardSize + 3] = new  ChessPieceView(mChessBoard[7][7]);

	mChessBoard[0][1] = new Knight(1, 0, PLAYER_BLACK);
	mChessBoard[7][1] = new Knight(1, 7, PLAYER_WHITE);
	mChessBoard[0][6] = new Knight(6, 0, PLAYER_BLACK);
	mChessBoard[7][6] = new Knight(6, 7, PLAYER_WHITE);
	mChessPieceView[2 * kBoardSize + 4] = new ChessPieceView(mChessBoard[0][1]);
	mChessPieceView[2 * kBoardSize + 5] = new  ChessPieceView(mChessBoard[7][1]);
	mChessPieceView[2 * kBoardSize + 6] = new ChessPieceView(mChessBoard[0][6]);
	mChessPieceView[2 * kBoardSize + 7] = new  ChessPieceView(mChessBoard[7][6]);

	mChessBoard[0][2] = new Bishop(2, 0, PLAYER_BLACK);
	mChessBoard[7][2] = new Bishop(2, 7, PLAYER_WHITE);
	mChessBoard[0][5] = new Bishop(5, 0, PLAYER_BLACK);
	mChessBoard[7][5] = new Bishop(5, 7, PLAYER_WHITE);
	mChessPieceView[2 * kBoardSize + 8] = new ChessPieceView(mChessBoard[0][2]);
	mChessPieceView[2 * kBoardSize + 9] = new  ChessPieceView(mChessBoard[7][2]);
	mChessPieceView[2 * kBoardSize + 10] = new ChessPieceView(mChessBoard[0][5]);
	mChessPieceView[2 * kBoardSize + 11] = new  ChessPieceView(mChessBoard[7][5]);

	mChessBoard[0][3] = new Queen(3, 0, PLAYER_BLACK);
	mChessBoard[7][3] = new Queen(3, 7, PLAYER_WHITE);
	mChessPieceView[2 * kBoardSize + 12] = new ChessPieceView(mChessBoard[0][3]);
	mChessPieceView[2 * kBoardSize + 13] = new  ChessPieceView(mChessBoard[7][3]);

	mChessBoard[0][4] = new King(4, 0, PLAYER_BLACK);
	mChessBoard[7][4] = new King(4, 7, PLAYER_WHITE);
	mChessPieceView[2 * kBoardSize + 14] = new ChessPieceView(mChessBoard[0][4]);
	mChessPieceView[2 * kBoardSize + 15] = new  ChessPieceView(mChessBoard[7][4]);
	Notify();
}

ChessBoard::~ChessBoard()
{
	if (mrList)
		delete mrList;
	for (int i = 0; i < kPieceNumber; i++){
		if (mChessPieceView[i])
			delete mChessPieceView[i];
	}
	delete[] mChessPieceView;

	for (int i = 0; i < kBoardSize; i++)
	{
		for (int j = 0; j < kBoardSize; j++){
			if (mChessBoard[i][j])
				delete mChessBoard[i][j];
		}
	}
	for (int i = 0; i < kBoardSize; i++){
		if (mChessBoard[i])
			delete[] mChessBoard[i];
	}
	if (mChessBoard)
		delete[] mChessBoard;
	for (int i = 0; i < kPieceNumber; i++){
		if (mCapturedChess[i])
			delete mCapturedChess[i];
	}
	delete[] mCapturedChess;
	delete plWhite;
	delete plBlack;
}

bool ChessBoard::SetPieceAt(ChessPiece* piece, int h, int v)
{
	if (!piece)
		return false;
	if (piece->getPlayerId() != getCurrentPlayer()->getId())
		return false;
	int oldH = piece->GetHPosition();
	int oldV = piece->GetVPosition();
	if (!piece->Move(h, v))
		return false;
	if (mChessBoard[v][h]){
		mChessBoard[v][h]->SetCapruted(true);
		int t = 0;
		while (mCapturedChess[t] != nullptr)
			t++;
		mCapturedChess[t] = mChessBoard[v][h];
		/*for (int i = 0; i < kPieceNumber; i++){
			if (mChessPieceView[i]){
				if (mChessPieceView[i]->getSubject() == mChessBoard[v][h]){
					delete mChessPieceView[i];
					mChessPieceView[i] = nullptr;
				}
			}
		}*/
		//delete mChessBoard[v][h];
	}
	mChessBoard[v][h] = piece;
	mChessBoard[oldV][oldH] = nullptr;
	plWhite->SetActive(!plWhite->IsActive());
	plBlack->SetActive(!plBlack->IsActive());
	return true;
}

void ChessBoard::Castling(int h, int v)
{
	if (getCurrentPlayer()->getId() == PLAYER_WHITE){
		ChessPiece* king = GetPieceAt(4, 7);
		int oldH = king->GetHPosition();
		int oldV = king->GetVPosition();
		king->Move(h, v);
		Notify();
		mChessBoard[v][h] = king;
		mChessBoard[oldV][oldH] = nullptr;
		ChessPiece* rook = (h < 4) ? GetPieceAt(0, 7) : GetPieceAt(7, 7);
		int t = (h < 4) ? 3 : 5;
		oldH = rook->GetHPosition();
		oldV = rook->GetVPosition();
		rook->Move(t, 7);
		Notify();
		mChessBoard[7][t] = rook;
		mChessBoard[oldV][oldH] = nullptr;
	}
	else{
		ChessPiece* king = GetPieceAt(4, 0);
		int oldH = king->GetHPosition();
		int oldV = king->GetVPosition();
		king->Move(h, v);
		Notify();
		mChessBoard[v][h] = king;
		mChessBoard[oldV][oldH] = nullptr;
		ChessPiece* rook = (h < 4) ? GetPieceAt(0, 0) : GetPieceAt(7, 0);
		int t = (h < 4) ? 3 : 5;
		oldH = rook->GetHPosition();
		oldV = rook->GetVPosition();
		rook->Move(t, 0);
		Notify();
		mChessBoard[0][t] = rook;
		mChessBoard[oldV][oldH] = nullptr;
	}
	plWhite->SetActive(!plWhite->IsActive());
	plBlack->SetActive(!plBlack->IsActive());
	return; 
}

ChessPiece* ChessBoard::GetPiece(char* name, int plId)
{
	ChessPiece* piece = nullptr;
	bool fSearch = true;
	for (int i = 0; i < kBoardSize && fSearch; i++){
		for (int j = 0; j < kBoardSize && fSearch; j++){
			ChessPiece* tmp = GetPieceAt(j, i);
			if (tmp){
				if ((tmp->getPlayerId() == plId) &&
					(strcmp(tmp->GetName(), name) == 0)){
					fSearch = false;
					piece = tmp;
				}
			}
		}
	}
	return piece;
}

bool ChessBoard::isAttackField(int plId, int h, int v)
{
	bool res = false;
	ChessPiece* piece;
	// The Horizontal Line
	int h0 = h, v0 = v;
	bool favailable = true;
	while (favailable && (h0 > 0) && (!res)){
		h0--;
		piece = mChessBoard[v0][h0];
		if (piece){
			if (piece->getPlayerId() != plId){
				if ((strcmp(piece->GetName(), "ROOK") == 0) ||
					(strcmp(piece->GetName(), "QUEEN") == 0) ||
					(strcmp(piece->GetName(), "KING") == 0)){
					res = true;
					if ((strcmp(piece->GetName(), "KING") == 0) && (h - h0) > 1)
						res = false;
				}
			}
			favailable = false;
		}
	}
	h0 = h; v0 = v;
	favailable = true;
	while (favailable && (h0 < 7) && (!res)){
		h0++;
		piece = mChessBoard[v0][h0];
		if (piece){
			if (piece->getPlayerId() != plId){
				if ((strcmp(piece->GetName(), "ROOK") == 0) ||
					(strcmp(piece->GetName(), "QUEEN") == 0) ||
					(strcmp(piece->GetName(), "KING") == 0)){
					res = true;
					if ((strcmp(piece->GetName(), "KING") == 0) && (h0 - h) > 1)
						res = false;
				}
			}
			favailable = false;
		}
	}
	// The Vertical Line
	h0 = h; v0 = v;
	favailable = true;
	while (favailable && (v0 > 0) && (!res)){
		v0--;
		piece = mChessBoard[v0][h0];
		if (piece){
			if (piece->getPlayerId() != plId){
				if ((strcmp(piece->GetName(), "ROOK") == 0) ||
					(strcmp(piece->GetName(), "QUEEN") == 0) ||
					(strcmp(piece->GetName(), "KING") == 0)){
					res = true;
					if ((strcmp(piece->GetName(), "KING") == 0) && (v - v0) > 1)
						res = false;
				}
			}
			favailable = false;
		}
	}
	h0 = h; v0 = v;
	favailable = true;
	while (favailable && (v0 < 7) && (!res)){
		v0++;
		piece = mChessBoard[v0][h0];
		if (piece){
			if (piece->getPlayerId() != plId){
				if ((strcmp(piece->GetName(), "ROOK") == 0) ||
					(strcmp(piece->GetName(), "QUEEN") == 0) ||
					(strcmp(piece->GetName(), "KING") == 0)){
					res = true;
					if ((strcmp(piece->GetName(), "KING") == 0) && (v0 - v) > 1)
						res = false;
				}
			}
			favailable = false;
		}
	}
	// The Diagonal Line (left-top to right-bottom) (lt-center)
	h0 = h; v0 = v;
	favailable = true;
	while (favailable && (v0 > 0) && (h0 > 0) && (!res)){
		v0--; h0--;
		piece = mChessBoard[v0][h0];
		if (piece){
			if (piece->getPlayerId() != plId){
				if ((strcmp(piece->GetName(), "BISHOP") == 0) ||
					(strcmp(piece->GetName(), "QUEEN") == 0) ||
					(strcmp(piece->GetName(), "KING") == 0) ||
					(strcmp(piece->GetName(), "PAWN") == 0)){
					res = true;
					if (((strcmp(piece->GetName(), "KING") == 0) || (strcmp(piece->GetName(), "PAWN") == 0)) && ((v - v0) > 1) && (h - h0 > 1))
						res = false;
				}
			}
			favailable = false;
		}
	}
	// The Diagonal Line (left-top to right-bottom) (center-rb)
	h0 = h; v0 = v;
	favailable = true;
	while (favailable && (v0 < 7) && (h0 < 7) && (!res)){
		v0++; h0++;
		piece = mChessBoard[v0][h0];
		if (piece){
			if (piece->getPlayerId() != plId){
				if ((strcmp(piece->GetName(), "BISHOP") == 0) ||
					(strcmp(piece->GetName(), "QUEEN") == 0) ||
					(strcmp(piece->GetName(), "KING") == 0) ||
					(strcmp(piece->GetName(), "PAWN") == 0)){
					res = true;
					if (((strcmp(piece->GetName(), "KING") == 0) || (strcmp(piece->GetName(), "PAWN") == 0)) && ((v0 - v) > 1) && (h0 - h > 1))
						res = false;
				}
			}
			favailable = false;
		}
	}
	// The Diagonal Line (left-bottom to right-top) (lb-center)
	h0 = h; v0 = v;
	favailable = true;
	while (favailable && (v0 < 7) && (h0 > 0) && (!res)){
		v0++; h0--;
		piece = mChessBoard[v0][h0];
		if (piece){
			if (piece->getPlayerId() != plId){
				if ((strcmp(piece->GetName(), "BISHOP") == 0) ||
					(strcmp(piece->GetName(), "QUEEN") == 0) ||
					(strcmp(piece->GetName(), "KING") == 0) ||
					(strcmp(piece->GetName(), "PAWN") == 0)){
					res = true;
					if (((strcmp(piece->GetName(), "KING") == 0) || (strcmp(piece->GetName(), "PAWN") == 0)) && ((v0 - v) > 1) && (h - h0 > 1))
						res = false;
				}
			}
			favailable = false;
		}
	}
	// The Diagonal Line (left-bottom to right-top) (center-rt)
	h0 = h; v0 = v;
	favailable = true;
	while (favailable && (v0 > 0) && (h0 < 7) && (!res)){
		v0--; h0++;
		piece = mChessBoard[v0][h0];
		if (piece){
			if (piece->getPlayerId() != plId){
				if ((strcmp(piece->GetName(), "BISHOP") == 0) ||
					(strcmp(piece->GetName(), "QUEEN") == 0) ||
					(strcmp(piece->GetName(), "KING") == 0) ||
					(strcmp(piece->GetName(), "PAWN") == 0)){
					res = true;
					if (((strcmp(piece->GetName(), "KING") == 0) || (strcmp(piece->GetName(), "PAWN") == 0)) && ((v - v0) > 1) && (h0 - h > 1))
						res = false;
				}
			}
			favailable = false;
		}
	}
	// Knight move (+2 +1)
	h0 = h + 1; v0 = v + 2;
	if ((h0 < 8) && (v0 < 8) && (!res)){
		piece = mChessBoard[v0][h0];
		if (piece){
			if ((strcmp(piece->GetName(), "KNIGHT") == 0) && 
				piece->getPlayerId() != plId){
				res = true;
			}
		}
	}
	// Knight move (+2 -1)
	h0 = h - 1; v0 = v + 2;
	if ((h0 > 0) && (v0 < 8) && (!res)){
		piece = mChessBoard[v0][h0];
		if (piece){
			if ((strcmp(piece->GetName(), "KNIGHT") == 0) &&
				piece->getPlayerId() != plId){
				res = true;
			}
		}
	}
	// Knight move (-2 -1)
	h0 = h - 1; v0 = v - 2;
	if ((h0 > 0) && (v0 > 0) && (!res)){
		piece = mChessBoard[v0][h0];
		if (piece){
			if ((strcmp(piece->GetName(), "KNIGHT") == 0) &&
				piece->getPlayerId() != plId){
				res = true;
			}
		}
	}
	// Knight move (-2 +1)
	h0 = h + 1; v0 = v - 2;
	if ((h0 < 8) && (v0 > 0) && (!res)){
		piece = mChessBoard[v0][h0];
		if (piece){
			if ((strcmp(piece->GetName(), "KNIGHT") == 0) &&
				piece->getPlayerId() != plId){
				res = true;
			}
		}
	}
	// Knight move (+1 +2)
	h0 = h + 2; v0 = v + 1;
	if ((h0 < 8) && (v0 < 8) && (!res)){
		piece = mChessBoard[v0][h0];
		if (piece){
			if ((strcmp(piece->GetName(), "KNIGHT") == 0) &&
				piece->getPlayerId() != plId){
				res = true;
			}
		}
	}
	// Knight move (+1 -2)
	h0 = h - 2; v0 = v + 1;
	if ((h0 > 0) && (v0 < 8) && (!res)){
		piece = mChessBoard[v0][h0];
		if (piece){
			if ((strcmp(piece->GetName(), "KNIGHT") == 0) &&
				piece->getPlayerId() != plId){
				res = true;
			}
		}
	}
	// Knight move (-1 -2)
	h0 = h - 2; v0 = v - 1;
	if ((h0 > 0) && (v0 > 0) && (!res)){
		piece = mChessBoard[v0][h0];
		if (piece){
			if ((strcmp(piece->GetName(), "KNIGHT") == 0) &&
				piece->getPlayerId() != plId){
				res = true;
			}
		}
	}
	// Knight move (-1 +2)
	h0 = h + 2; v0 = v - 1;
	if ((h0 < 8) && (v0 > 0) && (!res)){
		piece = mChessBoard[v0][h0];
		if (piece){
			if ((strcmp(piece->GetName(), "KNIGHT") == 0) &&
				piece->getPlayerId() != plId){
				res = true;
			}
		}
	}
	return res;
}

bool ChessBoard::getFState(ChessPiece* piece, int vP2, int hP2){
	bool fres = false;
	int vP1 = piece->GetVPosition();
	int hP1 = piece->GetHPosition();
	mChessBoard[vP1][hP1] = nullptr;
	ChessPiece* tmp = mChessBoard[vP2][hP2];
	mChessBoard[vP2][hP2] = piece;
	ChessPiece* king;
	if (tmp){
		if ((strcmp(tmp->GetName(), "KING") == 0) && tmp->getPlayerId() == piece->getPlayerId())
			king = tmp;
		else
			king = GetPiece("KING", piece->getPlayerId());
	}
	else
	{
		king = GetPiece("KING", piece->getPlayerId());
	}
	int vPos = king->GetVPosition();
	int hPos = king->GetHPosition();
	if (strcmp(piece->GetName(), "KING") == 0){
		vPos = vP2;
		hPos = hP2;
		king = piece;
	}
	if (isAttackField(king->getPlayerId(), hPos, vPos))
		fres = true;
	mChessBoard[vP1][hP1] = piece;
	mChessBoard[vP2][hP2] = tmp;
	return fres;
}

int** ChessBoard::getAvailableMoves(ChessPiece* piece)
{
	int **avMove = new int*[8];
	for (int i = 0; i < kBoardSize; i++)
		avMove[i] = new int[8];
	for (int i = 0; i < kBoardSize; i++)
		for (int j = 0; j < kBoardSize; j++)
			avMove[i][j] = FSTATE_NONE;
	if (piece->getPlayerId() != getCurrentPlayer()->getId())
		return avMove;
	char *strMoveCode = piece->getMoveAndCaptureDirections();
	int vP = piece->GetVPosition();
	int hP = piece->GetHPosition();
	avMove[vP][hP] = FSTATE_PIECE;
	int p = 0;
	int n = 0;
	bool fpawn = false;
	bool fpawncap = false;
	bool fknight = false;
	if (strcmp(piece->GetName(), "PAWN") == 0)
		fpawn = true;
	while (strMoveCode[p] != 0){
		n = 0;
		bool fcont = true;
		int dH = 0; 
		int dV = 0;
		switch (strMoveCode[p + 1]){
		case '1':
			n = 1;
			break;
		case '2':
			n = 2;
			break;
		case '8':
			n = 8;
			break;
		case '0':
			// S0 - Pawn capture directions
			n = 0;
			fpawncap = true;
			break;
		}
		switch (strMoveCode[p]){
		case 'F':
			dV = (piece->getPlayerId() == PLAYER_WHITE) ? -1 : 1;
			dH = 0;
			break;
		case 'D':
			dV = (piece->getPlayerId() == PLAYER_WHITE) ? -1 : 1;
			dH = 1;
			break;
		case 'A':
			dV = (piece->getPlayerId() == PLAYER_WHITE) ? -1 : 1;
			dH = -1;
			break;
		case 'C':
			dV = (piece->getPlayerId() == PLAYER_WHITE) ? 1 : -1;
			dH = -1;
			break;
		case 'R':
			dV = 0;
			dH = 1;
			break;
		case 'T':
			dV = (piece->getPlayerId() == PLAYER_WHITE) ? 1 : -1;
			dH = 1;
			break;
		case 'B':
			dV = (piece->getPlayerId() == PLAYER_WHITE) ? 1 : -1;
			dH = 0;
			break;
		case 'L':
			dV = 0;
			dH = -1;
			break;
		case 'K':
			dV = 2;
			dH = 1;
			fknight = true;
			break;
		case 'S':
			// S0 - Pawn capture directions
			dV = 0;
			dH = 0;
			break;
		}
		if (fknight){
			// Knight
			if ((hP + 2 < 8) && (vP + 1 < 8)){
				if (GetPieceAt(hP + 2, vP + 1)){
					if (GetPieceAt(hP + 2, vP + 1)->getPlayerId() != piece->getPlayerId())
						avMove[vP + 1][hP + 2] = FSTATE_CAPTURE;
				}
				else{
					avMove[vP + 1][hP + 2] = FSTATE_MOVE;
				}
				if (getFState(piece, vP + 1, hP + 2))
					avMove[vP + 1][hP + 2] = FSTATE_NONE;
			}
			if ((hP + 2 < 8) && (vP - 1 >= 0)){
				if (GetPieceAt(hP + 2, vP - 1)){
					if (GetPieceAt(hP + 2, vP - 1)->getPlayerId() != piece->getPlayerId())
						avMove[vP - 1][hP + 2] = FSTATE_CAPTURE;
				}
				else{
					avMove[vP - 1][hP + 2] = FSTATE_MOVE;
				}
				if (getFState(piece, vP - 1, hP + 2))
					avMove[vP - 1][hP + 2] = FSTATE_NONE;
			}
			if ((hP - 2 >= 0) && (vP + 1 < 8)){
				if (GetPieceAt(hP - 2, vP + 1)){
					if (GetPieceAt(hP - 2, vP + 1)->getPlayerId() != piece->getPlayerId())
						avMove[vP + 1][hP - 2] = FSTATE_CAPTURE;
				}
				else{
					avMove[vP + 1][hP - 2] = FSTATE_MOVE;
				}
				if (getFState(piece, vP + 1, hP - 2))
					avMove[vP + 1][hP - 2] = FSTATE_NONE;
			}
			if ((hP - 2 >= 0) && (vP - 1 >= 0)){
				if (GetPieceAt(hP - 2, vP - 1)){
					if (GetPieceAt(hP - 2, vP - 1)->getPlayerId() != piece->getPlayerId())
						avMove[vP - 1][hP - 2] = FSTATE_CAPTURE;
				}
				else{
					avMove[vP - 1][hP - 2] = FSTATE_MOVE;
				}
				if (getFState(piece, vP - 1, hP - 2))
					avMove[vP - 1][hP - 2] = FSTATE_NONE;
			}
			if ((hP + 1 < 8) && (vP + 2 < 8)){
				if (GetPieceAt(hP + 1, vP + 2)){
					if (GetPieceAt(hP + 1, vP + 2)->getPlayerId() != piece->getPlayerId())
						avMove[vP + 2][hP + 1] = FSTATE_CAPTURE;
				}
				else{
					avMove[vP + 2][hP + 1] = FSTATE_MOVE;
				}
				if (getFState(piece, vP + 2, hP + 1))
					avMove[vP + 2][hP + 1] = FSTATE_NONE;
			}
			if ((hP + 1 < 8) && (vP - 2 >= 0)){
				if (GetPieceAt(hP + 1, vP - 2)){
					if (GetPieceAt(hP + 1, vP - 2)->getPlayerId() != piece->getPlayerId())
						avMove[vP - 2][hP + 1] = FSTATE_CAPTURE;
				}
				else{
					avMove[vP - 2][hP + 1] = FSTATE_MOVE;
				}
				if (getFState(piece, vP - 2, hP + 1))
					avMove[vP - 2][hP + 1] = FSTATE_NONE;
			}
			if ((hP - 1 >= 0) && (vP + 2 < 8)){
				if (GetPieceAt(hP - 1, vP + 2)){
					if (GetPieceAt(hP - 1, vP + 2)->getPlayerId() != piece->getPlayerId())
						avMove[vP + 2][hP - 1] = FSTATE_CAPTURE;
				}
				else{
					avMove[vP + 2][hP - 1] = FSTATE_MOVE;
				}
				if (getFState(piece, vP + 2, hP - 1))
					avMove[vP + 2][hP - 1] = FSTATE_NONE;
			}
			if ((hP - 1 >= 0) && (vP - 2 >= 0)){
				if (GetPieceAt(hP - 1, vP - 2)){
					if (GetPieceAt(hP - 1, vP - 2)->getPlayerId() != piece->getPlayerId())
						avMove[vP - 2][hP - 1] = FSTATE_CAPTURE;
				}
				else{
					avMove[vP - 2][hP - 1] = FSTATE_MOVE;
				}
				if (getFState(piece, vP - 2, hP - 1))
					avMove[vP - 2][hP - 1] = FSTATE_NONE;
			}
		}
		else{
			if (fpawn){
				// Pawn
				if (fpawncap){
					if ((hP + dH >= 0) && (vP + dV >= 0) &&
						(hP + dH < 8) && (vP + dV < 8)){
						if (GetPieceAt(hP + dH, vP + dV)){
							if (GetPieceAt(hP + dH, vP + dV)->getPlayerId() != piece->getPlayerId())
								avMove[vP + dV][hP + dH] = FSTATE_CAPTURE;
						}
						if (getFState(piece, vP + dV, hP + dH))
							avMove[vP +dV][hP + dH] = FSTATE_NONE;
					}
				}else{
					for (int li = 0; li < n && fcont; li++){
						if ((hP + dH * (li + 1) >= 0) && (vP + dV * (li + 1) >= 0) &&
							(hP + dH * (li + 1) < 8) && (vP + dV * (li + 1) < 8)){
							if (GetPieceAt(hP + dH * (li + 1), vP + dV * (li + 1))){
								if (GetPieceAt(hP + dH * (li + 1), vP + dV * (li + 1))->getPlayerId() != piece->getPlayerId())
									avMove[vP + dV * (li + 1)][hP + dH * (li + 1)] = FSTATE_NONE;
								fcont = false;
							}
							else{
								avMove[vP + dV * (li + 1)][hP + dH * (li + 1)] = FSTATE_MOVE;
							}
							if (getFState(piece, vP + dV * (li + 1), hP + dH * (li + 1)))
								avMove[vP + dV * (li + 1)][hP + dH * (li + 1)] = FSTATE_NONE;
						}
					}
				}
			}else{
				// King, Queen, Bishop, Rook
				for (int li = 0; li < n && fcont; li++){
					if ((hP + dH * (li + 1) >= 0) && (vP + dV * (li + 1) >= 0) &&
						(hP + dH * (li + 1) < 8) && (vP + dV * (li + 1) < 8)){
						if (GetPieceAt(hP + dH * (li + 1), vP + dV * (li + 1))){
							if (GetPieceAt(hP + dH * (li + 1), vP + dV * (li + 1))->getPlayerId() != piece->getPlayerId())
								avMove[vP + dV * (li + 1)][hP + dH * (li + 1)] = FSTATE_CAPTURE;
							fcont = false;
						}
						else{
							avMove[vP + dV * (li + 1)][hP + dH * (li + 1)] = FSTATE_MOVE;
						}
						if (getFState(piece, vP + dV * (li + 1), hP + dH * (li + 1)))
							avMove[vP + dV * (li + 1)][hP + dH * (li + 1)] = FSTATE_NONE;
					}
				}
				if ((strcmp(piece->GetName(), "KING") == 0) &&
					(piece->HasMoved() == false)){
					if (piece->getPlayerId() == PLAYER_WHITE){
						ChessPiece* rook = GetPieceAt(0, 7);
						if (rook){
							if (rook->HasMoved() == false){
								if ((GetPieceAt(3, 7) == nullptr) && (GetPieceAt(2, 7) == nullptr)){
									if ((!isAttackField(piece->getPlayerId(), 3, 7)) &&
										(!isAttackField(piece->getPlayerId(), 2, 7)))
										avMove[7][2] = FSTATE_CASTLING;
								}
							}
						}
						rook = GetPieceAt(7, 7);
						if (rook){
							if (rook->HasMoved() == false){
								if ((GetPieceAt(5, 7) == nullptr) && (GetPieceAt(6, 7) == nullptr)){
									if ((!isAttackField(piece->getPlayerId(), 5, 7)) &&
										(!isAttackField(piece->getPlayerId(), 6, 7)))
										avMove[7][6] = FSTATE_CASTLING;
								}
							}
						}
					}
					else{
						ChessPiece* rook = GetPieceAt(0, 0);
						if (rook){
							if (rook->HasMoved() == false){
								if ((GetPieceAt(3, 0) == nullptr) && (GetPieceAt(2, 0) == nullptr)){
									if ((!isAttackField(piece->getPlayerId(), 3, 0)) &&
										(!isAttackField(piece->getPlayerId(), 2, 0)))
										avMove[0][2] = FSTATE_CASTLING;
								}
							}
						}
						rook = GetPieceAt(7, 0);
						if (rook){
							if (rook->HasMoved() == false){
								if ((GetPieceAt(5, 0) == nullptr) && (GetPieceAt(6, 0) == nullptr)){
									if ((!isAttackField(piece->getPlayerId(), 5, 0)) &&
										(!isAttackField(piece->getPlayerId(), 6, 0)))
										avMove[0][6] = FSTATE_CASTLING;
								}
							}
						}
					}

				}
			}
		}
		p+=2;
	}
	return avMove; 
}

bool ChessBoard::isNonZeroCountAvailableMoves(int playerId)
{
	int curPlayer = playerId;
	bool res = false;
	ChessPiece* piece = nullptr;
	int i = 0, j = 0;
	while (!res && (i < kBoardSize)){
		j = 0;
		while (!res && (j < kBoardSize)){
			piece = GetPieceAt(j, i);
			if (piece){
				if (piece->getPlayerId() == curPlayer){
					int **avMove = getAvailableMoves(piece);
					int p = 0, q = 0;
					while (!res && (p < kBoardSize)){
						q = 0;
						while (!res && (q < kBoardSize)){
							if ((avMove[p][q] == FSTATE_CAPTURE) || (avMove[p][q] == FSTATE_MOVE))
								res = true;
							q++;
						}
						p++;
					}
					for (int i = 0; i < kBoardSize; i++)
						delete[] avMove[i];
					delete[] avMove;
				}
			}
			j++;
		}
		i++;
	}
	return res;
}

int ChessBoard::makeMove(ChessPiece* piece, int h, int v)
{
	if (!piece)
		return MOVE_FAIL;
	if (piece->getPlayerId() != getCurrentPlayer()->getId())
		return MOVE_FAIL;
	if (getFState(piece, v, h))
		return MOVE_FAIL_CHECK;
	int** avMove = getAvailableMoves(piece);
	int q = avMove[v][h];
	for (int i = 0; i < kBoardSize; i++)
		delete[] avMove[i];
	delete[] avMove;
	if (q == FSTATE_NONE) 
		return MOVE_FAIL;
	if (q == FSTATE_PIECE)
		return MOVE_FAIL;
	if (q == FSTATE_CASTLING){
		Castling(h, v);
		if (mrList->getCurrentId() != mrList->getMoveCount()){
			mrList->DeleteMovesToID(mrList->getCurrentId() - 1);
		}
		mrList->AddSimpleMove(((h < 4)?"0-0-0":"0-0"), (piece->getPlayerId() == PLAYER_BLACK));
		return MOVE_SUCCESS;
	}
	int hOld = piece->GetHPosition();
	int vOld = piece->GetVPosition();
	if (SetPieceAt(piece, h, v)){
		ChessPiece* king = GetPiece("KING", getCurrentPlayer()->getId());
		int vPos = king->GetVPosition();
		int hPos = king->GetHPosition();
		if (isAttackField(king->getPlayerId(), hPos, vPos))
			getCurrentPlayer()->SetChecked(true);
		else
			getCurrentPlayer()->SetChecked(false);
		char inf[MAX_INFO_SIZE];
		inf[0] = (strcmp(piece->GetName(), "KNIGHT") == 0) ? 'N' : piece->GetName()[0];
		inf[1] = char(hOld + 97);
		inf[2] = char(56 - vOld);
		inf[3] = (q == FSTATE_CAPTURE) ? 'x' : '-';
		inf[4] = char(h + 97);
		inf[5] = char(56 - v);
		bool f = isNonZeroCountAvailableMoves(getCurrentPlayer()->getId());
		if (getCurrentPlayer()->IsChecked()){
			inf[6] = f?'+':'#';
			inf[7] = 0;
		}
		else{
			inf[6] = 0;
		}
		if (mrList->getCurrentId() != mrList->getMoveCount()){
			mrList->DeleteMovesToID(mrList->getCurrentId());
		}
		if (getCurrentPlayer()->getId() == PLAYER_BLACK){
			
		}
		mrList->AddSimpleMove(inf, (piece->getPlayerId() == PLAYER_BLACK));
		Notify();
		if (!f){
			getCurrentPlayer()->SetNoAvailableMoves(true);
			if (getCurrentPlayer()->IsChecked()){
				if (getCurrentPlayer()->getId() == PLAYER_BLACK){
					// WHITE WON
					if (mrList->getCurrentId() != mrList->getMoveCount()){
						mrList->DeleteMovesToID(mrList->getCurrentId());
					}
					mrList->AddSimpleMove("1-0", true);
					Notify();
				}
				else{
					// BLACK WON
					if (mrList->getCurrentId() != mrList->getMoveCount()){
						mrList->DeleteMovesToID(mrList->getCurrentId());
					}
					mrList->AddSimpleMove("0-1", false);
					Notify();
				}
			}
			else{
				// DRAW
				if (mrList->getCurrentId() != mrList->getMoveCount()){
					mrList->DeleteMovesToID(mrList->getCurrentId());
				}
				mrList->AddSimpleMove("1/2-1/2", (getCurrentPlayer()->getId() == PLAYER_BLACK));
				Notify();
			}
			return MOVE_ENDGAME;
		}
		return MOVE_SUCCESS;
	}
	return MOVE_FAIL;
}

bool ChessBoard::Redo()
{
	if (mrList->getCurrentId() > mrList->getMoveCount())
		return false;
	//if (mrList->getCurrentId() <= 0){
	//	mrList->setCurrentId(1);
	//	//Redo();
	//	//return true;
	//}
	bool fMate = false;
	bool fWhite = (getCurrentPlayer()->getId() == PLAYER_WHITE);
	if (fWhite){
		if (mrList->getCurrentId() == mrList->getMoveCount()){
			return false; 
		}
		mrList->setCurrentId(mrList->getCurrentId() + 1);
	}
	SimpleMove *sm = mrList->getSimpleMove(mrList->getCurrentId());
	char info[MAX_INFO_SIZE];
	int i = 0, infoLenght = 0;
	if (fWhite){
		while ((sm->info[i] != ' ') && (sm->info[i] != 0)){
			info[infoLenght] = sm->info[i];
			i++; infoLenght++;
		}
		info[infoLenght] = 0;
	}
	else{
		while (sm->info[i] != ' '){
			if (sm->info[i] == 0){
				// TODO : 
				return false;
			}
			i++;
		}
		i++;
		infoLenght = 0;
		while (sm->info[i] != 0){
			info[infoLenght] = sm->info[i];
			i++; infoLenght++;
		}
		info[infoLenght] = 0;
	}
	int hFrom = -1, hTo = -1, vFrom = -1, vTo = -1;
	char chP = 0, chPP = 0;
	int fMoveState = STATE_MOVE;
	int fCheckState = STATE_NORMAL;
	switch (info[0]){
	case '0':
		if (info[1] != '-')
			return false;
		else {
			if (info[2] == '0'){
				if (info[3] == '-'){
					if (info[4] == '0') {
						if (info[5] == ' ' || info[5] == 0){
							// queenside Castling "0-0-0"
							fMoveState = STATE_CASTLING_QS;
						}
						else {
							// Error in the SimpleMove
							return false;
						}
					}
					else {
						// Error in the SimpleMove
						return false;
					}
				}
				else if (info[3] == ' ' || info[3] == 0){
					// kingside Castling "0-0"
					fMoveState = STATE_CASTLING_KS;
				}
				else{
					// Error in the SimpleMove
					return false;
				}
			}
			else if (info[2] == '1'){
				// BLACK WON "0-1"
				fCheckState = STATE_CHECKMATE;
				fMoveState = STATE_CHECKMATE;
			}
			else {
				// Error in the SimpleMove
				return false;
			}
		}
		break;
	case '1':
		if (info[1] == '/'){
			// DRAW "1/2-1/2"
			fCheckState = STATE_DRAW;
			fMoveState = STATE_DRAW;
		}
		else if (info[1] == '-' && info[2] == '0'){
			// WHITE WON "1-0"
			fCheckState = STATE_CHECKMATE;
			fMoveState = STATE_CHECKMATE;
		}
		else {
			// Error in the SimpleMove
			return false;
		}
		break;
	case 'P':
	case 'R':
	case 'N':
	case 'B':
	case 'K':
	case 'Q':
		chP = info[0];
		hFrom = info[1] - 97;
		vFrom = 56 - info[2];
		switch (info[3]){
		case '-':
			// Move
			// TODO:
			fMoveState = STATE_MOVE;
			hTo = info[4] - 97;
			vTo = 56 - info[5];
			switch (info[6])
			{
			case '+':
				fCheckState = STATE_CHECK;
				break;
			case ' ':
				fCheckState = STATE_NORMAL;
				break;
			case '#':
				fCheckState = STATE_CHECK;
				fMate = true;
				break;
			case 0:
				fCheckState = STATE_NORMAL;
				break;
			default:
				// Error in the SimpleMove
				return false;
			}
			break;
		case 'x':
			// Capture
			// TODO:
			fMoveState = STATE_CAPTURE;
			hTo = info[4] - 97;
			vTo = 56 - info[5];
			switch (info[6])
			{
			case '+':
				fCheckState = STATE_CHECK;
				break;
			case ' ':
			case 0:
				fCheckState = STATE_NORMAL;
				break;
			case '#':
				fCheckState = STATE_CHECK;
				fMate = true;
				break;
			default:
				// Error in the SimpleMove
				return false;
			}
			break;
		case '=':
			// Pawn Promotion
			// TODO:
			fMoveState = STATE_PROMOTION;
			chPP = info[4];
			switch (info[5])
			{
			case '+':
				fCheckState = STATE_CHECK;
				break;
			case ' ':
			case 0:
				fCheckState = STATE_NORMAL;
				break;
			case '#':
				fCheckState = STATE_CHECK;
				fMate = true;
				break;
			default:
				// Error in the SimpleMove
				return false;
			}
			break;
		default:
			// Error in the SimpleMove
			return false;
		}
		break;
	default:
		return false;
	}
	ChessPiece *piece = nullptr;
	int t;
	switch (fMoveState){
	case STATE_MOVE:
		piece = GetPieceAt(hFrom, vFrom);
		piece->Move(hTo, vTo);
		mChessBoard[vTo][hTo] = piece;
		mChessBoard[vFrom][hFrom] = nullptr;
		break;
	case STATE_CAPTURE:
		piece = GetPieceAt(hFrom, vFrom);
		piece->Move(hTo, vTo);
		t = 0;
		while (mCapturedChess[t] != nullptr)
			t++;
		mChessBoard[vTo][hTo]->SetCapruted(true);
		mCapturedChess[t] = mChessBoard[vTo][hTo];
		mChessBoard[vTo][hTo] = piece;
		mChessBoard[vFrom][hFrom] = nullptr;
		break;
	case STATE_CASTLING_KS:
		// Castling (Kingside) "0-0"
		if (fWhite){
			piece = GetPieceAt(4, 7);
			piece->Move(6, 7);
			mChessBoard[7][6] = piece;
			mChessBoard[7][4] = nullptr;
			piece = GetPieceAt(7, 7);
			piece->Move(5, 7);
			mChessBoard[7][5] = piece;
			mChessBoard[7][7] = nullptr;
		}
		else{
			piece = GetPieceAt(4, 0);
			piece->Move(6, 0);
			mChessBoard[0][6] = piece;
			mChessBoard[0][4] = nullptr;
			piece = GetPieceAt(7, 0);
			piece->Move(5, 0);
			mChessBoard[0][5] = piece;
			mChessBoard[0][7] = nullptr;
		}
		break;
	case STATE_CASTLING_QS:
		// Castling (Queenside) "0-0-0"
		if (fWhite){
			piece = GetPieceAt(4, 7);
			piece->Move(2, 7);
			mChessBoard[7][2] = piece;
			mChessBoard[7][4] = nullptr;
			piece = GetPieceAt(0, 7);
			piece->Move(3, 7);
			mChessBoard[7][3] = piece;
			mChessBoard[7][0] = nullptr;
		}
		else{
			piece = GetPieceAt(4, 0);
			piece->Move(2, 0);
			mChessBoard[0][2] = piece;
			mChessBoard[0][4] = nullptr;
			piece = GetPieceAt(0, 0);
			piece->Move(3, 0);
			mChessBoard[0][3] = piece;
			mChessBoard[0][0] = nullptr;
		}
		break;
	case STATE_PROMOTION:
		// TODO: PAWN PROMOTION
		break;
	}
	if (fWhite){
		plBlack->SetChecked(false);
		plBlack->SetNoAvailableMoves(false);
	}
	else{
		plWhite->SetChecked(false);
		plWhite->SetNoAvailableMoves(false);
	}
	switch (fCheckState){
	case STATE_NORMAL:
		break;
	case STATE_CHECK:
		// TODO: Rework
		if (fWhite)
			plBlack->SetChecked(true);
		else
			plWhite->SetChecked(true);
		if (fMate){
			if (fWhite) {
				plBlack->SetNoAvailableMoves(true);
				plBlack->SetChecked(true);
				plWhite->SetActive(!plWhite->IsActive());
				plBlack->SetActive(!plBlack->IsActive());
				Redo();
				return true;
			}
			else {
				plWhite->SetNoAvailableMoves(true);
				plWhite->SetChecked(true);
				plWhite->SetActive(!plWhite->IsActive());
				plBlack->SetActive(!plBlack->IsActive());
				Redo();
				return true;
			}
		}
		break;
	case STATE_CHECKMATE:
		// Mate "0-1" or "1-0"
		// TODO: Rework
		if (!fWhite) {
			plBlack->SetNoAvailableMoves(true);
			plBlack->SetChecked(true);
			plWhite->SetNoAvailableMoves(false);
			plWhite->SetChecked(false);
			Notify();
			return false;
		}
		else {
			plWhite->SetNoAvailableMoves(true);
			plWhite->SetChecked(true);
			plBlack->SetNoAvailableMoves(false);
			plBlack->SetChecked(false);
			Notify();
			return false;
		}
		break;
	case STATE_DRAW:
		// Draw "1/2-1/2"
		plWhite->SetActive(!plWhite->IsActive());
		plBlack->SetActive(!plBlack->IsActive());
		plBlack->SetNoAvailableMoves(true);
		plWhite->SetNoAvailableMoves(true);
		Notify();
		return false;
		break;
	}
	plWhite->SetActive(!plWhite->IsActive());
	plBlack->SetActive(!plBlack->IsActive());
	if (fMate) {
		Redo();
		return false;
	}
	Notify();
	return true;
}

bool ChessBoard::Undo()
{
	if (mrList->getCurrentId() <= 0)
		return false;
	plWhite->SetActive(!plWhite->IsActive());
	plBlack->SetActive(!plBlack->IsActive());
	if (!getCurrentPlayer()->HasAvailableMoves()){
		plWhite->SetActive(!plWhite->IsActive());
		plBlack->SetActive(!plBlack->IsActive());
	}
	bool fMate = false;
	bool fWhite = (getCurrentPlayer()->getId() == PLAYER_WHITE);
	SimpleMove *sm = mrList->getSimpleMove(mrList->getCurrentId());
	char info[MAX_INFO_SIZE];
	int i = 0, infoLenght = 0;
	if (fWhite){
		while ((sm->info[i] != ' ') && (sm->info[i] != 0)){
			info[infoLenght] = sm->info[i];
			i++; infoLenght++;
		}
		info[infoLenght] = 0;
	}
	else{
		while (sm->info[i] != ' ' && (sm->info[i] != 0))
			i++;
		if (sm->info[i] == 0){
			fWhite = true;
			i = 0;
		}
		else
			i++;
		infoLenght = 0;
		while (sm->info[i] != 0){
			info[infoLenght] = sm->info[i];
			i++; infoLenght++;
		}
		info[infoLenght] = 0;
	}
	int hFrom = -1, hTo = -1, vFrom = -1, vTo = -1;
	char chP = 0, chPP = 0;
	int fMoveState = STATE_MOVE;
	int fCheckState = STATE_NORMAL;
	switch (info[0]){
	case '0':
		if (info[1] != '-')
			return false;
		else {
			if (info[2] == '0'){
				if (info[3] == '-'){
					if (info[4] == '0') {
						if (info[5] == ' ' || info[5] == 0){
							// queenside Castling "0-0-0"
							fMoveState = STATE_CASTLING_QS;
						}
						else {
							// Error in the SimpleMove
							return false;
						}
					}
					else {
						// Error in the SimpleMove
						return false;
					}
				}
				else if (info[3] == ' ' || info[3] == 0){
					// kingside Castling "0-0"
					fMoveState = STATE_CASTLING_KS;
				}
				else{
					// Error in the SimpleMove
					return false;
				}
			}
			else if (info[2] == '1'){
				// BLACK WON "0-1"
				fCheckState = STATE_CHECKMATE;
				fMoveState = STATE_CHECKMATE;
			}
			else {
				// Error in the SimpleMove
				return false;
			}
		}
		break;
	case '1':
		if (info[1] == '/'){
			// DRAW "1/2-1/2"
			fCheckState = STATE_DRAW;
			fMoveState = STATE_DRAW;
		}
		else if (info[1] == '-' && info[2] == '0'){
			// WHITE WON "1-0"
			fCheckState = STATE_CHECKMATE;
			fMoveState = STATE_CHECKMATE;
		}
		else {
			// Error in the SimpleMove
			return false;
		}
		break;
	case 'P':
	case 'R':
	case 'N':
	case 'B':
	case 'K':
	case 'Q':
		chP = info[0];
		hFrom = info[1] - 97;
		vFrom = 56 - info[2];
		switch (info[3]){
		case '-':
			// Move
			// TODO:
			fMoveState = STATE_MOVE;
			hTo = info[4] - 97;
			vTo = 56 - info[5];
			switch (info[6])
			{
			case '+':
				fCheckState = STATE_CHECK;
				break;
			case ' ':
				fCheckState = STATE_NORMAL;
				break;
			case '#':
				fCheckState = STATE_CHECK;
				fMate = true;
				break;
			case 0:
				fCheckState = STATE_NORMAL;
				break;
			default:
				// Error in the SimpleMove
				return false;
			}
			break;
		case 'x':
			// Capture
			// TODO:
			fMoveState = STATE_CAPTURE;
			hTo = info[4] - 97;
			vTo = 56 - info[5];
			switch (info[6])
			{
			case '+':
				fCheckState = STATE_CHECK;
				break;
			case ' ':
			case 0:
				fCheckState = STATE_NORMAL;
				break;
			case '#':
				fCheckState = STATE_CHECK;
				fMate = true;
				break;
			default:
				// Error in the SimpleMove
				return false;
			}
			break;
		case '=':
			// Pawn Promotion
			// TODO:
			fMoveState = STATE_PROMOTION;
			chPP = info[4];
			switch (info[5])
			{
			case '+':
				fCheckState = STATE_CHECK;
				break;
			case ' ':
			case 0:
				fCheckState = STATE_NORMAL;
				break;
			case '#':
				fCheckState = STATE_CHECK;
				fMate = true;
				break;
			default:
				// Error in the SimpleMove
				return false;
			}
			break;
		default:
			// Error in the SimpleMove
			return false;
		}
		break;
	default:
		return false;
	}
	ChessPiece *piece = nullptr;
	int t;
	switch (fMoveState){
	case STATE_MOVE:
		piece = GetPieceAt(hTo, vTo);
		piece->Move(hFrom, vFrom);
		piece->setMoveCount(piece->getMoveCount() - 2);
		if (piece->getMoveCount() == 0)
			piece->SetMoved(false);
		mChessBoard[vFrom][hFrom] = piece;
		mChessBoard[vTo][hTo] = nullptr;
		break;
	case STATE_CAPTURE:
		piece = GetPieceAt(hTo, vTo);
		piece->Move(hFrom, vFrom);
		piece->setMoveCount(piece->getMoveCount() - 2);
		if (piece->getMoveCount() == 0)
			piece->SetMoved(false);
		mChessBoard[vFrom][hFrom] = piece;
		mChessBoard[vTo][hTo] = nullptr;
		t = 0;
		while (mCapturedChess[t] != nullptr)
			t++;
		mCapturedChess[t - 1]->SetCapruted(false);
		if (t - 1 >= 0) {
			mChessBoard[vTo][hTo] = mCapturedChess[t - 1];
			mCapturedChess[t - 1] = nullptr;
		}
		break;
	case STATE_CASTLING_KS:
		// Castling (Kingside) "0-0"
		if (fWhite){
			piece = GetPieceAt(6, 7);
			piece->Move(4, 7);
			piece->setMoveCount(piece->getMoveCount() - 2);
			if (piece->getMoveCount() == 0)
				piece->SetMoved(false);
			mChessBoard[7][4] = piece;
			mChessBoard[7][6] = nullptr;
			piece = GetPieceAt(5, 7);
			piece->Move(7, 7);
			piece->setMoveCount(piece->getMoveCount() - 2);
			if (piece->getMoveCount() == 0)
				piece->SetMoved(false);
			mChessBoard[7][7] = piece;
			mChessBoard[7][5] = nullptr;
		}
		else{
			piece = GetPieceAt(6, 0);
			piece->Move(4, 0);
			piece->setMoveCount(piece->getMoveCount() - 2);
			if (piece->getMoveCount() == 0)
				piece->SetMoved(false);
			mChessBoard[0][4] = piece;
			mChessBoard[0][6] = nullptr;
			piece = GetPieceAt(5, 0);
			piece->Move(7, 0);
			piece->setMoveCount(piece->getMoveCount() - 2);
			if (piece->getMoveCount() == 0)
				piece->SetMoved(false);
			mChessBoard[0][7] = piece;
			mChessBoard[0][5] = nullptr;
		}
		break;
	case STATE_CASTLING_QS:
		// Castling (Queenside) "0-0-0"
		if (fWhite){
			piece = GetPieceAt(2, 7);
			piece->Move(4, 7);
			piece->setMoveCount(piece->getMoveCount() - 2);
			if (piece->getMoveCount() == 0)
				piece->SetMoved(false);
			mChessBoard[7][4] = piece;
			mChessBoard[7][2] = nullptr;
			piece = GetPieceAt(3, 7);
			piece->Move(0, 7);
			piece->setMoveCount(piece->getMoveCount() - 2);
			if (piece->getMoveCount() == 0)
				piece->SetMoved(false);
			mChessBoard[7][0] = piece;
			mChessBoard[7][3] = nullptr;
		}
		else{
			piece = GetPieceAt(2, 0);
			piece->Move(4, 0);
			piece->setMoveCount(piece->getMoveCount() - 2);
			if (piece->getMoveCount() == 0)
				piece->SetMoved(false);
			mChessBoard[0][4] = piece;
			mChessBoard[0][2] = nullptr;
			piece = GetPieceAt(3, 0);
			piece->Move(0, 0);
			piece->setMoveCount(piece->getMoveCount() - 2);
			if (piece->getMoveCount() == 0)
				piece->SetMoved(false);
			mChessBoard[0][0] = piece;
			mChessBoard[0][3] = nullptr;
		}
		break;
	case STATE_PROMOTION:
		// TODO: PAWN PROMOTION
		break;
	}
	if (fWhite){
		plBlack->SetChecked(false);
		plBlack->SetNoAvailableMoves(false);
	}
	else{
		plWhite->SetChecked(false);
		plWhite->SetNoAvailableMoves(false);
	}
	switch (fCheckState){
	case STATE_NORMAL:
		break;
	case STATE_CHECK:
		// TODO: Rework
		if (fWhite)
			plBlack->SetChecked(false);
		else
			plWhite->SetChecked(false);
		break;
	case STATE_CHECKMATE:
		// Mate "0-1" or "1-0"
		// TODO: Rework
		if (fWhite) {
			mrList->setCurrentId(mrList->getCurrentId() - 1);
			plWhite->SetNoAvailableMoves(true);
			Undo();
			return true;
		}
		else {
			plBlack->SetNoAvailableMoves(true);
			Undo();
			return true;
		}
		break;
	case STATE_DRAW:
		// Draw "1/2-1/2"
		if (fWhite) {
			mrList->setCurrentId(mrList->getCurrentId() - 1);
			plBlack->SetNoAvailableMoves(false);
			Undo();
			return true;
		}
		else {
			plWhite->SetNoAvailableMoves(false);
			Undo();
			return true;
		}
		break;
	}
	if (fWhite){
		mrList->setCurrentId(mrList->getCurrentId() - 1);
		if (mrList->getCurrentId() == 0){
			Notify();
			return false;
		}
	}
	Notify();
	return true;
}

ChessPiece* ChessBoard::getPieceFromCaptured()
{
	ChessPiece *piece = nullptr;
	int i = 0;
	while (mCapturedChess[i])
		i++;
	if (i > 0)
		piece = mCapturedChess[i - 1];
	return piece;
}

bool ChessBoard::decodeSimpleMove(char *inf)
{
	//int p = 0;
	//int v1 = -1, h1 = -1, v2 = -1, h2 = -1;
	//bool fWhite = true;
	//while (inf[p] != 0){
	//	if (inf[p] == ' '){
	//		fWhite = false;
	//		p++;
	//	}
	//	else{
	//		switch (inf[p]){
	//		case 'P':
	//			h1 = inf[p + 1] - 97;
	//			v1 = 56 - inf[p + 2];
	//			switch (inf[p + 3]){
	//			case '-':
	//				// Move to (v2, h2)
	//				h2 = inf[p + 4] - 97;
	//				v2 = 56 - inf[p + 5];
	//				p += 6;
	//				break;
	//			case 'x':
	//				// Capture (v2, h2)
	//				h2 = inf[p + 4] - 97;
	//				v2 = 56 - inf[p + 5];
	//				p += 6;
	//				break;
	//			default:
	//				return false;
	//			}
	//			if (inf[p] == '+'){
	//				// Check
	//				p++;
	//			}
	//			break;
	//		case 'Q':
	//		case 'K':
	//		case 'N':
	//		case 'R':
	//		case 'B':
	//			h1 = inf[p + 1] - 97;
	//			v1 = 56 - inf[p + 2];
	//			switch (inf[p + 3]){
	//			case '-':
	//				// Move to (v2, h2)
	//				h2 = inf[p + 4] - 97;
	//				v2 = 56 - inf[p + 5];
	//				p += 6;
	//				break;
	//			case 'x':
	//				// Capture (v2, h2)
	//				h2 = inf[p + 4] - 97;
	//				v2 = 56 - inf[p + 5];
	//				p += 6;
	//				break;
	//			default:
	//				return false;
	//			}
	//			if (inf[p] == '+' || inf[p] == '#'){
	//				// Check '+' or Mate '#'
	//				p++;
	//			}
	//			break;
	//		case '1':
	//			if (inf[p + 1] == '-'){
	//				if (inf[p + 2] == '0'){
	//					// WHITE WON
	//					p += 3;
	//					break;
	//				}
	//				else
	//					return false;
	//			}
	//			else if (inf[p + 1] == '/'){
	//				// DRAW "1/2-1/2"
	//				p += 7;
	//				break;
	//			}
	//			else
	//				return false;
	//			break;
	//		case '0':
	//			if (inf[p + 1] != '-')
	//				return false;
	//			switch (inf[p + 2]){
	//			case '0':
	//				if (inf[p + 3] == '-'){
	//					if (inf[p + 4] == '0'){
	//						// queenside Castling "0-0-0"
	//						p += 5;
	//					}
	//					else
	//						return false;
	//				}
	//				else if (inf[p + 3] == ' '){
	//					// kingside Castling "0-0"
	//					p += 3;
	//				}
	//				else
	//					return false;
	//				break;
	//			case '1':
	//				// BLACK WON "0-1"
	//				p += 3;
	//				break;
	//			default:
	//				return false;
	//			}
	//			break;
	//		case '=':
	//			// Pawn promotion
	//		}
	//	}
	//}
	return true;
}
