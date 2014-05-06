#include "Robot.h"
#include "TLoginForm.h"
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
			break;
		}
	case 2:	//投标号
		{
			memcpy(buf, USERNAME, sizeof(USERNAME));
			break;
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
}