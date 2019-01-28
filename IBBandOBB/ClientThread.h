#pragma once
#include "Include.h"
#include "Thread.h"

class CClient;
class CSocket;
class CBuffer;

class CClientThread : public CThread
{
private:
	CClient*			m_pClient;
	bool				m_bReceived;
	CBuffer*			m_pBuffer;

public:
	void				SetBuffer(CBuffer* pBuffer) { m_pBuffer = pBuffer; }
	void				SetCharacterID(CHARACTERID eID);
	virtual void		ThreadRun() override;

private:
	void				GetDatafromBuffer();

public:
	CClientThread(CSocket* pSocket);
	virtual ~CClientThread();
};