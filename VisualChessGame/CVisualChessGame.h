/*! @file /** CVisualChessGame.cpp */

/**
 * 1. ����, ������ � ���������, ��������� ��� ������ ��������� ��� �������������.
 *    �������.������ ���� - �����, ���������, ���������, ��������� ���, ������ �������
 *    �������� ���, �����.��������� ������ ������ �������� ���������� � �������
 *    ���������("��� ������� ������", "������� ������ �����" � �.�.)
 * 2. ���������� ������ ��������� ����, ���� �������� �� �������� ������.����������
 *    ����� ������, ���� ����� ����� �� �������� ������.������� ���� ������ ��������������
 *    � ����.��� ����������.
 * 3. ���������� ������ ���� � memory - mapped file.�������� ������������ �����.
 * 4. ����� ���� ������(����, ����� � �.�), ����� ������� ����.����� ������, ����
 *    ����� �����.
 * 5. ���������� ��������(�����, ����� � �.�.) � ������� ��� �������� ������������.
 * 6. Undo � Redo �� ����� ����� �����.������ ���� �������� ������, � �.�.� ���� -
 *    ����������� ����� �������� ����� ����������� ����.
 * 7. ������� ����� � �� �������� � ��������� ����.������ ������ � ���� ���������
 *    ��������������.
 * 8. ������ ������� ������ ����� ����������, ���� ������ ����� ��� ��������.
 */
#pragma once

#include "afxwin.h"
#include "CMainWnd.h"

class CVisualChessGame : public CWinApp
{
private:
	HANDLE m_hMutex;
public:
	CVisualChessGame();
	~CVisualChessGame(); 
	virtual BOOL InitInstance();
};