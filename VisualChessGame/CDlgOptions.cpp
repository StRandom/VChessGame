#include "CDlgOptions.h"

BEGIN_MESSAGE_MAP(CDlgOptions, CDialog)
	ON_WM_CREATE()
	ON_CONTROL_RANGE(BN_CLICKED, IDOK, IDOK, OnOK)
	ON_COMMAND(IDC_BUTTON_BCOLOR, OnChangeColor)
END_MESSAGE_MAP()

CDlgOptions::CDlgOptions() : CDialog(IDD_DIALOG_OPTIONS) 
{
}
CDlgOptions::CDlgOptions(CWnd *pParent = NULL): CDialog(IDD_DIALOG_OPTIONS, pParent) {}

int CDlgOptions::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	HICON icon = AfxGetApp()->LoadIcon(IDI_ICON1);
	SetIcon(icon, TRUE);
	return 0;
}

void CDlgOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);	
	DDX_Check(pDX, IDC_CHECK_TOOLBAR, m_stateToolBar);
	DDX_Check(pDX, IDC_CHECK_STATUSBAR, m_stateStatusBar);
	DDX_Radio(pDX, IDC_RADIO_WPPC1, m_whitePlayerPieceColor);
	DDX_Radio(pDX, IDC_RADIO_BPPC1, m_blackPlayerPieceColor);
}

void CDlgOptions::OnOK(UINT uID)
{
	UpdateData(true);
	CDialog::OnOK();
}

void CDlgOptions::InitValues(COLORREF bColor, COLORREF wppColor, COLORREF bppColor, bool vTB, bool vSB)
{
	m_backgroundColor = bColor;
	m_whitePlayerPieceColor = (wppColor == RGB(255, 255, 255)) ? 0 : (wppColor == RGB(0, 0, 255))?1:2;
	m_blackPlayerPieceColor = (bppColor == RGB(75, 75, 75)) ? 0 : (bppColor == RGB(255, 0, 0)) ? 1 : 2;
	m_bToolBar = vTB;
	m_bStatusBar = vSB;
	m_stateToolBar = (vTB)?BST_CHECKED:BST_UNCHECKED;
	m_stateStatusBar = (vSB) ? BST_CHECKED : BST_UNCHECKED;
}

BOOL CDlgOptions::OnInitDialog()
{
	CDialog::OnInitDialog();
	UpdateData(false);
	return true;
}
void CDlgOptions::OnChangeColor()
{
	CColorDialog cc(m_backgroundColor, NULL, NULL);
	if (cc.DoModal() == IDOK)
	{
		m_backgroundColor = cc.GetColor();
	}
}