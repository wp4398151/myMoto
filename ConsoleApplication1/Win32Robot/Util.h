#ifndef _UTIL_H_
#define _UTIL_H_
#include <Windows.h>
#include <WinSock2.h>

#define DOLOGA(str) OutputDebugStringA(str)

#define MYSOCKETCONTENTDATASIZE 1024*1024*4

class MySocketClientUtil
{
	inline static void InitializeSocket()
	{
		WSADATA wsd;
		WSAStartup(MAKEWORD(2, 2), &wsd);
	}
	inline static void UninitializeSocket()
	{
		WSACleanup();
	}
public:
	inline MySocketClientUtil(LPSTR ipBuf, int port)
	{
		m_socketHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		m_servAddr.sin_family = AF_INET;//地址家族
		m_servAddr.sin_addr.s_addr = inet_addr(ipBuf);//IP地址
		m_servAddr.sin_port = htons((short)port);//服务端口
	}

	inline BOOL Connect()
	{
		if (SOCKET_ERROR == connect(m_socketHost, (LPSOCKADDR)&m_servAddr, sizeof(m_servAddr)))
		{
			DOLOGA("连接失败");
			return FALSE;
		}
		return TRUE;
	}

	inline BOOL SendData(char* buf, int size)
	{
		if (SOCKET_ERROR == send(m_socketHost, buf, size, 0))
		{
			DOLOGA("发送数据失败");
			return FALSE;
		}
		return TRUE;
	}
	
	inline BOOL receive()
	{
		if (SOCKET_ERROR == recv(m_socketHost, m_contentBuf, MYSOCKETCONTENTDATASIZE, 0))
		{
			DOLOGA("接受数据失败");
			return FALSE;
		}
		return TRUE;
	}
	inline const LPSTR GetResult()
	{
		return m_contentBuf;
	}

	inline VOID Close()
	{
		closesocket(m_socketHost);
	}
	
private:
	INT m_port;
	SOCKET m_socketHost;
	SOCKADDR_IN m_servAddr;
	CHAR m_contentBuf[MYSOCKETCONTENTDATASIZE];	//用4M来存储数据
};

#endif _UTIL_H_