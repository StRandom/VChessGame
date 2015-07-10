#pragma once

#include <windows.h>

#define REGPATH				"Software\\StRandomCorp\\VisualChessGame"
#define REGPATH_DLGMAIN		"Software\\StRandomCorp\\VisualChessGame\\DlgMain"
#define REGPATH_DEFAULT		"Software\\StRandomCorp\\VisualChessGame\\Default"
#define REGPATH_STARTUP		"Software\\Microsoft\\Windows\\CurrentVersion\\Run"

#define REGPAR_POSMAXX		"max.x"
#define REGPAR_POSMAXY		"max.y"
#define REGPAR_POSMINX		"min.x"
#define REGPAR_POSMINY		"min.y"
#define REGPAR_POSL			"left"
#define REGPAR_POST			"top"
#define REGPAR_POSR			"right"
#define REGPAR_POSB			"bottom"

#define REGPAR_BKG			"BkgColor"
#define REGPAR_WHITECLR		"WhiteColor"
#define REGPAR_BLACKCLR		"BlackColor"
#define REGPAR_FSB			"ShowStatusBar"
#define REGPAR_FTB			"ShowToolBar"

void ExtractFilePath(LPCSTR pszFileName, LPSTR pszFilePath);

void WriteStrToReg(HKEY hKeyGlob, LPCTSTR lpSubKey, LPCTSTR lpValueName, LPCSTR lpStr);
void ReadFromReg(HKEY hKeyGlob, LPCTSTR lpSubKey, LPCTSTR lpValueName,
	LPSTR lpStr, DWORD nSzStr);

void WriteStrToRegHKCU(LPCTSTR lpSubKey, LPCTSTR lpValueName, LPCSTR lpStr);
void ReadStrFromRegHKCU(LPCTSTR lpSubKey, LPCTSTR lpValueName, LPSTR lpStr, DWORD nSzStr);

void WriteIntToRegHKCU(LPCTSTR lpSubKey, LPCTSTR lpValueName, UINT AVal);
int ReadIntFromRegHKCU(LPCTSTR lpSubKey, LPCTSTR lpValueName, int ADefVal);

BOOL ReadMemFromRegHKCU(LPCTSTR lpSubKey, LPCTSTR lpValueName, LPVOID lpBuf, DWORD nSzBuf);
BOOL WriteMemToRegHKCU(LPCTSTR lpSubKey, LPCTSTR lpValueName, LPVOID lpBuf, DWORD nSzBuf);

void ReadPosWindowFromReg(int ADefaultWidth, int ADefaultHeight, LPCTSTR ASubKey, WINDOWPLACEMENT &APos);
void WritePosWindowToReg(LPCTSTR ASubKey, WINDOWPLACEMENT &APos);

void ReadSettingsFromReg(LPCTSTR ASubKey, COLORREF &bkg, int &white, int &black, bool &fsb, bool &ftb);
void WriteSettingsToReg(LPCTSTR ASubKey, COLORREF bkg, int white, int black, bool fsb, bool ftb);