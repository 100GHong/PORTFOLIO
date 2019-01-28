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
	void			setCharID(CHARACTERID eID) { m_eCharacter = eID; }
	SOCKET*			getSocket() { return m_pSocket->GetSocket(); }

public:
	CClient(CSocket* pSocket);
	virtual ~CClient();
};