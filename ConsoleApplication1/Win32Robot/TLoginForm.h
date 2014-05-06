// 实现登陆界面操作
#ifndef _TLOGINFORM_H_
#define _TLOGINFORM_H_
#include "IEditFiller.h"

#define TLOGINFORMNAME "TLoginForm" 
#define USERNAME "12345678"
#define PASSWORD "1111"
#define PICNUM "437002"

class TLoginFrom : public IEditFiller
{
public:
	TLoginFrom(){ memcpy(m_WndName, TLOGINFORMNAME, sizeof(TLOGINFORMNAME)); }

	virtual VOID beforeFill(IRobot *pRobot);
	virtual BOOL dispachWnd(HWND hwnd, int childIdx, LPSTR buf, INT bufSize);	//处理窗口程序,如果是返回FALSE则是不需要填入文字
	virtual VOID afterFill(IRobot *pRobot);
	inline virtual const LPSTR GetWndName(){ return m_WndName; }
private:
	char m_WndName[WINDOWNAMEMAXNUM];
};

#endif //_TLOGINFORM_H_