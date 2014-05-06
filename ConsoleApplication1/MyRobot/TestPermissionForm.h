// ʵ�ֵ�½������Ե�½���Ĳ���
#ifndef _TESTPERMISSIONFORM_H_
#define _TESTPERMISSIONFORM_H_

#include "IEditFiller.h"

#define TESTPERMISSIONFORMNAME "TErrorBoxForm" 

class TestPermissionForm : public IEditFiller
{
public:
	TestPermissionForm(){ memcpy(m_WndName, TESTPERMISSIONFORMNAME, sizeof(TESTPERMISSIONFORMNAME)); }

	virtual void beforeFill(IRobot *pRobot);
	virtual BOOL dispachWnd(HWND hwnd, int childIdx, LPSTR buf, INT bufSize);	//�����ڳ���,����Ƿ���FALSE���ǲ���Ҫ��������
	virtual void afterFill(IRobot *pRobot);
	inline virtual const LPSTR GetWndName(){ return m_WndName; }
private:
	char m_WndName[WINDOWNAMEMAXNUM];
};
#endif _TESTPERMISSIONFORM_H_