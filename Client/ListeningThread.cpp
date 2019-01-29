#include "stdafx.h"
#include "ListeningThread.h"
#include "NetworkMgr.h"

void ClisteningThread::ThreadRun()
{
	if (m_sListeningSocket.Initailize() != NO_ERROR)
		return;

	if (m_sListeningSocket.Bind(INADDR_ANY) != NO_ERROR)
		return;

	if (m_sListeningSocket.Listen() != NO_ERROR)
		return;

	DWORD		ret = 0;
	CSocket*	pNewSocket;
	DWORD		dwElapsedTime;
	DWORD		dwPrevTime = ::GetTickCount();
	while (true)
	{
		ret = ::WaitForSingleObject(m_hQuitEvent, 0);
		if (ret == WAIT_OBJECT_0)
			break;

		pNewSocket = nullptr;
		pNewSocket = m_sListeningSocket.Accept();

		if (pNewSocket == nullptr)
			return;

		dwPrevTime = ::GetTickCount();
		while (true)
		{
			if (CNetworkMgr::GetInstance()->SetNewConnection(pNewSocket))
				break;
			else
			{
				dwElapsedTime = ::GetTickCount() - dwPrevTime;
				if (dwElapsedTime > 300000)
				{
					Safe_Delete(pNewSocket);
					ReportError(_T("ClisteningThread::SetNewConnection"));
					break;
				}
				Sleep(5);
			}
		}
	}
	
		
	
	//DWORD dwPrevTime = ::GetTickCount();

	//while (true) {
	//	const DWORD dwCurrTime = ::GetTickCount();
	//	const DWORD dwElapsedTime = dwCurrTime - dwPrevTime;
	//	dwPrevTime = dwCurrTime;

	//	const DWORD ret = ::WaitForSingleObject(m_hQuitEvent, 0);
	//	if (ret == WAIT_OBJECT_0)
	//		break;
	//	else if (ret == WAIT_TIMEOUT)
	//		Update(dwElapsedTime);
	//	else
	//		return;
	//}// while
}

void ClisteningThread::Update(DWORD dwElapsedTime)
{

}

ClisteningThread::ClisteningThread()
	: m_sListeningSocket(INVALID_SOCKET)
{
}

ClisteningThread::~ClisteningThread()
{
}
