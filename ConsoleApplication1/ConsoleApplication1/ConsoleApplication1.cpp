// ConsoleApplication1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <Windows.h>
VOID StartClient();

int _tmain(int argc, _TCHAR* argv[])
{
	if (TRUE)
	{
		StartClient();
		return 0;
	}
	HOOKPROC pFunc = NULL;
	HMODULE hdll = LoadLibraryW(L"Win32Project1.dll");
	
	pFunc = (HOOKPROC)GetProcAddress(hdll, "_CallWndProc@12");
	if (pFunc == NULL){
		FreeLibrary(hdll);
		return 0;
	}
	
	HINSTANCE hInstApp = GetModuleHandle(NULL);
	HHOOK hhok = SetWindowsHookExW(WH_CALLWNDPROC, pFunc, hdll, 0);
	
	if ( !hhok)
	{
		return 0;
	}
	for ( int i = 0 ; i < 20; i++ )
	{
		Sleep(1000);
	}

	MessageBoxA(NULL, "", "", MB_OK);
	UnhookWindowsHookEx(hhok);
	FreeLibrary(hdll);
	char a = getchar();
	return 0;
}

#define MY_ADDRASS	"127.0.0.1"
#define MY_PORT		4999		
#define BUF_SIZE	256
VOID StartClient()
{
	char buf[BUF_SIZE];
	ZeroMemory(buf, BUF_SIZE);
	int retVal;
	WSADATA            wsd;            //WSADATA����
	SOCKET             sHost;          //�������׽���
	SOCKADDR_IN        servAddr;       //��������ַ
	WSAStartup(MAKEWORD(2, 2), &wsd);
	sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//���÷�������ַ
	servAddr.sin_family = AF_INET;//��ַ����
	servAddr.sin_addr.s_addr = inet_addr(MY_ADDRASS);//IP��ַ
	servAddr.sin_port = htons((short)MY_PORT);//����˿ں�
	int nServAddlen = sizeof(servAddr);//���ýṹ�Ĵ�С

	//���ӷ�����
	retVal = connect(sHost, (LPSOCKADDR)&servAddr, sizeof(servAddr));

	//���������������
	lstrcpyA(buf, "Trans OK");
	retVal = send(sHost, buf, strlen(buf), 0);

	//�˳�
	closesocket(sHost);    //�ر��׽���
	WSACleanup();        //�ͷ��׽�����Դ
}