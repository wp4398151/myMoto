// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
VOID StartClient();

int _tmain(int argc, _TCHAR* argv[])
{
	
	return 0;
}

void TestInJection()
{
	HOOKPROC pFunc = NULL;
	HMODULE hdll = LoadLibraryW(L"Win32Project1.dll");

	pFunc = (HOOKPROC)GetProcAddress(hdll, "_CallWndProc@12");
	if (pFunc == NULL){
		FreeLibrary(hdll);
		return 0;
	}

	HINSTANCE hInstApp = GetModuleHandle(NULL);
	HHOOK hhok = SetWindowsHookExW(WH_CALLWNDPROC/*WH_SYSMSGFILTER*/, pFunc, hdll, 0);

	if (!hhok)
	{
		DWORD nCode = GetLastError();

		return 0;
	}
	for (int i = 0; i < 1; i++)
	{
		Sleep(1000);
	}
	HWND hwnd = FindWindowA("TLoginForm", NULL);
	SendMessageA(hwnd, WM_USER + 100, 0, 0);
	MessageBoxA(NULL, "", "", MB_OK);
	UnhookWindowsHookEx(hhok);
	FreeLibrary(hdll);

}

#define MY_ADDRASS	"127.0.0.1"
#define MY_PORT		4999		
#define BUF_SIZE	256
VOID StartClient()
{
	char buf[BUF_SIZE];
	ZeroMemory(buf, BUF_SIZE);
	int retVal;
	WSADATA            wsd;            //WSADATA变量
	SOCKET             sHost;          //服务器套接字
	SOCKADDR_IN        servAddr;       //服务器地址
	WSAStartup(MAKEWORD(2, 2), &wsd);
	sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//设置服务器地址
	servAddr.sin_family = AF_INET;//地址家族
	servAddr.sin_addr.s_addr = inet_addr(MY_ADDRASS);//IP地址
	servAddr.sin_port = htons((short)MY_PORT);//服务端口号
	int nServAddlen = sizeof(servAddr);//填充该结构的大小

	//连接服务器
	retVal = connect(sHost, (LPSOCKADDR)&servAddr, sizeof(servAddr));

	//向服务器发送数据
	lstrcpyA(buf, "Trans OK");
	retVal = send(sHost, buf, strlen(buf),  0);

	//退出
	closesocket(sHost);    //关闭套接字
	WSACleanup();        //释放套接字资源
}