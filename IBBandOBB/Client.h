#pragma once
#include "Include.h"
#include "Socket.h"

class CClient
{
private:
	CSocket*		m_pSocket;
	CHARACTERID		m_eCharacter;

public:
	CHARACTERID		getCharID() { return m_eCharacter;	}
	CSocket*		getSocket() { return m_pSocket; }

public:
	CClient(CSocket* pSocket);
	virtual ~CClient();
};