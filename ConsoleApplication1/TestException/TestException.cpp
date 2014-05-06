// TestException.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <WinSock2.h>
#include <Windows.h>
#include <WinBase.h>

void StartServer();
void SetEditText(HWND hwnd);
VOID dispachWnd(HWND hwnd);
VOID GetChildAndCaseProc();
VOID DoMouseClick(LONG dx, LONG dy);
VOID clickHwndPos(HWND hwnd, INT posX, INT posY);
//位置

int _tmain(int argc, _TCHAR* argv[])
{
	//先填好值
	//GetChildAndCaseProc();
//	SetEditText(TRUE);
	HWND hwnd = FindWindowA("TLoginForm", NULL);
	BOOL isOk = SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	clickHwndPos(hwnd, 250, 325);
	return 0;
}

//登陆的流程
VOID DoLoginProc()
{
	//"TLoginForm";
	//"TErrorBoxForm"
}

//点击指定窗口的指定相对窗口位置
VOID clickHwndPos(HWND hwnd, INT posX, INT posY)
{
	RECT rectWnd;
	memset(&rectWnd, 0, sizeof(rectWnd));
	GetWindowRect(hwnd, &rectWnd);
	DoMouseClick(rectWnd.left + posX, rectWnd.top + posY);
}

//鼠标点击
VOID DoMouseClick(LONG dx, LONG dy)
{
	int screenX = GetSystemMetrics(SM_CXSCREEN);
	int screenY = GetSystemMetrics(SM_CYSCREEN);
		
	LONG absoluteX = dx * (65535 / screenX);
	LONG absoluteY = dy * (65535 / screenY);

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
	input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN ;
	SendInput(1, &input, sizeof(INPUT));
	Sleep(1);
	input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP;
	SendInput(1, &input, sizeof(INPUT));
	Sleep(1);
}

//可以成功的输入字符串
void SetEditText(HWND hwnd, LPSTR lpStr)
{
	SendMessage(hwnd, WM_ACTIVATE, WA_ACTIVE, 0);
	SendMessage(hwnd, WM_ACTIVATE, WA_CLICKACTIVE, 0);
	SendMessageA(hwnd, WM_SETTEXT, 0, (LPARAM)lpStr);
//  Simulate a key press
//	keybd_event('A',
//		MapVirtualKeyA('A', 0),
//		KEYEVENTF_EXTENDEDKEY | 0,
//		0);

	// Simulate a key release
//	keybd_event('A',
//		MapVirtualKeyA('A', 0),
//		KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
//		0);
}

//将每个窗口得到的顺序进行编号方便分发给对应的处理程序
VOID GetChildAndCaseProc(LPSTR lpStrFormName)
{
	HWND hwnd = FindWindowA(lpStrFormName, NULL);
	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	HWND hwndChild = GetWindow(hwnd, GW_CHILD);
	do
	{
		dispachWnd(hwndChild);
		hwndChild = GetNextWindow(hwndChild, GW_HWNDNEXT);
	} while (hwndChild);

	clickHwndPos(hwnd, 680, 530);
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
					SetEditText(hwnd, "1111");
					//SendKeyToEdit(hwnd);
					break;
	}
	case 2:		//投标号
	{
					SetEditText(hwnd, "12345678");
					//SendKeyToEdit(hwnd);
					break;
	}
	case 3:		//图形校验
	{
					SetEditText(hwnd, "567733");
					//SendKeyToEdit(hwnd);
					break;
	}
	}
	sprintf_s(buf, "-->>> 得到的子窗口句柄: 0x%X", hwnd);
	OutputDebugStringA(buf);
}



#define BUF_SIZE 256

void StartServer()
{
	
	WSAData wsadata;
	WSAStartup(MAKEWORD(2,2), &wsadata);
	int retVal = 0;
	SOCKET            sServer;        //服务器套接字
	SOCKET            sClient;        //客户端套接字
	SOCKADDR_IN       addrServ;;     //服务器地址
	char buf[BUF_SIZE];
	ZeroMemory(buf, BUF_SIZE);
	//创建套接字
	sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//服务器套接字地址 
	addrServ.sin_family = AF_INET;
	addrServ.sin_port = htons(4999);
	addrServ.sin_addr.s_addr = INADDR_ANY;
	//绑定套接字
	retVal = bind(sServer, (LPSOCKADDR)&addrServ, sizeof(SOCKADDR_IN));
	if (retVal == SOCKET_ERROR)
	{
		retVal = WSAGetLastError();
	}

	//开始监听 
	retVal = listen(sServer, 1);
	//接受客户端请求
	sockaddr_in addrClient;
	ZeroMemory(&addrClient, sizeof(sockaddr_in));
	int addrClientlen = sizeof(addrClient);
	sClient = accept(sServer, (sockaddr FAR*)&addrClient, &addrClientlen);
	//接收客户端数据
	retVal = recv(sClient, buf, BUF_SIZE, 0);

	MessageBoxA(NULL, buf, "收到", MB_OK);
	//退出
	closesocket(sServer);    //关闭套接字
	closesocket(sClient);    //关闭套接字
	WSACleanup();            //释放套接字资源;
}