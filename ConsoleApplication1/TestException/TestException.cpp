// TestException.cpp : �������̨Ӧ�ó������ڵ㡣
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
//λ��

int _tmain(int argc, _TCHAR* argv[])
{
	//�����ֵ
	//GetChildAndCaseProc();
//	SetEditText(TRUE);
	HWND hwnd = FindWindowA("TLoginForm", NULL);
	BOOL isOk = SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	clickHwndPos(hwnd, 250, 325);
	return 0;
}

//��½������
VOID DoLoginProc()
{
	//"TLoginForm";
	//"TErrorBoxForm"
}

//���ָ�����ڵ�ָ����Դ���λ��
VOID clickHwndPos(HWND hwnd, INT posX, INT posY)
{
	RECT rectWnd;
	memset(&rectWnd, 0, sizeof(rectWnd));
	GetWindowRect(hwnd, &rectWnd);
	DoMouseClick(rectWnd.left + posX, rectWnd.top + posY);
}

//�����
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

//���Գɹ��������ַ���
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

//��ÿ�����ڵõ���˳����б�ŷ���ַ�����Ӧ�Ĵ������
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
	case 1:		//����
	{
					SetEditText(hwnd, "1111");
					//SendKeyToEdit(hwnd);
					break;
	}
	case 2:		//Ͷ���
	{
					SetEditText(hwnd, "12345678");
					//SendKeyToEdit(hwnd);
					break;
	}
	case 3:		//ͼ��У��
	{
					SetEditText(hwnd, "567733");
					//SendKeyToEdit(hwnd);
					break;
	}
	}
	sprintf_s(buf, "-->>> �õ����Ӵ��ھ��: 0x%X", hwnd);
	OutputDebugStringA(buf);
}



#define BUF_SIZE 256

void StartServer()
{
	
	WSAData wsadata;
	WSAStartup(MAKEWORD(2,2), &wsadata);
	int retVal = 0;
	SOCKET            sServer;        //�������׽���
	SOCKET            sClient;        //�ͻ����׽���
	SOCKADDR_IN       addrServ;;     //��������ַ
	char buf[BUF_SIZE];
	ZeroMemory(buf, BUF_SIZE);
	//�����׽���
	sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//�������׽��ֵ�ַ 
	addrServ.sin_family = AF_INET;
	addrServ.sin_port = htons(4999);
	addrServ.sin_addr.s_addr = INADDR_ANY;
	//���׽���
	retVal = bind(sServer, (LPSOCKADDR)&addrServ, sizeof(SOCKADDR_IN));
	if (retVal == SOCKET_ERROR)
	{
		retVal = WSAGetLastError();
	}

	//��ʼ���� 
	retVal = listen(sServer, 1);
	//���ܿͻ�������
	sockaddr_in addrClient;
	ZeroMemory(&addrClient, sizeof(sockaddr_in));
	int addrClientlen = sizeof(addrClient);
	sClient = accept(sServer, (sockaddr FAR*)&addrClient, &addrClientlen);
	//���տͻ�������
	retVal = recv(sClient, buf, BUF_SIZE, 0);

	MessageBoxA(NULL, buf, "�յ�", MB_OK);
	//�˳�
	closesocket(sServer);    //�ر��׽���
	closesocket(sClient);    //�ر��׽���
	WSACleanup();            //�ͷ��׽�����Դ;
}