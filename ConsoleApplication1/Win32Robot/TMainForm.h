#ifndef _TMAINFORM_H_
#define _TMAINFORM_H_
#include "IEditFiller.h"

#define TMAINFORMNAME "TMainForm"

#define PRICE "28000"
	
class TMainForm: public IEditFiller
{
public:
	TMainForm(){ memcpy(m_WndName, TMAINFORMNAME, sizeof(TMAINFORMNAME)); }

	virtual VOID beforeFill(IRobot *pRobot);
	virtual BOOL dispachWnd(HWND hwnd, int childIdx, LPSTR buf, INT bufSize);	//处理窗口程序,如果是返回FALSE则是不需要填入文字
	virtual VOID afterFill(IRobot *pRobot);
	inline virtual const LPSTR GetWndName(){ return m_WndName; }
private:
	char m_WndName[WINDOWNAMEMAXNUM];
};
#endif //_TMAINFORM_H_