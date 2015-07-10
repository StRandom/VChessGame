#include <Windows.h>
#include "resource.h"
#include "Help.h"

using namespace std;

#define HH_DISPLAY_TOPIC 0x0000
typedef HWND(WINAPI *HTMLHELP) (HWND, LPCSTR, UINT, DWORD);

HTMLHELP g_HtmlHelp;
HMODULE g_hDllHtmlHelp;
string g_HelpFileName;

void UpdateHelpFileName() {
	char path[MAX_PATH], drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];
	GetModuleFileName(NULL, path, sizeof(path));
	_splitpath(path, drive, dir, fname, ext);
	g_HelpFileName = (string)drive + (string)dir + (string)"Help.chm";
}

void InitHelp()
{
	g_hDllHtmlHelp = LoadLibrary("HHCtrl.ocx");
	g_HtmlHelp = (HTMLHELP)GetProcAddress(g_hDllHtmlHelp, "HtmlHelpA");
	UpdateHelpFileName();
}

void FreeHelp()
{
	if (!g_hDllHtmlHelp)
		FreeLibrary(g_hDllHtmlHelp);
}

void CallHelp(HWND hWnd, char* pcTopic) {
	if (!g_HtmlHelp) return;
	string s = g_HelpFileName + "::html/" + pcTopic;
	g_HtmlHelp(NULL, s.c_str(), HH_DISPLAY_TOPIC, NULL);
}


void CloseHelp() { g_HtmlHelp(NULL, NULL, HH_CLOSE_ALL, NULL); }