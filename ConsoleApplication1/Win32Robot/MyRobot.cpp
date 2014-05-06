// MyRobot.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Robot.h"
#include "Util.h"
#include "TLoginForm.h"
#include "Screen.h"

VOID Robot::DoFill()
{
	if (!m_pFiller || !m_pFiller->GetWndName())
	{
		DOLOGA("没有传入填信息的处理程序");
		return;
	}
	const LPSTR pWindowName = m_pFiller->GetWndName();
	HWND hwnd = FindWindowA(pWindowName, NULL);
	while(!hwnd ||!(WS_VISIBLE & GetWindowLong(hwnd, GWL_STYLE)))
	{
		DOLOGA("没有得到指定的窗口，或者是窗口没有显示");
		Sleep(100);
	}
	strcpy_s(m_bufWindowName, pWindowName);
	m_hwnd = hwnd;

	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	m_pFiller->beforeFill(this);
	HWND hwndChild = GetWindow(hwnd, GW_CHILD);
	if (hwndChild)
	{
		do
		{
			dispachWnd(hwndChild);
			hwndChild = GetNextWindow(hwndChild, GW_HWNDNEXT);
		} while (hwndChild);
	}
	m_pFiller->afterFill(this);
}

//点击当前窗口的相对位置
VOID Robot::DoClick(INT posX, INT posY)
{
		RECT rectWnd;
		memset(&rectWnd, 0, sizeof(rectWnd));
		GetWindowRect(m_hwnd, &rectWnd);

		//SendMessage(m_hwnd, WM_ACTIVATEAPP, 0, 0);

		int screenX = GetSystemMetrics(SM_CXSCREEN);
		int screenY = GetSystemMetrics(SM_CYSCREEN);

		LONG absoluteX = (rectWnd.left + posX) * (65535 / screenX);
		LONG absoluteY = (rectWnd.top + posY)* (65535 / screenY);

		INPUT input;
		input.type = INPUT_MOUSE;
		input.mi.dx = absoluteX;
		input.mi.dy = absoluteY;
		input.mi.mouseData = 0;
		input.mi.time = 0;
		input.mi.dwExtraInfo = 0;
		input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
		SendInput(1, &input, sizeof(INPUT));
		Sleep(1);
		input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN;
		SendInput(1, &input, sizeof(INPUT));
		Sleep(1);
		input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP;
		SendInput(1, &input, sizeof(INPUT));
		Sleep(1);
}

VOID Robot::dispachWnd(HWND hwnd)
{
	char buf[EDITTEXTMAX] = { 0 };
	if (m_pFiller->dispachWnd(hwnd, ++m_EditIdx, buf, EDITTEXTMAX))
	{
		SetEditText(hwnd, buf);
	}
}

//填入指定的信息
void Robot::SetEditText(HWND hwnd, LPSTR lpStr)
{
	SendMessage(hwnd, WM_ACTIVATE, WA_ACTIVE, 0);
	SendMessage(hwnd, WM_ACTIVATE, WA_CLICKACTIVE, 0);
	
	SendMessageA(hwnd, WM_SETTEXT, 0, (LPARAM)lpStr);
}

//识别窗口上指定的图片,并返回字符串
BOOL Robot::OCRImage(RECT imageRect, LPSTR lpBuf, int size)
{
	
	return TRUE;
}

//将当前窗口的指定范围的截图保存成文件
VOID Robot::SaveWndImg(RECT subRect)
{
	RECT rect;
	::GetWindowRect(m_hwnd, &rect);
	SetWindowPos(m_hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	CScreen *screen = new CScreen(16, NULL, subRect.right, subRect.bottom);

	screen->GetScreen(rect.left + subRect.left, rect.top + subRect.top, subRect.right, subRect.bottom);
	screen->SetScreentoPath("C:\\1.bmp");
	delete screen;
}
