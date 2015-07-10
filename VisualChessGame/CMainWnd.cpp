/** CMainWnd.cpp */

#include "CMainWnd.h"
#include <fstream>
#include "Help.h"

BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_GAME_NEW, MenuGameNew)
	ON_COMMAND(ID_GAME_LOAD, MenuGameLoad)
	ON_COMMAND(ID_GAME_SAVE, MenuGameSave)
	ON_COMMAND(ID_GAME_SAVEAS, MenuGameSaveAs)
	ON_COMMAND(ID_GAME_OPTIONS, MenuGameOptions)
	ON_COMMAND(ID_GAME_EXIT, MenuGameExit)
	ON_COMMAND(ID_GAMEPLAY_RECENTLYOPENEDGAMES, MenuGamePlayRecentlyOpenedGames)
	ON_COMMAND(ID_GAMEPLAY_UNDOMOVE, MenuGamePlayUndoMove)
	ON_COMMAND(ID_GAMEPLAY_REDOMOVE, MenuGamePlayRedoMove)
	ON_COMMAND(ID_GAMEPLAY_LISTOFMOVES, MenuGamePlayListOfMoves)
	ON_COMMAND(ID_HELP_ABOUT, MenuHelpAbout)
	ON_COMMAND(ID_HELP_RULES, MenuHelpRules)
END_MESSAGE_MAP()

CMainWnd::CMainWnd()
{
	Create(NULL, "Visual Chess Game", WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, rectDefault, NULL, NULL);
	int white = 0, black = 0;
	int isb = 1, itb = 1;
	m_backgroundColor = ReadIntFromRegHKCU(REGPATH_DEFAULT, REGPAR_BKG, -1);
	white = ReadIntFromRegHKCU(REGPATH_DEFAULT, REGPAR_WHITECLR, 0);
	black = ReadIntFromRegHKCU(REGPATH_DEFAULT, REGPAR_BLACKCLR, 0);
	isb = ReadIntFromRegHKCU(REGPATH_DEFAULT, REGPAR_FSB, 1);
	itb = ReadIntFromRegHKCU(REGPATH_DEFAULT, REGPAR_FTB, 1);
	m_bStatusBar = (isb == 1); m_bToolBar = (itb == 1);
	ShowControlBar(&m_wndToolBar, m_bToolBar, FALSE);
	ShowControlBar(&m_wndStatusBar, m_bStatusBar, FALSE);
	if (m_backgroundColor == -1)
		m_backgroundColor = RGB(255, 255, 255);
	m_whitePlayerPieceColor = (white == 0) ? RGB(255, 255, 255) : (white == 1) ? RGB(0, 0, 255) : RGB(0, 255, 0);
	m_blackPlayerPieceColor = (black == 0) ? RGB(75, 75, 75) : (black == 1) ? RGB(255, 0, 0) : RGB(255, 255, 0);
	m_WhiteBrush = CreateSolidBrush(m_blackPlayerPieceColor);
	m_BlackBrush = CreateSolidBrush(m_whitePlayerPieceColor);
	m_BackgroundBrush = CreateSolidBrush(m_backgroundColor);
	m_ChessBoard = nullptr;
	m_ChessBoardView = nullptr;
	ChessHistoryView *chessHistoryView = nullptr;
	m_bmpPiece.LoadBitmap(IDB_BITMAP_PIECES);
	CDC *dc = GetDC();
	HDC hDC = dc->GetSafeHdc();
	int vPixInchX = GetDeviceCaps(hDC, LOGPIXELSX);
	int vPixInchY = GetDeviceCaps(hDC, LOGPIXELSY);
	ReleaseDC(dc);
	WINDOWPLACEMENT fPos;
	ReadPosWindowFromReg(7 * vPixInchX, 5 * vPixInchY, REGPATH_DLGMAIN, fPos);
	SetWindowPlacement(&fPos);
	InitHelp();
}

