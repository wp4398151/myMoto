// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include <WinUser.h>
#include <Windows.h>
#include <stdio.h>

extern "C" __declspec(dllexport) LRESULT CALLBACK CallWndProc(int nCode, WPARAM wParam, LPARAM lParam)
{
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
	char buf[100] = { 0 };
	DWORD dwProcId = GetCurrentProcessId();
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		sprintf(buf, "-->>> %d", dwProcId);
		OutputDebugStringA(buf);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}



