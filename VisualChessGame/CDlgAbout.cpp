#include "CDlgAbout.h"

BEGIN_MESSAGE_MAP(CDlgAbout, CDialog)
	ON_WM_CREATE()
END_MESSAGE_MAP()

CDlgAbout::CDlgAbout() : CDialog(IDD_DIALOG_ABOUT) {}
CDlgAbout::CDlgAbout(CWnd *pParent = NULL) : CDialog(IDD_DIALOG_ABOUT, pParent) {}

int CDlgAbout::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	HICON icon = AfxGetApp()->LoadIcon(IDI_ICON1);
	SetIcon(icon, TRUE);
	return 0;
}

