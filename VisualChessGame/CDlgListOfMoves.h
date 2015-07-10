/*! @file CDlgListOfMoves.h */
#pragma once

#include "afxwin.h"
#include "afxext.h"
#include "resource.h"	

class CDlgListOfMoves : public CDialog
{
public:
	CDlgListOfMoves();
	CDlgListOfMoves(CWnd*);
	void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
private:
	DECLARE_MESSAGE_MAP();
};