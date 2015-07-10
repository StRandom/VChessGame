#include <htmlhelp.h>
#include <string>

void InitHelp();
void UpdateHelpFileName();
void FreeHelp();
void CallHelp(HWND hWnd, char* pcTopic);
void CloseHelp();