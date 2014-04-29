// TestException.cpp : 定义控制台应用程序的入口点。
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