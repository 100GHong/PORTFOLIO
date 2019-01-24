#include "stdafx.h"
#include "ClientThread.h"
#include "Client.h"

void CClientThread::ThreadRun()
{

}

CClientThread::CClientThread(CSocket* pSocket)
	: m_pClient(new CClient(pSocket))
{
}

CClientThread::~CClientThread()
{
	Safe_Delete(m_pClient);
}
