/*! @file CMainWnd.h */
#pragma once

#include "afxwin.h" 
#include "afxext.h" 
#include "CDlgOptions.h"
#include "CDlgAbout.h"
#include "CDlgListOfMoves.h"
#include "vld.h"
#include "resource.h"

#include "Engine\ChessBoardView.h"
#include "Engine\ChessHistoryView.h"
#include "VisualChessBoard.h"
#include "Registry.h"

static UINT indicators[] =
{
	IDS_STRING3,
	IDS_STRING2,
	IDS_STRING1
};

class CMainWnd : public CFrameWnd
{
public:
	CMainWnd();
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	void MenuGameNew();
	void MenuGameLoad();
	void MenuGameSave();
	void MenuGameSaveAs();
	void MenuGameOptions();
	void MenuGameExit();
	void MenuGamePlayRecentlyOpenedGames();
	void MenuGamePlayUndoMove();
	void MenuGamePlayRedoMove();
	void MenuGamePlayListOfMoves();
	void MenuHelpAbout();
	void MenuHelpRules();

	bool GetIsVisibleToolBar() { return m_bToolBar; }
	~CMainWnd();
private:
	CStatusBar m_wndStatusBar;
	CMenu m_wndMenu;
	CToolBar   m_wndToolBar;
	CDlgOptions m_dlgOptions;
	CDlgAbout m_dlgAbout;
	CDlgListOfMoves m_dlgListOfMoves;
	static const int INDICATORS_SIZE = 100;
	static const int MIN_WINDOW_WIDTH = 700;
	static const int MIN_WINDOW_HEIGHT = 700;
	DECLARE_MESSAGE_MAP();
private:
	COLORREF m_backgroundColor;
	COLORREF m_whitePlayerPieceColor;
	COLORREF m_blackPlayerPieceColor;
	bool m_bToolBar;
	bool m_bStatusBar;
	VisualChessBoard *m_ChessBoard;
	CBitmap m_bmpPiece;
	ChessBoardView *m_ChessBoardView;
	ChessHistoryView *m_ChessHistoryView;
	HBRUSH m_WhiteBrush;
	HBRUSH m_BlackBrush;
	HBRUSH m_BackgroundBrush;
	int m_topMargin;
	int m_bottomMargin;
	int m_leftMargin;
	int m_rightMargin;
	int m_height;
	int m_width;
	int m_sideSize;
};