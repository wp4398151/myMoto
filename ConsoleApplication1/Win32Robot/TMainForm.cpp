#include "stdafx.h"
#include "TMainForm.h"

VOID TMainForm::beforeFill(IRobot *pRobot)
{

}

BOOL TMainForm::dispachWnd(HWND hwnd, int childIdx, LPSTR buf, INT bufSize)
{
	if (!buf)
	{
		return FALSE;
	}

	switch (childIdx)
	{
	case 3:	//����
	{
				memcpy(buf, PRICE, sizeof(PRICE));
				return TRUE;
	}
	case 4:	//Ͷ���
	{
				memcpy(buf, PRICE, sizeof(PRICE));
				return TRUE;
	}
	default:
		return FALSE;
	}
	return FALSE;
}

VOID TMainForm::afterFill(IRobot *pRobot)
{
	//����
	pRobot->DoClick(815,400);
}