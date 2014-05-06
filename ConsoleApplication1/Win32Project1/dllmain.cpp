// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include <WinUser.h>
#include <Windows.h>
#include <stdio.h>
#include "Screen.h"
VOID DoMyLogic();
VOID SaveWndImg(HWND hwnd, RECT subRect);
VOID GetChildAndCaseProc(HWND hwnd);
VOID dispachWnd(HWND hwnd);
VOID SendKeyToEdit(HWND hwnd);
//登陆验证图片
RECT rectLoginFrom = { 688, 440, 110, 30 };
//登陆投标号
//RECT rectLoginName = { 248, , 122, 27};
//登陆密码
//RECT rectLoginPass = {};
extern "C" __declspec(dllexport) LRESULT CALLBACK CallWndProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	char buf[100] = { 0 };
	DWORD dwProcId = GetCurrentProcessId();
	sprintf(buf, "-->>> 处理的ID: %d", dwProcId);

		CWPSTRUCT *pStruct = (CWPSTRUCT*)lParam;
		if (pStruct && pStruct->message == WM_LBUTTONUP)
		{
			HWND hwnd = pStruct->hwnd;
			WCHAR buf[MAX_PATH] = {0};
			WINDOWINFO wndInfo;
			wndInfo.cbSize = sizeof(WINDOWINFO);
			int iRet = GetWindowTextW(hwnd, buf, MAX_PATH);
			if (iRet !=  0)
			{
				lstrcatW(buf, L" 得到该窗口->> ");
				OutputDebugStringW(buf);
			}
		}
		return CallNextHookEx(NULL,nCode, wParam, lParam);
}

BOOL APIENTRY DllMain( HMODULE hModule,
					   DWORD  ul_reason_for_call,
					   LPVOID lpReserved
					 )
{
	DWORD dwProcId = GetCurrentProcessId();
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DoMyLogic();
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

VOID DoMyLogic()
{
	char buf[100] = { 0 };
	DWORD dwProcId = GetCurrentProcessId();
	DWORD dwWndProcId = 0;
	HWND hwnd = FindWindowA( "TLoginForm", NULL);
	GetWindowThreadProcessId(hwnd, &dwWndProcId);

	sprintf(buf, "-->>>  PROCID: %d , HWND: 0x%X  WindowProcId: %d", dwProcId, hwnd, dwWndProcId);
	OutputDebugStringA(buf);
	if (dwProcId == dwWndProcId)
	{
		RECT rect;
		char buf[64];
		memset(&rect, 0, sizeof(rect));
		GetWindowRect(hwnd, &rect);
		sprintf(buf, "-->>> 得到的进程ID: %d", dwProcId);
		//需要将对应的窗口大小得出
		//OutputDebugStringA(buf);
		SaveWndImg(hwnd, rectLoginFrom);
		//MessageBoxA(NULL, buf, "Info", MB_OK);
		
	}
}

VOID SaveWndImg(HWND hwnd, RECT subRect)
{
	RECT rect;
	::GetWindowRect(hwnd, &rect);
	//SetForegroundWindow(hwnd);
	//ShowWindow(hwnd, SW_SHOWNORMAL);
	SetWindowPos(hwnd, HWND_TOPMOST,  0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	//CScreen *screen = new CScreen(16, NULL, rect.right - rect.left, rect.bottom - rect.top);
	CScreen *screen = new CScreen(16, NULL, subRect.right, subRect.bottom);

	screen->GetScreen(rect.left + subRect.left, rect.top + subRect.top, subRect.right, subRect.bottom);
	screen->SetScreentoPath("C:\\1.bmp");
	
	GetChildAndCaseProc(hwnd);
	delete screen;
}

VOID GetChildAndCaseProc(HWND hwnd)
{
	
	HWND hwndChild = GetWindow(hwnd, GW_CHILD);
	
	do
	{
		dispachWnd(hwndChild);
		hwndChild = GetNextWindow(hwndChild, GW_HWNDNEXT);
	} while (hwndChild);
}

VOID dispachWnd(HWND hwnd)
{
	char buf[100] = { 0 };
	static int count = 0;
	count++;
	switch (count)
	{
		case 1:		//密码
		{
				SendKeyToEdit(hwnd);
				break;
		}
		case 2:		//投标号
		{
				SendKeyToEdit(hwnd);
				break;
		}
		case 3:		//图形校验
		{
				SendKeyToEdit(hwnd);
				break;
		}
	}
	sprintf(buf, "-->>> 得到的子窗口句柄: 0x%X", hwnd);
	OutputDebugStringA(buf);
}
/*
void SimKeyClick(UINT vk_Code)
{
	//扩展键
	DWORD dwFlages = 0;
		switch(vk_Code)
	{
	default:
		break;
	case(VK_NUMLOCK) :
	case(VK_CAPITAL) :
	case(VK_SCROLL) :
	case(VK_CONTROL) :
	case(VK_LCONTROL) :
	case(VK_RCONTROL) :
	case(VK_SHIFT) :
	case(VK_LSHIFT) :
	case(VK_RSHIFT) :
	case(VK_MENU) :
	case(VK_LMENU) :
	case(VK_RMENU) :
				   dwFlages|= KEYEVENTF_EXTENDEDKEY;
	}
	WORD wScan = MapVirtualKey(vk_Code, 0);
	INPUT Input[2] = { 0 };
	Input[0].type = INPUT_KEYBOARD;
	Input[0].ki.wVk = vk_Code;
	Input[0].ki.wScan = wScan;
	Input[0].ki.dwFlags = dwFlages;
	Input[1].type = INPUT_KEYBOARD;
	Input[1].ki.wVk= vk_Code;
	Input[1].ki.wScan= wScan;
	Input[1].ki.dwFlags= dwFlages | KEYEVENTF_KEYUP;
	SendInput(2, Input, sizeof(INPUT));
}
*/
VOID SendKeyToEdit(HWND hwnd)
{
	//WORD wScan = MapVirtualKey('a', 0);
	SendMessage(hwnd, WM_ACTIVATE, WA_CLICKACTIVE, 0);

	keybd_event('A', 0, 0, 0);
	keybd_event('A', 0, KEYEVENTF_KEYUP, 0);
	//INPUT inputs;
	//inputs.type = INPUT_KEYBOARD;
	//inputs.ki.time = 0;
	//inputs.ki.wScan = wScan;
	//inputs.ki.wVk = 'a';
	//inputs.ki.dwFlags = 0;
	//SendInput(1, &inputs, sizeof(inputs));
}