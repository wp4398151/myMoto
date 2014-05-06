#ifndef _IEDITFILLER_H_
#define _IEDITFILLER_H_



#include <Windows.h>

#define WINDOWNAMEMAXNUM 256
#define EDITTEXTMAX 256

class IRobot
{
public:
	virtual VOID DoClick(INT posX, INT posY) = 0;
};
// 用户需要实现该接口用来在填入信息，以及在之后或者之前进行按键的操作
class IEditFiller
{
public:
	virtual void beforeFill(IRobot *pRobot) = 0;
	virtual BOOL dispachWnd(HWND hwnd, int childIdx, LPSTR buf, INT bufSize) = 0;	//处理窗口程序,如果是返回FALSE则是不需要填入文字
	virtual void afterFill(IRobot *pRobot) = 0;
	virtual const LPSTR GetWndName() = 0;
};

#endif //_IEDITFILLER_H_