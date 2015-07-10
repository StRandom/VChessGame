/*! @file CDlgOptions.h */
#pragma once

#include "afxwin.h"
#include "afxext.h"
#include "resource.h"	

class CDlgOptions : public CDialog	
{
public:
	CDlgOptions();
	CDlgOptions(CWnd*);
	virtual void DoDataExchange(CDataExchange* pDX);
	void OnOK(UINT uID);
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	BOOL OnInitDialog();
	void InitValues(COLORREF bColor, COLORREF wppColor, COLORREF bppColor, bool vTB, bool vSB);
	COLORREF GetBackgroundColor() { return m_backgroundColor; }
	COLORREF GetWhitePlayerPieceColor() { return (m_whitePlayerPieceColor == 0) ? RGB(255, 255, 255) : 
		                                         (m_whitePlayerPieceColor == 1) ? RGB(0,0,255): RGB(0,255,0) ; }
	COLORREF GetBlackPlayerPieceColor() { return (m_blackPlayerPieceColor == 0) ? RGB(75, 75, 75) :
										         (m_blackPlayerPieceColor == 1) ? RGB(255, 0, 0) : RGB(255, 255, 0);
	}
	bool GetIsVisibleToolBar() { return (m_stateToolBar == BST_CHECKED); }
	bool GetIsVisibleStatusBar() { return (m_stateStatusBar == BST_CHECKED); }
	void OnChangeColor();
protected:
private:
	DECLARE_MESSAGE_MAP();
private:
	COLORREF m_backgroundColor;
	int m_whitePlayerPieceColor;
	int m_blackPlayerPieceColor;
	bool m_bToolBar;
	bool m_bStatusBar;
	int m_stateToolBar;
	int m_stateStatusBar;
};