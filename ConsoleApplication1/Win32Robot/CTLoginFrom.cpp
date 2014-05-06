#include "stdafx.h"
#include "Robot.h"
#include "TLoginForm.h"
#include "TMainForm.h"
#include "TestPermissionForm.h"

VOID TLoginFrom::beforeFill(IRobot *pRobot)
{
	pRobot->DoClick(250, 325);
	//需要点击一下验证窗口
	TestPermissionForm testPForm;
	Robot irobot(&testPForm);
	irobot.DoFill();
}

BOOL TLoginFrom::dispachWnd(HWND hwnd, int childIdx, LPSTR buf, INT bufSize)
{
	if (!buf)
	{
		return FALSE;
	}

	switch (childIdx)
	{
	case 1:	//密码
	 	{
			memcpy(buf, PASSWORD, sizeof(PASSWORD));
			return TRUE;
		}
	case 2:	//投标号
		{
			memcpy(buf, USERNAME, sizeof(USERNAME));
			return TRUE;
		}
	case 3:	//验证码
		{
			memcpy(buf, PICNUM, sizeof(PICNUM));
			return TRUE;
		}
	default:
		return FALSE;
	}
	return FALSE;
}

VOID TLoginFrom::afterFill(IRobot *pRobot)
{
	//需要点击一下确定
	pRobot->DoClick(680, 530);
	Sleep(100);
	//进入到下一个窗口
	TMainForm mainForm;
	Robot irobot(&mainForm);
	irobot.DoFill();
}