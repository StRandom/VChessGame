#include "CDlgListOfMoves.h"

BEGIN_MESSAGE_MAP(CDlgListOfMoves, CDialog)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()

CDlgListOfMoves::CDlgListOfMoves() : CDialog(IDD_DIALOG_LISTOFMOVES) {}
CDlgListOfMoves::CDlgListOfMoves(CWnd *pParent = NULL) : CDialog(IDD_DIALOG_LISTOFMOVES, pParent) {}

void CDlgListOfMoves::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI)
{
	lpMMI->ptMinTrackSize.x = 240;
	lpMMI->ptMinTrackSize.y = 200;
	lpMMI->ptMaxTrackSize.x = 240;
	lpMMI->ptMaxSize.x = 240;
	CDialog::OnGetMinMaxInfo(lpMMI);
}

void CDlgListOfMoves::OnSize(UINT nType, int cx, int cy)
{
	CListBox *list = (CListBox*)GetDlgItem(IDC_LIST_OFMOVES);
	list->SetWindowPos(NULL, 0, 0, cx, cy, SWP_SHOWWINDOW);
	CDialog::OnSize(nType, cx, cy);
}

int CDlgListOfMoves::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	HICON icon = AfxGetApp()->LoadIcon(IDI_ICON1);
	SetIcon(icon, TRUE);
	return 0;
}



