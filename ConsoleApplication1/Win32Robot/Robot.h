#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "IEditFiller.h"

// 一个机器人负责跟踪处理一个窗口

class Robot : public IRobot
{
public:
	Robot(IEditFiller *pFiller) : m_pFiller(pFiller){ m_EditIdx = 0; ZeroMemory(m_bufWindowName, sizeof(m_bufWindowName)); }
	~Robot(){};
		
	VOID DoFill();
	VOID DoClick(INT posX, INT posY);
	BOOL OCRImage(RECT imageRect, LPSTR lpBuf, int size);
private:
	VOID dispachWnd(HWND hwnd);
	VOID SetEditText(HWND hwnd, LPSTR lpStr);
	VOID SaveWndImg(RECT subRect);

private:
	IEditFiller *m_pFiller;
	char m_bufWindowName[WINDOWNAMEMAXNUM];
	HWND m_hwnd;
	int m_EditIdx;
};

#endif _ROBOT_H_