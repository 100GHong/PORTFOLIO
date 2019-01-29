#pragma once
#include "stdafx.h"

class CCriticalSection : public CRITICAL_SECTION
{
public:
	CCriticalSection() { InitializeCriticalSection(this); }
	~CCriticalSection() { DeleteCriticalSection(this); }
};


class CCriticalSectionLock
{
public:
	CCriticalSectionLock(const CRITICAL_SECTION& cs) : m_pcs(&cs)
	{
		EnterCriticalSection((LPCRITICAL_SECTION)m_pcs);
	}

	~CCriticalSectionLock()
	{
		if (m_pcs != nullptr)
			LeaveCriticalSection((LPCRITICAL_SECTION)m_pcs);
	}
	explicit            operator bool() { return true; }
protected:
	const CRITICAL_SECTION*				m_pcs;
};

#define CSLOCK( cs_ )   if( CCriticalSectionLock CONCATENATE( lock_, __LINE__ ) = cs_ )