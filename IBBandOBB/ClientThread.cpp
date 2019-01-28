#include "stdafx.h"
#include "ClientThread.h"
#include "Client.h"
#include "CBuffer.h"

void CClientThread::SetCharacterID(CHARACTERID eID)
{
	m_pClient->setCharID(eID);
}

void CClientThread::ThreadRun()
{
	FD_SET	ReadSet;
	FD_SET	WriteSet;
	SOCKET	Socket = *(m_pClient->getSocket());
	int		iTotal = 0;
	char	recvBuf[4096];
	ZeroMemory(recvBuf, sizeof(recvBuf));

	TIMEVAL Waittime;
	Waittime.tv_usec = 1000;

	while (true)
	{
		if (m_bReceived)
		{
			FD_ZERO(&WriteSet);
			FD_SET(Socket, &WriteSet);
			if ((iTotal = select(0, 0, &WriteSet, NULL, &Waittime)) == SOCKET_ERROR)
			{
				ReportError(_T("CClientThread::select"));
				return;
			}
			else if (iTotal > 0)
			{
				SData buf = m_pBuffer->GetSData();
				send(Socket, reinterpret_cast<const char*>(&buf), sizeof(SData), 0);
			}

			m_bReceived = !m_bReceived;
		}
		else
		{
			FD_ZERO(&ReadSet);
			FD_SET(Socket, &ReadSet);

			if ((iTotal = select(0, &ReadSet, 0, NULL, &Waittime)) == SOCKET_ERROR)
			{
				ReportError(_T("CClientThread::select"));
				return;
			}
			else if (iTotal > 0)
			{
				CData buf;
				int ibufsize = recv(Socket, recvBuf, sizeof(recvBuf), 0);
				if (ibufsize >= sizeof(CData))
				{
					ibufsize = ibufsize - sizeof(CData);
					memcpy(&buf, &(recvBuf[ibufsize]), sizeof(CData));
					m_pBuffer->SetCData(buf, m_pClient->getCharID());
				}
			}

			ZeroMemory(recvBuf, sizeof(recvBuf));
			m_bReceived = !m_bReceived;
		}
		
	}
}

void CClientThread::GetDatafromBuffer()
{

}

CClientThread::CClientThread(CSocket* pSocket)
	: m_pClient(new CClient(pSocket)),
	  m_bReceived(false)
{
}

CClientThread::~CClientThread()
{
	Safe_Delete(m_pClient);
}
