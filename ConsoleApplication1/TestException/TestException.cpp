// TestException.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <WinSock2.h>
#include <Windows.h>
#include <WinBase.h>

void StartServer();
int _tmain(int argc, _TCHAR* argv[])
{
	StartServer();
	return 0;
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