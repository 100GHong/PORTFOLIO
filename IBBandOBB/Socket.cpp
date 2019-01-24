#include "stdafx.h"
#include "Socket.h"

int CSocket::Initailize()
{
	m_Socket = socket(AF_INET, SOCK_STREAM, 0);

	return NO_ERROR;
}

int CSocket::Connect(const sockaddr & inAddr)
{
	int		iError = connect(m_Socket, &inAddr, sizeof(sockaddr));
	if (ERROR_CHECK(iError))
	{
		ReportError(_T("Socket::Connet"));
		return WSAGetLastError();
	}
	return NO_ERROR;
}

int CSocket::Bind(const char * inAddr)
{
	sockaddr_in	Addr;
	Addr.sin_family = AF_INET;
	Addr.sin_port = htons(GAME_PORT_FIRST);
	inet_pton(AF_INET, inAddr, &Addr.sin_addr);

	sockaddr	addr;
	memcpy(&addr, &Addr, sizeof(sockaddr));
	return Bind(addr);
}

int CSocket::Bind(const sockaddr & inAddr)
{
	int		iError = ::bind(m_Socket, &inAddr, sizeof(sockaddr));

	if (ERROR_CHECK(iError))
	{
		ReportError(_T("Socket::Bind"));
		return WSAGetLastError();
	}
	return NO_ERROR;
}

int CSocket::Listen(int inBackLog)
{
	int	iError = listen(m_Socket, inBackLog);
	if (ERROR_CHECK(iError))
	{
		ReportError(_T("Socket::Listen"));
		return WSAGetLastError();
	}
	return NO_ERROR;
}

CSocket * CSocket::Accept()
{
	sockaddr_in inAddr;
	socklen_t	length = sizeof(sockaddr);
	SOCKET		newSocket = accept(m_Socket, (SOCKADDR*)&inAddr, &length);

	if (newSocket == INVALID_SOCKET)
		return new CSocket(newSocket, inAddr);
	else
	{
		ReportError(_T("Socket::Accept"));
		return nullptr;
	}
}

int32_t CSocket::Send(const void * inData, size_t inLen)
{
	int		iSentCount = send(m_Socket, static_cast<const char*>(inData), inLen, 0);
	if (iSentCount < 0)
	{
		ReportError(_T("Socket::Send"));
		return WSAGetLastError();
	}
	return iSentCount;
}

int32_t CSocket::Receive(void * inData, size_t inLen)
{
	int		iReceivedCount = recv(m_Socket, static_cast<char*>(inData), inLen, 0);
	if (iReceivedCount < 0)
	{
		ReportError(_T("Socket::Receive"));
		return WSAGetLastError();
	}
	return iReceivedCount;
}

void CSocket::SetIp(const char * szIP)
{
	m_SockAddr.sin_addr.s_addr = inet_pton(AF_INET, szIP, nullptr);
}

CSocket::~CSocket()
{
	closesocket(m_Socket);
}