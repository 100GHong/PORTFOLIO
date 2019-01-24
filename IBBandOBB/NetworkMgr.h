#pragma once

#include "Include.h"
#include "CBuffer.h"
#include "Thread.h"
#include "Socket.h"

class CNetworkMgr
{
	DECLARE_SINGLETON(CNetworkMgr)
private:
	WSADATA              m_wsaData;
	CBuffer				 m_tBuffer;
	CThread*			 m_pListenThread = nullptr;
	CThread*			 m_pIBBThread = nullptr;
	CThread*			 m_pOBBThread = nullptr;
	CSocket*			 m_pNewSocket = nullptr;
	CRITICAL_SECTION	 m_cs;

public:
	void		Initialize();
	void		Update();
	void		Release();
	void		NewConnectionUpdate();
	bool		SetNewConnection(CSocket* pNewSocket);

private:


private:
	CNetworkMgr();
	~CNetworkMgr();
};