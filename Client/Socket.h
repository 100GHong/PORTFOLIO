#pragma once
#include "Include.h"

class CSocket
{
public:
	int				Initailize();
	int				Connect(const  sockaddr& inAddr);
	int				Bind(const char* inAddr);
	int				Bind(const sockaddr& inAddr);
	int				Bind(ULONG inAddr);
	int				Listen(int	inBackLog = SOMAXCONN);
	CSocket*		Accept();
	int32_t			Send(const void* inData, size_t inLen);
	int32_t			Receive(void* inData, size_t inLen);

	void            SetIp(const char* szIP);
	void            SetPort(u_short usPort) { m_SockAddr.sin_port = htons(usPort); }
	void            SetSocketInfo(SOCKET socket, SOCKADDR_IN& sockAddr) { m_Socket = socket; m_SockAddr = sockAddr; }

	unsigned int    GetIp() const { return m_SockAddr.sin_addr.S_un.S_addr; }
	unsigned short	GetPort() const { return ntohs(m_SockAddr.sin_port); }
	SOCKET*			GetSocket() { return &m_Socket; }

	bool            IsConnected() const { return m_Socket != INVALID_SOCKET; }
private:
	SOCKET			m_Socket;
	sockaddr_in		m_SockAddr;

public:
	CSocket(SOCKET	inSocket) : m_Socket(inSocket) {}
	CSocket(SOCKET	inSocket, sockaddr_in inaddr) : m_Socket(inSocket), m_SockAddr(inaddr) {}
	virtual ~CSocket();
};