#include <vld.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "ChessBoardView.h"
#include "ChessHistoryView.h"

using namespace std;

int main()
{
	ChessBoard *chess = new ChessBoard();
	ChessBoardView *chessView = new ChessBoardView(chess);
	ChessHistoryView *chessHistoryView = new ChessHistoryView(chess->getMoveList());
	chess->Init();
	int chV, chH, fV, fH;
	int k = 0;
	int f = 0;
	char info[MAX_INFO_SIZE];
	bool fWhite = true;
	ifstream inFile("Test_SimpleQSandKSCastling.txt");
	while (!inFile.eof()){
		inFile >> info;
		chess->getMoveList()->AddSimpleMove(info, !fWhite);
		fWhite = !fWhite;
		k++;
	}
	chess->getMoveList()->setCurrentId(0);
	cout << "Redo() has started" << endl;
	while (chess->Redo()) {}
	cout << "Redo() has finished" << endl;
	int t = -1;
	while (t != 0){
		cout << "Pick the action: (0 - Exit, 1 - Redo, 2 - Undo, 3 - Move)" << endl;
		cin >> t;
		if (t == 1){
			if (chess->Redo()){
			}
			else{
				cout << "REDO impossible!" << endl;
			}
		}
		else if (t == 2){
			if (chess->Undo()){
			}
			else{
				cout << "UNDO impossible!" << endl;
			}
		}
		else if (t == 3){
			cout << "Make Move: (fromV, fromH, toV, to H)" << endl;
			cin >> chV >> chH >> fV >> fH;
			f = chess->makeMove(chess->GetPieceAt(chH, chV), fH, fV);
			/*if (f == MOVE_ENDGAME)
				t = 0;*/
		}
		cout << ((chess->getCurrentPlayer()->getId() == 1) ? "WHITE" : "BLACK") << endl;
	}
	//cout << "Undo() has started" << endl;
	//while (chess->Undo()) {}
	//cout << "Undo() has finished" << endl;
	//cout << "Redo() has started" << endl;
	//while (chess->Redo()) {}
	//cout << "Redo() has finished" << endl;
	//chess->Undo();
	//chess->Notify();
	//while (f != MOVE_ENDGAME){
	//	cin >> chV >> chH >> fV >> fH;
	//	f = chess->makeMove(chess->GetPieceAt(chH, chV), fH, fV);
	//	/*if (f == MOVE_ENDGAME && k == 6) {
	//	chess->Undo();
	//	f = 0;
	//	}*/
	//	k++;
	//}
	system("pause");
	delete chessHistoryView;
	delete chessView;
	delete chess;
	return 0;
}

/**
 * Scholar's mate:
 * 6 4 4 4       Pe2-e4
 * 1 4 3 4       Pe7-e5
 * 7 3 3 7       Qd1-h5
 * 0 1 2 0       Nb8-a6
 * 7 5 4 2       Bf1-c4
 * 0 6 2 5       Ng8-f6
 * 3 7 1 5       Qh5xf7
 */