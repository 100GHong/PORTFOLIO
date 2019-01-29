#pragma once
#include "stdafx.h"

class CThread
{
protected:
	HANDLE				m_hQuitEvent;
	HANDLE				m_hThreadEvent;
	DWORD				m_dwThreadId = 0;

public:
	virtual bool		BeginThread();
	virtual	void		EndThread(DWORD dwTimeout = 0);
	virtual void        ThreadRun() PURE;

	DWORD               GetThreadId() const { return m_dwThreadId; }
protected:
	static unsigned int WINAPI
		ThreadProc(LPVOID pvParam)
	{
		CThread* pThread = reinterpret_cast<CThread*>(pvParam);
		if (pThread != nullptr)
			pThread->ThreadRun();
		else
			return -1;
		return S_OK;
	}

public:
	CThread();
	virtual ~CThread();
};