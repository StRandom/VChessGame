#pragma once

#include "Engine\ChessBoard.h"
#include <afxwin.h>
#include <Windows.h>

#define LOGICAL_BOARD_SIZE_X	1601
#define LOGICAL_BOARD_SIZE_Y	1601
#define LOGICAL_PIECE_SIZE_X	200
#define LOGICAL_PIECE_SIZE_Y	200

class VisualChessBoard : public ChessBoard{
public:
	VisualChessBoard();
	virtual ~VisualChessBoard();

	virtual void Init();
	void setDCSettings(HDC &hdcTemp, int cx0, int cy0, int cx, int cy);
	void SetValues(COLORREF white, COLORREF black, CDC *dc, CBitmap *bmp);
	void SetBrushes(COLORREF white, COLORREF black);
	HDC getDC() { return m_dc; }
	HBITMAP getBmpOffscreen() { return m_bmpOffscreen; }
	HBITMAP getBmpPieces() { return m_bmpPieces; }
	HDC getOffscreen() { return m_dcOffscreen; }
	int getCXSize() { return m_cxSize; }
	int getCYSize() { return m_cySize; }
	int getXOffSetForPieces(char* pieceName);
	HBRUSH getWhiteBrush() { return m_WhiteBrush; }
	HBRUSH getBlackBrush() { return m_BlackBrush; }
	int getHCurrentSelected() { return m_hCurrentSelected; }
	void setHCurrentSelected(int h) { m_hCurrentSelected = h; }
	int getVCurrentSelected() { return m_vCurrentSelected; }
	void setVCurrentSelected(int v) { m_vCurrentSelected = v; }
	CStatusBar *getStatusBar() { return m_StatusBar; }
	void setStatusBar(CStatusBar *csb) { m_StatusBar = csb; }
protected:
	COLORREF m_whitePlayerPieceColor;
	COLORREF m_blackPlayerPieceColor;
	HBRUSH m_WhiteBrush;
	HBRUSH m_BlackBrush;
	HDC m_dc;
	HDC m_dcOffscreen;
	HBITMAP m_bmpOffscreen;
	HBITMAP m_bmpPieces;
	int m_cxSize;
	int m_cySize;
	int m_hCurrentSelected;
	int m_vCurrentSelected;
	CStatusBar *m_StatusBar;
};