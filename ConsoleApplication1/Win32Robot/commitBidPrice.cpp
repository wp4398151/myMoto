#include "stdafx.h"
#include "IEditFiller.h"
#include "commitBidPrice.h"


void CommitBidPrice::beforeFill(IRobot *pRobot)
{
	return;
}

BOOL CommitBidPrice::dispachWnd(HWND hwnd, int childIdx, LPSTR buf, INT bufSize)
{
	if (!buf)
	{
		return FALSE;
	}

	switch (childIdx)
	{
	case 1:	//出价的验证码
	{
				//memcpy(buf, PASSWORD, sizeof(PASSWORD));
				return TRUE;
	}
	default:
		return FALSE;
	}
	return FALSE;
	return FALSE;
}

void CommitBidPrice::afterFill(IRobot *pRobot)
{
	pRobot->DoClick(159, 247);
}