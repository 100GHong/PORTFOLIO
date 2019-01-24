#pragma once
#include "Include.h"
#include "Thread.h"

class CClient;
class CSocket;

class CClientThread : public CThread
{
private:
	CClient*			m_pClient;

public:
	virtual void ThreadRun() override;

public:
	CClientThread(CSocket* pSocket);
	virtual ~CClientThread();
};