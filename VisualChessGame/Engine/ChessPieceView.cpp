#include <iostream>
#include "ChessPieceView.h"

void ChessPieceView::Draw()
{
	if (!mSubject->HasCaptured())
		std::cout << mSubject->GetName() << "\t";
}