#include "stdafx.h"
#include "TestPermissionForm.h"

void TestPermissionForm::beforeFill(IRobot *pRobot)
{
	return;
}

BOOL TestPermissionForm::dispachWnd(HWND hwnd, int childIdx, LPSTR buf, INT bufSize)
{
	return FALSE;
}

void TestPermissionForm::afterFill(IRobot *pRobot)
{
	pRobot->DoClick(280, 265);
}