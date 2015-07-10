/** CVisualChessGame.cpp */

#include "CVisualChessGame.h"

CVisualChessGame::CVisualChessGame()
{}

CVisualChessGame::~CVisualChessGame()
{
	CloseHandle(m_hMutex);
}

BOOL CVisualChessGame::InitInstance()
{
	m_hMutex = OpenMutex(MUTEX_ALL_ACCESS, 0, "VISUALCHESSGAMEEXE");
	if (!m_hMutex)
		m_hMutex = CreateMutex(0, 0, "VISUALCHESSGAMEEXE");
	else {
		AfxMessageBox(_T("VisualChessGame.exe : The application is already run!"));
		return 0;
	}
	m_pMainWnd = new CMainWnd();
	ASSERT(m_pMainWnd);
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
};

CVisualChessGame theApp;
