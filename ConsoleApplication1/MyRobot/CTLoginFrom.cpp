#include "Robot.h"
#include "TLoginForm.h"
#include "TestPermissionForm.h"

VOID TLoginFrom::beforeFill(IRobot *pRobot)
{
	pRobot->DoClick(250, 325);
	//��Ҫ���һ����֤����
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
	case 1:	//����
	 	{
			memcpy(buf, PASSWORD, sizeof(PASSWORD));
			break;
		}
	case 2:	//Ͷ���
		{
			memcpy(buf, USERNAME, sizeof(USERNAME));
			break;
		}
	case 3:	//��֤��
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
	//��Ҫ���һ��ȷ��
	pRobot->DoClick(680, 530);
}