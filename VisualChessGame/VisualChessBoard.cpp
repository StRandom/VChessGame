#include "VisualChessBoard.h"
#include "resource.h"

VisualChessBoard::VisualChessBoard()
{
	m_cxSize = LOGICAL_BOARD_SIZE_X;
	m_cySize = LOGICAL_BOARD_SIZE_Y;
	m_hCurrentSelected = -1;
	m_vCurrentSelected = -1;
	m_StatusBar = nullptr;
}

VisualChessBoard::~VisualChessBoard()
{
	if (m_WhiteBrush)
		DeleteObject(m_WhiteBrush);
	if (m_BlackBrush)
		DeleteObject(m_BlackBrush);

}

void VisualChessBoard::Init()
{
	ChessBoard::Init();
}

void VisualChessBoard::setDCSettings(HDC &hdcTemp, int cx0, int cy0, int cx, int cy){
	SetMapMode(hdcTemp, MM_ISOTROPIC);
	SetWindowExtEx(hdcTemp, m_cxSize, m_cySize, NULL);
	SetViewportExtEx(hdcTemp, cx - cx0, cy - cy0, NULL);
	SetViewportOrgEx(hdcTemp, 0, 0, NULL);
}
void VisualChessBoard::SetValues(COLORREF white, COLORREF black, CDC *dc, CBitmap *bmp)
{
	m_whitePlayerPieceColor = white;
	m_blackPlayerPieceColor = black;
	m_WhiteBrush = CreateSolidBrush(m_whitePlayerPieceColor);
	m_BlackBrush = CreateSolidBrush(m_blackPlayerPieceColor);
	m_dc = dc->GetSafeHdc();
	m_bmpPieces = (HBITMAP)bmp->GetSafeHandle();
	m_dcOffscreen = CreateCompatibleDC(m_dc);
	m_bmpOffscreen = CreateCompatibleBitmap(m_dc, m_cxSize, m_cySize);
	HBITMAP hBmpOld = (HBITMAP)SelectObject(m_dcOffscreen, m_bmpOffscreen);
	setDCSettings(m_dc, 0, 0, m_cxSize, m_cySize);
	PatBlt(m_dcOffscreen, 0, 0, m_cxSize, m_cySize, WHITENESS);
}

void VisualChessBoard::SetBrushes(COLORREF white, COLORREF black)
{
	m_whitePlayerPieceColor = white;
	m_blackPlayerPieceColor = black;
	m_WhiteBrush = CreateSolidBrush(m_whitePlayerPieceColor);
	m_BlackBrush = CreateSolidBrush(m_blackPlayerPieceColor);
}

int VisualChessBoard::getXOffSetForPieces(char* pieceName)
{
	if (strcmp(pieceName, "ROOK") == 0){
		return LOGICAL_PIECE_SIZE_X * 0;
	}
	else if (strcmp(pieceName, "KNIGHT") == 0){
		return LOGICAL_PIECE_SIZE_X * 1;
	}
	else if (strcmp(pieceName, "BISHOP") == 0){
		return LOGICAL_PIECE_SIZE_X * 2;
	}
	else if (strcmp(pieceName, "QUEEN") == 0){
		return LOGICAL_PIECE_SIZE_X * 3;
	}
	else if (strcmp(pieceName, "KING") == 0){
		return LOGICAL_PIECE_SIZE_X * 4;
	}
	else if (strcmp(pieceName, "PAWN") == 0){
		return LOGICAL_PIECE_SIZE_X * 5;
	}
	else
		return LOGICAL_BOARD_SIZE_X;
}