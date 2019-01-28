#include "stdafx.h"
#include "NetworkMgr.h"
#include "CriticalSection.h"
#include "ListeningThread.h"
#include "ClientThread.h"
#include "Thread.h"


IMPLEMENT_SINGLETON(CNetworkMgr)

void CNetworkMgr::Initialize()
{
	int                  Ret;

	if ((Ret = WSAStartup(MAKEWORD(2, 2), &m_wsaData)) != 0)
	{
		printf("WSAStartup failed with error %d\n", Ret);
		return;
	}

	m_pListenThread = new ClisteningThread;

	m_pListenThread->BeginThread();
	//dynamic_cast<ClisteningThread*>(m_pListenThread)->ThreadRun();
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
	if (m_pOBBThread != nullptr)
		Safe_Delete(m_pOBBThread);
	if (m_pIBBThread != nullptr)
		Safe_Delete(m_pIBBThread);
	if (m_pListenThread != nullptr)
		Safe_Delete(m_pListenThread);
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
	{
		ReportError(_T("CNetworkMgr::NewConnectionUpdate::CClientThread"));
		return;
	}

	if (m_pIBBThread == nullptr)
	{
		m_pIBBThread = pNewThread;
		dynamic_cast<CClientThread*>(m_pIBBThread)->SetCharacterID(CHARACTERID::CHAR_IBB);
		dynamic_cast<CClientThread*>(m_pIBBThread)->SetBuffer(&m_tBuffer);
		dynamic_cast<CClientThread*>(m_pIBBThread)->BeginThread();
	}
	else if (m_pOBBThread == nullptr)
	{
		m_pOBBThread = pNewThread;
		dynamic_cast<CClientThread*>(m_pOBBThread)->SetCharacterID(CHARACTERID::CHAR_OBB);
		dynamic_cast<CClientThread*>(m_pOBBThread)->SetBuffer(&m_tBuffer);
		dynamic_cast<CClientThread*>(m_pOBBThread)->BeginThread();
	}
}

CNetworkMgr::CNetworkMgr()
{
}

CNetworkMgr::~CNetworkMgr()
{
	Release();
}