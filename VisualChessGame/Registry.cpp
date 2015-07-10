#include "resource.h"
#include "Registry.h"


void ReadFromReg(HKEY hKeyGlob, LPCTSTR lpSubKey, LPCTSTR lpValueName,
	LPSTR lpStr, DWORD nSzStr)
{
	HKEY hKey;
	DWORD Disp;
	lpStr[0] = 0;
	if (RegCreateKeyEx(hKeyGlob, lpSubKey, 0, NULL, REG_OPTION_NON_VOLATILE,
		KEY_QUERY_VALUE, NULL, &hKey, &Disp) != ERROR_SUCCESS) return;
	__try {
		if (RegQueryValueEx(hKey, lpValueName, 0, NULL, (BYTE*)lpStr, &nSzStr)
			!= ERROR_SUCCESS) lpStr[0] = 0;
	}
	__finally { RegCloseKey(hKey); }
}

void WriteStrToReg(HKEY hKeyGlob, LPCTSTR lpSubKey, LPCTSTR lpValueName, LPCSTR lpStr)
{
	HKEY hKey;
	DWORD Disp;
	if (RegCreateKeyEx(hKeyGlob, lpSubKey, 0, NULL, REG_OPTION_NON_VOLATILE,
		KEY_QUERY_VALUE | KEY_SET_VALUE, NULL, &hKey, &Disp) != ERROR_SUCCESS) return;
	__try {
		RegSetValueEx(hKey, lpValueName, 0, REG_SZ, (BYTE*)lpStr, strlen(lpStr) + 1);
	}
	__finally { RegCloseKey(hKey); }
}

void ReadStrFromRegHKCU(LPCTSTR lpSubKey, LPCTSTR lpValueName, LPSTR lpStr, DWORD nSzStr) {
	ReadFromReg(HKEY_CURRENT_USER, lpSubKey, lpValueName, lpStr, nSzStr);
}

void WriteStrToRegHKCU(LPCTSTR lpSubKey, LPCTSTR lpValueName, LPCSTR lpStr) {
	WriteStrToReg(HKEY_CURRENT_USER, lpSubKey, lpValueName, lpStr);
}

int ReadIntFromRegHKCU(LPCTSTR lpSubKey, LPCTSTR lpValueName, int ADefVal) {
	int res = ADefVal; char sInt[32];
	ReadFromReg(HKEY_CURRENT_USER, lpSubKey, lpValueName, sInt, sizeof(sInt));
	if (lstrlen(sInt)) res = atoi(sInt);
	return res;
}

void WriteIntToRegHKCU(LPCTSTR lpSubKey, LPCTSTR lpValueName, UINT AVal)
{
	HKEY hKey;
	DWORD Disp;
	char sInt[32];

	_itoa(AVal, sInt, 10);
	if (RegCreateKeyEx(HKEY_CURRENT_USER, lpSubKey, 0, NULL, REG_OPTION_NON_VOLATILE,
		KEY_QUERY_VALUE | KEY_SET_VALUE, NULL, &hKey, &Disp) != ERROR_SUCCESS) return;
	__try {
		RegSetValueEx(hKey, lpValueName, 0, REG_SZ, (BYTE*)sInt, strlen(sInt) + 1);
	}
	__finally { RegCloseKey(hKey); }
}

BOOL ReadMemFromRegHKCU(LPCTSTR lpSubKey, LPCTSTR lpValueName,
	LPVOID lpBuf, DWORD nSzBuf) {
	HKEY hKey; DWORD Disp; BOOL bOk;
	ZeroMemory(lpBuf, nSzBuf);
	if (RegCreateKeyEx(HKEY_CURRENT_USER, lpSubKey, 0, NULL, REG_OPTION_NON_VOLATILE,
		KEY_QUERY_VALUE, NULL, &hKey, &Disp) != ERROR_SUCCESS) return FALSE;
	__try {
		bOk = RegQueryValueEx(hKey, lpValueName, 0, NULL, (BYTE*)lpBuf, &nSzBuf)
			== ERROR_SUCCESS;
	}
	__finally { RegCloseKey(hKey); }
	return bOk;
}

BOOL WriteMemToRegHKCU(LPCTSTR lpSubKey, LPCTSTR lpValueName,
	LPVOID lpBuf, DWORD nSzBuf) {
	HKEY hKey; DWORD Disp; BOOL bOk;
	if (RegCreateKeyEx(HKEY_CURRENT_USER, lpSubKey, 0, NULL, REG_OPTION_NON_VOLATILE,
		KEY_QUERY_VALUE | KEY_SET_VALUE, NULL, &hKey, &Disp) != ERROR_SUCCESS) return FALSE;
	__try {
		bOk = RegSetValueEx(hKey, lpValueName, 0, REG_BINARY, (BYTE*)lpBuf, nSzBuf)
			== ERROR_SUCCESS;
	}
	__finally { RegCloseKey(hKey); }
	return bOk;
}

void ExtractFilePath(LPCSTR pszFileName, LPSTR pszFilePath)
{
	/*	Извлечение из полного имени файла pszFileName полного пути в pszFilePath
	(если путь оканчивается на разделитель \ или :, то он включается в путь)
	*/
	if (pszFilePath)
		if (pszFileName)
		{
		int k = 0;
		for (int i = 0; pszFileName[i] != 0; i++)
			if ((pszFileName[i] == ':') || (pszFileName[i] == '\\')) k = i;
		if (pszFileName != pszFilePath)
			memcpy(pszFilePath, pszFileName, k + 1);
		pszFilePath[k + 1] = 0;
		}
		else
			pszFilePath[0] = 0;
}

