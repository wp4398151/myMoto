#include "stdafx.h"
#include "Robot.h"
#include "TLoginForm.h"
#include "TMainForm.h"
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
			return TRUE;
		}
	case 2:	//Ͷ���
		{
			memcpy(buf, USERNAME, sizeof(USERNAME));
			return TRUE;
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
	Sleep(100);
	//���뵽��һ������
	TMainForm mainForm;
	Robot irobot(&mainForm);
	irobot.DoFill();
}