int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_dlgListOfMoves.Create(IDD_DIALOG_LISTOFMOVES, this);
	m_wndStatusBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_BOTTOM | WS_CLIPSIBLINGS);
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));
	m_wndStatusBar.SetPaneText(0, "Current Player : NONE");
	m_wndStatusBar.SetPaneStyle(1, SBPS_STRETCH);
	m_wndStatusBar.SetPaneText(1, "State : Pre-Game");
	m_wndStatusBar.SetPaneText(2, "Prev. move : NONE");
	m_wndMenu.LoadMenu(IDR_MAIN_MENU);
	SetMenu(&m_wndMenu);
	m_wndToolBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP | WS_CLIPSIBLINGS);
	m_wndToolBar.LoadToolBar(IDR_TOOLBAR);
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() | CBRS_SIZE_DYNAMIC);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);	
	DockControlBar(&m_wndToolBar);
	HICON icon = AfxGetApp()->LoadIcon(IDI_ICON1);
	SetIcon(icon, TRUE);
	return 0;
}

void CMainWnd::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI)
{
	lpMMI->ptMinTrackSize.x = MIN_WINDOW_WIDTH;
	lpMMI->ptMinTrackSize.y = MIN_WINDOW_HEIGHT;
	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}

void CMainWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_ChessBoard == nullptr)
		return;
	if ((point.x <= m_leftMargin) || (point.x >= m_width - m_leftMargin) ||
		(point.y <= m_topMargin) || (point.y >= m_height))
		return;
	int h = (int(point.x) - m_leftMargin) / m_sideSize;
	if ((h < 0) || (h >= 8))
		return;
	int v = (int(point.y) - m_topMargin) / m_sideSize;
	if ((v < 0) || (v >= 8))
		return;
	RECT rcPiece;
	ChessPiece *piece = m_ChessBoard->GetPieceAt(h, v);
	if (piece){
		if (piece->getPlayerId() == m_ChessBoard->getCurrentPlayer()->getId()){
			m_ChessBoard->setHCurrentSelected(h);
			m_ChessBoard->setVCurrentSelected(v);
			rcPiece.left = m_leftMargin + m_ChessBoard->getHCurrentSelected() * m_sideSize;
			rcPiece.top = m_topMargin + m_ChessBoard->getVCurrentSelected()  * m_sideSize;
			rcPiece.right = m_leftMargin + (m_ChessBoard->getHCurrentSelected() + 1) * m_sideSize;
			rcPiece.bottom = m_topMargin + (m_ChessBoard->getVCurrentSelected() + 1) * m_sideSize;
			RedrawWindow(&rcPiece);
		}
		else
			return;
	}
	else
		return;
	m_ChessBoard->Notify(); 
	RedrawWindow();
}