void ReadPosWindowFromReg(int ADefaultWidth, int ADefaultHeight, LPCTSTR ASubKey,
	WINDOWPLACEMENT &APos)
{
	int DefW = ADefaultWidth, DefH = ADefaultHeight,
		DefL = (GetSystemMetrics(SM_CXSCREEN) - DefW) / 2,
		DefT = (GetSystemMetrics(SM_CYSCREEN) - DefH) / 2;
	APos.length = sizeof(WINDOWPLACEMENT);
	APos.flags = 0;
	APos.ptMaxPosition.x = ReadIntFromRegHKCU(ASubKey, REGPAR_POSMAXX, -1);
	APos.ptMaxPosition.y = ReadIntFromRegHKCU(ASubKey, REGPAR_POSMAXY, -1);
	APos.ptMinPosition.x = ReadIntFromRegHKCU(ASubKey, REGPAR_POSMINX, -1);
	APos.ptMinPosition.y = ReadIntFromRegHKCU(ASubKey, REGPAR_POSMINY, -1);
	APos.rcNormalPosition.left = ReadIntFromRegHKCU(ASubKey, REGPAR_POSL, DefL);
	APos.rcNormalPosition.top = ReadIntFromRegHKCU(ASubKey, REGPAR_POST, DefT);
	APos.rcNormalPosition.right = ReadIntFromRegHKCU(ASubKey, REGPAR_POSR, DefL + DefW);
	APos.rcNormalPosition.bottom = ReadIntFromRegHKCU(ASubKey, REGPAR_POSB, DefT + DefH);
	int w = GetSystemMetrics(SM_CXFULLSCREEN),
		h = GetSystemMetrics(SM_CYFULLSCREEN), g = 20;
	if (APos.rcNormalPosition.right < g) APos.rcNormalPosition.right = g;
	if (APos.rcNormalPosition.bottom < g) APos.rcNormalPosition.bottom = g;
	if (APos.rcNormalPosition.left > w - g) APos.rcNormalPosition.left = w - g;
	if (APos.rcNormalPosition.top > h - g) APos.rcNormalPosition.top = h - g;
	if (APos.showCmd == SW_HIDE) APos.showCmd = SW_SHOW;
}

void WritePosWindowToReg(LPCTSTR ASubKey, WINDOWPLACEMENT &APos)
{
	WriteIntToRegHKCU(ASubKey, REGPAR_POSMAXX, APos.ptMaxPosition.x);
	WriteIntToRegHKCU(ASubKey, REGPAR_POSMAXY, APos.ptMaxPosition.y);
	WriteIntToRegHKCU(ASubKey, REGPAR_POSMINX, APos.ptMinPosition.x);
	WriteIntToRegHKCU(ASubKey, REGPAR_POSMINY, APos.ptMinPosition.y);
	WriteIntToRegHKCU(ASubKey, REGPAR_POSL, APos.rcNormalPosition.left);
	WriteIntToRegHKCU(ASubKey, REGPAR_POST, APos.rcNormalPosition.top);
	WriteIntToRegHKCU(ASubKey, REGPAR_POSR, APos.rcNormalPosition.right);
	WriteIntToRegHKCU(ASubKey, REGPAR_POSB, APos.rcNormalPosition.bottom);
}

void ReadSettingsFromReg(LPCTSTR ASubKey, COLORREF &bkg, int &white, int &black, bool &fsb, bool &ftb)
{
	int isb, itb;
	bkg = ReadIntFromRegHKCU(ASubKey, REGPAR_BKG, -1);
	white = ReadIntFromRegHKCU(ASubKey, REGPAR_WHITECLR, 0);
	black = ReadIntFromRegHKCU(ASubKey, REGPAR_BLACKCLR, 0);
	isb = ReadIntFromRegHKCU(ASubKey, REGPAR_FSB, 1); 
	itb = ReadIntFromRegHKCU(ASubKey, REGPAR_FTB, 1);
	fsb = (isb == 0); ftb = (itb == 0);
	if (bkg == -1)
		bkg = RGB(255,255,255);
}

void WriteSettingsToReg(LPCTSTR ASubKey, COLORREF bkg, int white, int black, bool fsb, bool ftb)
{
	WriteIntToRegHKCU(ASubKey, REGPAR_BKG, bkg);
	WriteIntToRegHKCU(ASubKey, REGPAR_WHITECLR, white);
	WriteIntToRegHKCU(ASubKey, REGPAR_BLACKCLR, black);
	WriteIntToRegHKCU(ASubKey, REGPAR_FSB, fsb);
	WriteIntToRegHKCU(ASubKey, REGPAR_FTB, ftb);
}

void GetFolderMyDoc(char *pcPath, DWORD nSzBuf)
{
	ReadFromReg(HKEY_CURRENT_USER,
		"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders",
		"Personal", pcPath, nSzBuf);
	if (!lstrlen(pcPath))
		ReadFromReg(HKEY_USERS,
		".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders",
		"Personal", pcPath, nSzBuf);
	if (!lstrlen(pcPath))
		lstrcpy(pcPath, "C:\\My Documents");
}