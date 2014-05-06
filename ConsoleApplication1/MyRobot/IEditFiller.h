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
// �û���Ҫʵ�ָýӿ�������������Ϣ���Լ���֮�����֮ǰ���а����Ĳ���
class IEditFiller
{
public:
	virtual void beforeFill(IRobot *pRobot) = 0;
	virtual BOOL dispachWnd(HWND hwnd, int childIdx, LPSTR buf, INT bufSize) = 0;	//�����ڳ���,����Ƿ���FALSE���ǲ���Ҫ��������
	virtual void afterFill(IRobot *pRobot) = 0;
	virtual const LPSTR GetWndName() = 0;
};

#endif //_IEDITFILLER_H_