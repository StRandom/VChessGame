#include "ChessBoardView.h"

void ChessBoardView::Draw(){
	for (int i = 0; i < mSubject->GetBoardSize(); i++){
		for (int j = 0; j < mSubject->GetBoardSize(); j++){
			HDC hDC = mSubject->getOffscreen();
			HBRUSH hBrush = ((i + j) % 2 == 0) ? mSubject->getWhiteBrush() : mSubject->getBlackBrush();
			if (!mSubject->GetPieceAt(j, i)){
				HBRUSH hBrushOld = (HBRUSH)SelectObject(hDC, hBrush);
				Rectangle(hDC, 0 + j*LOGICAL_PIECE_SIZE_Y, 0 + i * LOGICAL_PIECE_SIZE_X, - 1 + (j + 1) * LOGICAL_PIECE_SIZE_Y, - 1 + (i + 1) * LOGICAL_PIECE_SIZE_X);
				SelectObject(hDC, hBrushOld);
			}
			else if (!mSubject->GetPieceAt(j, i)->HasCaptured()){
				bool fWhite = (mSubject->GetPieceAt(j, i)->getPlayerId() == PLAYER_WHITE)?true:false;
				int iOff = mSubject->getXOffSetForPieces(mSubject->GetPieceAt(j, i)->GetName());
				RECT rect;
				rect.left = j * LOGICAL_PIECE_SIZE_Y;
				rect.top = i * LOGICAL_PIECE_SIZE_X;
				rect.right = (j + 1) * LOGICAL_PIECE_SIZE_Y;
				rect.bottom = (i + 1) * LOGICAL_PIECE_SIZE_X;
				HBRUSH hBrush = ((i + j) % 2 == 0) ? mSubject->getWhiteBrush() : mSubject->getBlackBrush();
				HBRUSH hBrushPiece = fWhite ? mSubject->getWhiteBrush() : mSubject->getBlackBrush();
				HBRUSH hBrushOld = (HBRUSH)SelectObject(hDC, hBrush);
				bool fSel = (mSubject->getHCurrentSelected() == j) && (mSubject->getVCurrentSelected() == i);
				HBRUSH hBrushBorder =fSel?CreateSolidBrush(RGB(0, 255, 0)): CreateSolidBrush(RGB(0, 0, 0));
				HDC hBitmapDC = CreateCompatibleDC(hDC);
				CBitmap *Bitmap;
				HBITMAP hOldBitmap = (HBITMAP)SelectObject(hBitmapDC, mSubject->getBmpPieces());
				HBRUSH hBrushBDCOld = (HBRUSH)SelectObject(hBitmapDC, hBrush);
				FloodFill(hBitmapDC, iOff, 0, RGB(0,0,0));
				SelectObject(hBitmapDC, hBrushBDCOld);
				hBrushBDCOld = (HBRUSH)SelectObject(hBitmapDC, hBrushPiece);
				FloodFill(hBitmapDC, iOff+110, 130, RGB(0, 0, 0));
				SelectObject(hBitmapDC, hBrushBDCOld);
				StretchBlt(hDC, j*LOGICAL_PIECE_SIZE_Y + 2, i * LOGICAL_PIECE_SIZE_X + 2, LOGICAL_PIECE_SIZE_Y - 4, LOGICAL_PIECE_SIZE_X - 4,
					hBitmapDC, iOff, 0, LOGICAL_PIECE_SIZE_X, LOGICAL_PIECE_SIZE_Y, SRCCOPY);
				SelectObject(hDC, hBrushOld);
				hBrushOld = (HBRUSH)SelectObject(hDC, hBrush);
				FrameRect(hDC, &rect, hBrushBorder);
				int r = (fSel) ? 8 : 2;
				for (int t = 0; t < r; t++){
					FrameRect(hDC, &rect, hBrushBorder);
					rect.left++;
					rect.bottom--;
					rect.right--;
					rect.top++;
				}
				SelectObject(hDC, hBrushOld);
				SelectObject(hBitmapDC, hOldBitmap);
				DeleteDC(hBitmapDC);
			}
		}
	}
	char value1[50];
	char value2[50];
	char value3[50];
	strcpy(value1, "Current Player : ");
	strcat(value1, ((mSubject->getCurrentPlayer()->getId() == PLAYER_WHITE)?STR_PLAYER_WHITE:STR_PLAYER_BLACK));
	mSubject->getStatusBar()->SetPaneText(0, value1);
	mSubject->getStatusBar()->SetPaneStyle(1, SBPS_STRETCH);
	strcpy(value2, "State: ");
	if (mSubject->getCurrentPlayer()->IsChecked()){
		if (!mSubject->getCurrentPlayer()->HasAvailableMoves())
			strcat(value2, STR_STATE_MATE);
		else
			strcat(value2, STR_STATE_CHECK);
	}
	else if (!mSubject->getCurrentPlayer()->HasAvailableMoves())
		strcat(value2, STR_STATE_DRAW);
	else
		strcat(value2, STR_STATE_ONGOING);
	mSubject->getStatusBar()->SetPaneText(1, value2);
	strcpy(value3, "Prev. move: ");
	if (mSubject->getMoveList()->getLast()){
		char subValue3[MAX_INFO_SIZE];
		int i = 0;
		while (mSubject->getMoveList()->getLast()->info[i] != 0 && mSubject->getMoveList()->getLast()->info[i] != ' '){
			subValue3[i] = mSubject->getMoveList()->getLast()->info[i];
			i++;
		}
		subValue3[i] = 0;
		if (mSubject->getCurrentPlayer()->getId() == PLAYER_WHITE){
			int t = 0;
			i++;
			while (mSubject->getMoveList()->getLast()->info[i] != 0 && mSubject->getMoveList()->getLast()->info[i] != ' '){
				subValue3[t] = mSubject->getMoveList()->getLast()->info[i];
				i++; t++;
			}
			subValue3[t] = 0;
		}
		strcat(value3, subValue3);
	}
	else
		strcat(value3, "NONE");
	mSubject->getStatusBar()->SetPaneText(2, value3);
}