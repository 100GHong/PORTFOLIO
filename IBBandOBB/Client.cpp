#include "stdafx.h"
#include "Client.h"

CClient::CClient(CSocket* pSocket)
	: m_pSocket(pSocket)
{
}

CClient::~CClient()
{
	Safe_Delete(m_pSocket);
}
