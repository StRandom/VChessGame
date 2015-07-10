#pragma once

#include "Engine\MoveRecorder.h"
#include "CDlgListOfMoves.h"
#include <afxwin.h>
#include <Windows.h>

class VisualMoveRecorder : public MoveRecorder {
public:
	VisualMoveRecorder();
	virtual ~VisualMoveRecorder();
	void setListBox(CDlgListOfMoves *clb) { m_ListBox = clb; }
	CDlgListOfMoves *getListBox() { return m_ListBox; }
protected:
	CDlgListOfMoves *m_ListBox;
};