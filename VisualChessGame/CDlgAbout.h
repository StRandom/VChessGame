/*! @file CDlgOptions.h */
#pragma once

#include "afxwin.h"
#include "afxext.h"
#include "resource.h"	

class CDlgAbout : public CDialog
{
public:
	CDlgAbout();
	CDlgAbout(CWnd*);
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
private:
	DECLARE_MESSAGE_MAP();
};