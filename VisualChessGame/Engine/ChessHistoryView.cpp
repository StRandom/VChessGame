#include "ChessHistoryView.h"

ChessHistoryView::ChessHistoryView(VisualMoveRecorder* chb)
{
	mSubject = chb;
	mSubject->Attach(this);
}

void ChessHistoryView::Draw(){
	SimpleMove* sm = mSubject->getFirst();
	CListBox *list = ((CListBox*)(mSubject->getListBox()->GetDlgItem(IDC_LIST_OFMOVES)));
	int i = list->GetCount();
	while (i >= 0)
		list->DeleteString(i--);
	while (sm){
		char info[MAX_INFO_SIZE];
		_itoa(sm->id, info, 10);
		strcat(info, ".");
		strcat(info, sm->info);
		list->AddString(info);
		sm = sm->next;
	}
}

ChessHistoryView::~ChessHistoryView()
{
	mSubject->Detach(this);
}