#include "stdafx.h"
#include "Thread.h"

bool CThread::BeginThread()
{
	if (m_hThreadEvent != NULL)
		return false;

	m_hQuitEvent = CreateEvent(NULL, false, false, NULL);
	if (NULL == m_hQuitEvent)
		return false;

	m_hThreadEvent = (HANDLE)_beginthreadex(NULL, 0, ThreadProc
		, (void*)this, 0, (unsigned*)&m_dwThreadId);

	if (NULL == m_hThreadEvent)
	{
		::CloseHandle(m_hQuitEvent);
		m_hQuitEvent = NULL;
		return false;
	}

	return true;
}

void CThread::EndThread(DWORD dwTimeout)
{
	if (NULL != m_hThreadEvent)
	{
		SetEvent(m_hQuitEvent);
		::WaitForSingleObject(m_hThreadEvent, dwTimeout);
		::CloseHandle(m_hThreadEvent);
		m_hThreadEvent = NULL;
		m_dwThreadId = 0;
	}
	if (m_hQuitEvent != NULL)
	{
		::CloseHandle(m_hQuitEvent);
		m_hQuitEvent = NULL;
	}
}

CThread::CThread()
	: m_hQuitEvent(NULL)
	, m_hThreadEvent(NULL)
{
}

CThread::~CThread()
{
	EndThread();
}