void CMainWnd::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (m_ChessBoard == nullptr)
		return;
	if ((point.x <= m_leftMargin) || (point.x >= m_width - m_leftMargin) ||
		(point.y <= m_topMargin) || (point.y >= m_height))
		return;
	int h = (int(point.x) - m_leftMargin) / m_sideSize;
	if ((h < 0) || (h >= 8))
		return;
	int v = (int(point.y) - m_topMargin) / m_sideSize;
	if ((v < 0) || (v >= 8))
		return;
	if ((m_ChessBoard->getHCurrentSelected() == -1) || (m_ChessBoard->getVCurrentSelected() == -1))
		return;
	if (m_ChessBoard->makeMove(m_ChessBoard->GetPieceAt(m_ChessBoard->getHCurrentSelected(), m_ChessBoard->getVCurrentSelected()), h, v) == MOVE_SUCCESS)
	{
		RECT rcPiece;
		rcPiece.left = m_leftMargin + m_ChessBoard->getHCurrentSelected() * m_sideSize;
		rcPiece.top = m_topMargin + m_ChessBoard->getVCurrentSelected()  * m_sideSize;
		rcPiece.right = m_leftMargin + (m_ChessBoard->getHCurrentSelected() + 1) * m_sideSize;
		rcPiece.bottom = m_topMargin + (m_ChessBoard->getVCurrentSelected() + 1) * m_sideSize;
		m_ChessBoard->setHCurrentSelected(-1);
		m_ChessBoard->setVCurrentSelected(-1);
		RedrawWindow(&rcPiece);
		rcPiece.left = m_leftMargin + h * m_sideSize;
		rcPiece.top = m_topMargin + v * m_sideSize;
		rcPiece.right = m_leftMargin + (h + 1) * m_sideSize;
		rcPiece.bottom = m_topMargin + (v + 1) * m_sideSize;
		RedrawWindow(&rcPiece);
	} else if (m_ChessBoard->makeMove(m_ChessBoard->GetPieceAt(m_ChessBoard->getHCurrentSelected(), m_ChessBoard->getVCurrentSelected()), h, v) == MOVE_ENDGAME){
		RECT rcPiece;
		rcPiece.left = m_leftMargin + m_ChessBoard->getHCurrentSelected() * m_sideSize;
		rcPiece.top = m_topMargin + m_ChessBoard->getVCurrentSelected()  * m_sideSize;
		rcPiece.right = m_leftMargin + (m_ChessBoard->getHCurrentSelected() + 1) * m_sideSize;
		rcPiece.bottom = m_topMargin + (m_ChessBoard->getVCurrentSelected() + 1) * m_sideSize;
		m_ChessBoard->setHCurrentSelected(-1);
		m_ChessBoard->setVCurrentSelected(-1);
		RedrawWindow(&rcPiece);
		rcPiece.left = m_leftMargin + h * m_sideSize;
		rcPiece.top = m_topMargin + v * m_sideSize;
		rcPiece.right = m_leftMargin + (h + 1) * m_sideSize;
		rcPiece.bottom = m_topMargin + (v + 1) * m_sideSize;
		RedrawWindow(&rcPiece);
	}
	else
		RedrawWindow();
}
void CMainWnd::OnPaint()
{
	PAINTSTRUCT ps;
	RECT rcTB, rcSB, rc, rcClient, rcPiece;
	HGDIOBJ    prevOBJ;
	CDC *cDC = BeginPaint(&ps);
	HDC hDC = cDC->GetSafeHdc();
	m_wndToolBar.GetWindowRect(&rcTB);
	m_wndStatusBar.GetWindowRect(&rcSB);
	GetWindowRect(&rc);
	GetClientRect(&rcClient);
	FillRect(hDC, &rcClient, m_BackgroundBrush);
	m_topMargin = rcTB.bottom - rcTB.top + 1;
	m_bottomMargin = rcSB.bottom - rcSB.top + 1;
	m_height = rcClient.bottom - rcClient.top - m_topMargin - m_bottomMargin;
	m_width = rcClient.right - rcClient.left + 1;
	m_sideSize = ((m_height < m_width)?m_height : m_width)/ 10;
	m_leftMargin = m_width/2 - m_sideSize * 4;
	m_topMargin = m_topMargin + (m_height - 8 * m_sideSize) / 2 - m_bottomMargin/2;
	rcPiece.left = m_leftMargin;
	rcPiece.top = m_topMargin;
	rcPiece.right = m_leftMargin + 8*m_sideSize;
	rcPiece.bottom = m_topMargin + 8*m_sideSize;
	StretchBlt(hDC, rcPiece.left, rcPiece.top, rcPiece.right - rcPiece.left, rcPiece.bottom - rcPiece.top, 
		m_ChessBoard->getOffscreen(), 0, 0, m_ChessBoard->getCXSize(), m_ChessBoard->getCXSize(), SRCCOPY);
	EndPaint(&ps);
}

void CMainWnd::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);
}

void CMainWnd::MenuGameNew()
{
	// TODO: Game -> New
	if (m_ChessHistoryView)
		delete m_ChessHistoryView;
	if (m_ChessBoardView)
		delete m_ChessBoardView;
	if (m_ChessBoard)
		delete m_ChessBoard;
	m_ChessBoard = new VisualChessBoard();
	m_ChessBoardView = new ChessBoardView(m_ChessBoard);
	m_ChessBoard->getMoveList()->setListBox(&m_dlgListOfMoves);
	m_ChessHistoryView = new ChessHistoryView(m_ChessBoard->getMoveList());
	m_ChessBoard->SetValues(m_whitePlayerPieceColor, m_blackPlayerPieceColor, GetDC(), &m_bmpPiece);
	m_ChessBoard->setStatusBar(&m_wndStatusBar);
	m_ChessBoard->Init();
	RedrawWindow();
}

