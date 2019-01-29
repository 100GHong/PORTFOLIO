#pragma once

#include "Include.h"
#include "CBuffer.h"
#include "Socket.h"
class CThread;

class CNetworkMgr
{
	DECLARE_SINGLETON(CNetworkMgr)
private:
	WSADATA              m_wsaData;
	CBuffer				 m_tBuffer;
	CSocket*			 m_pNewSocket = nullptr;
	CRITICAL_SECTION	 m_cs;

	// Threads
	CThread*			 m_pListenThread = nullptr;
	CThread*			 m_pIBBThread = nullptr;
	CThread*			 m_pOBBThread = nullptr;

public:
	void		Initialize();
	void		Update();
	void		Release();
	void		NewConnectionUpdate();
	bool		SetNewConnection(CSocket* pNewSocket);
	
	const CData	GetCData();

private:


private:
	CNetworkMgr();
	~CNetworkMgr();
};