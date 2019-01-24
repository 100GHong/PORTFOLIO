#include "stdafx.h"
#include "CriticalSection.h"
#include "NetworkMgr.h"
#include "ListeningThread.h"
#include "ClientThread.h"

void CNetworkMgr::Initialize()
{
	int                  Ret;

	if ((Ret = WSAStartup(MAKEWORD(2, 2), &m_wsaData)) != 0)
	{
		printf("WSAStartup failed with error %d\n", Ret);
		return;
	}

	m_pListenThread = new ClisteningThread;

	dynamic_cast<ClisteningThread*>(m_pListenThread)->ThreadRun();
	//socketAccepter.BindAndListen(5150, CreateUser);
	//socketAccepter.BeginThread();

	//printf("Press any key to exit...\r\n");
	//_getch();

	//socketAccepter.EndThread(INFINITE);
}

void CNetworkMgr::Update()
{
	NewConnectionUpdate();
}

void CNetworkMgr::Release()
{
	WSACleanup();
}

bool CNetworkMgr::SetNewConnection(CSocket * pNewSocket)
{
	CSLOCK(m_cs)
	{
		if (m_pNewSocket == nullptr)
			return false;
		m_pNewSocket = pNewSocket;
	}
	return true;
}

void CNetworkMgr::NewConnectionUpdate()
{
	CClientThread* pNewThread = nullptr;
	CSLOCK(m_cs)
	{
		if (m_pNewSocket == nullptr)
			return;
		pNewThread = new CClientThread(m_pNewSocket);
		m_pNewSocket = nullptr;
	}
	if (pNewThread == nullptr)
		return;

}

CNetworkMgr::CNetworkMgr()
{
}

CNetworkMgr::~CNetworkMgr()
{
	Release();
}