void CMainWnd::MenuGameLoad()
{
	// TODO: Game -> Load
	CFileDialog fileDialog(TRUE, NULL, "*.txt", NULL, "Text (*.txt)|*.txt|");
	char buffer[256];
	GetCurrentDirectory(256, buffer);
	fileDialog.m_ofn.lpstrInitialDir = buffer;
	if (fileDialog.DoModal() == IDOK)
	{
		if (m_ChessBoard){
			if (MessageBox("Do you want to break the current game without save?", "Load Existing Game", MB_YESNO) == IDNO){
				// TODO: Save As the Current Game
			}
		}
		if (m_ChessHistoryView)
			delete m_ChessHistoryView;
		if (m_ChessBoardView)
			delete m_ChessBoardView;
		if (m_ChessBoard)
			delete m_ChessBoard;
		m_ChessBoard = new VisualChessBoard();
		m_ChessBoardView = new ChessBoardView(m_ChessBoard);
		m_ChessBoard->getMoveList()->setListBox(&m_dlgListOfMoves);
		m_ChessHistoryView = new ChessHistoryView(m_ChessBoard->getMoveList());
		m_ChessBoard->SetValues(m_whitePlayerPieceColor, m_blackPlayerPieceColor, GetDC(), &m_bmpPiece);
		m_ChessBoard->setStatusBar(&m_wndStatusBar);
		m_ChessBoard->Init();
		char info[MAX_INFO_SIZE];
		bool fWhite = true;
		std::ifstream inFile(fileDialog.GetPathName());
		while (!inFile.eof()){
			inFile >> info;
			m_ChessBoard->getMoveList()->AddSimpleMove(info, !fWhite);
			fWhite = !fWhite;
		}
		inFile.close();
		m_ChessBoard->getMoveList()->setCurrentId(0);
		while (m_ChessBoard->Redo()) {}
		RedrawWindow();
	}
}

void CMainWnd::MenuGameSave()
{
	// TODO: Game -> Save
	int buffer_size = 512;
	if (!m_ChessBoard){
		MessageBox("No any ongoing game.", "Save Ongoing Game", MB_OK);
		return;
	}
	HANDLE hFile = CreateFileA("MMFVChessG.txt", GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	SimpleMove *sm = m_ChessBoard->getMoveList()->getFirst();
	while (sm != nullptr){
		DWORD dwBytesToWrite = (DWORD)strlen(sm->info);
		DWORD dwBytesWritten = 0;
		BOOL bErrorFlag = FALSE;
		bErrorFlag = WriteFile(hFile, sm->info, dwBytesToWrite, &dwBytesWritten, NULL);
		sm = sm->next;
		if (sm != nullptr){
			char NewLine[] = "\r\n";
			DWORD NumWritten;
			BOOL Result = WriteFile(hFile, &NewLine, 2, &NumWritten, NULL);
		}
	}

	HANDLE hFileMap = CreateFileMappingA(hFile, NULL, PAGE_READWRITE, 0, buffer_size, "mmf_vchessg");
	if (hFileMap == NULL){
		MessageBox("Can't open memory mapped file.", "Save Ongoing Game", MB_OK);
		return;
	}

	PBYTE pbMapView = (PBYTE)MapViewOfFile(hFileMap, FILE_MAP_ALL_ACCESS, 0, 0, buffer_size);
	if (pbMapView == NULL){
		MessageBox("Can't map view of file.", "Save Ongoing Game", MB_OK);
		return;
	}

	UnmapViewOfFile(pbMapView);
	CloseHandle(hFileMap);
	CloseHandle(hFile);
}

void CMainWnd::MenuGameSaveAs()
{
	// TODO: Game -> SaveAs
	if (!m_ChessBoard){
		MessageBox("No any ongoing game.", "Save Ongoing Game", MB_OK);
		return;
	}
	CFileDialog fileDialog(FALSE, ".txt", "*.txt");
	if (fileDialog.DoModal() == IDOK)
	{
		char fullFileName[256];
		strcpy(fullFileName, fileDialog.GetPathName());
		std::ofstream outFile(fullFileName);
		SimpleMove *sm = m_ChessBoard->getMoveList()->getFirst();
		while (sm != nullptr){
			if (sm->next == nullptr)
				outFile << sm->info;
			else
				outFile << sm->info << std::endl;
			sm = sm->next;
		}
		outFile.close();
	}
}

void CMainWnd::MenuGameOptions()
{
	// TODO: Game -> Options
	m_dlgOptions.InitValues(m_backgroundColor, m_whitePlayerPieceColor, m_blackPlayerPieceColor, m_bToolBar, m_bStatusBar);
	if (m_dlgOptions.DoModal() == IDOK){
		m_bToolBar = m_dlgOptions.GetIsVisibleToolBar();
		ShowControlBar(&m_wndToolBar, m_bToolBar, FALSE);
		m_bStatusBar = m_dlgOptions.GetIsVisibleStatusBar();
		ShowControlBar(&m_wndStatusBar, m_bStatusBar, FALSE);
		m_whitePlayerPieceColor = m_dlgOptions.GetWhitePlayerPieceColor();
		m_blackPlayerPieceColor = m_dlgOptions.GetBlackPlayerPieceColor();
		m_backgroundColor = m_dlgOptions.GetBackgroundColor();
		m_BlackBrush = CreateSolidBrush(m_whitePlayerPieceColor);
		m_WhiteBrush = CreateSolidBrush(m_blackPlayerPieceColor);
		m_BackgroundBrush = CreateSolidBrush(m_backgroundColor);
		if (m_ChessBoard){
			m_ChessBoard->SetBrushes(m_whitePlayerPieceColor, m_blackPlayerPieceColor);
			m_ChessBoard->Notify();
		}
		RedrawWindow();
	}
}

void CMainWnd::MenuGameExit()
{
	DestroyWindow();
}

void CMainWnd::MenuGamePlayRecentlyOpenedGames()
{
	// TODO: GamePlay -> Recently Opened Games
}

void CMainWnd::MenuGamePlayUndoMove()
{
	if (m_ChessBoard){
		if (m_ChessBoard->Undo()){
			m_ChessBoard->setHCurrentSelected(-1);
			m_ChessBoard->setVCurrentSelected(-1);
			RedrawWindow();
		}
		RedrawWindow();
	}
}

void CMainWnd::MenuGamePlayRedoMove()
{
	if (m_ChessBoard){
		if (m_ChessBoard->Redo()){
			m_ChessBoard->setHCurrentSelected(-1);
			m_ChessBoard->setVCurrentSelected(-1);
			RedrawWindow();
		}
	}
}

void CMainWnd::MenuGamePlayListOfMoves()
{
	// TODO: GamePlay -> List Of Moves
	RECT rc;
	GetWindowRect(&rc);
	if (m_dlgListOfMoves.IsWindowVisible())
		m_dlgListOfMoves.ShowWindow(SW_HIDE);
	else {
		m_dlgListOfMoves.SetWindowPos(NULL, rc.right - 240, rc.top, 240, rc.bottom - rc.top + 1, SWP_SHOWWINDOW);
	}
}

void CMainWnd::MenuHelpAbout()
{
	m_dlgAbout.DoModal();
}

void CMainWnd::MenuHelpRules()
{
	// TODO: Help -> Rules
	CallHelp(NULL, "rules.htm");
}

void CMainWnd::OnClose(){
	WINDOWPLACEMENT fPos;
	GetWindowPlacement(&fPos);
	WritePosWindowToReg(REGPATH_DLGMAIN, fPos);
	int white = (m_whitePlayerPieceColor == RGB(255, 255, 255)) ? 0 :
				(m_whitePlayerPieceColor == RGB(0, 0, 255)) ? 1 : 2;
	int black = (m_blackPlayerPieceColor == RGB(75, 75, 75)) ? 0 :
				(m_blackPlayerPieceColor == RGB(255, 0, 0)) ? 1 : 2;
	WriteSettingsToReg(REGPATH_DEFAULT, m_backgroundColor, white, black, m_bStatusBar, m_bToolBar);
	DestroyWindow();
}

CMainWnd::~CMainWnd(){
	if (m_ChessHistoryView)
		delete m_ChessHistoryView;
	if (m_ChessBoardView)
		delete m_ChessBoardView;
	if (m_ChessBoard)
		delete m_ChessBoard;
}

