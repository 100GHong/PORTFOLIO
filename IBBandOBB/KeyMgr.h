#pragma once

#include "Include.h"

class CKeyMgr
{
DECLARE_SINGLETON(CKeyMgr)
private:
	DWORD		m_dwKey = 0;
	DWORD		m_dwKeyPressed = 0;
	DWORD		m_dwKeyDown = 0;

public:
	void		KeyCheck(void);
	bool		KeyPressed(DWORD _dwKey);
	bool		KeyDown(DWORD _dwKey);
	bool		KeyCombine(DWORD _dwFirstKey, DWORD _dwSecondKey);

	DWORD		GetKey(void) const { return m_dwKey; }

private:
	CKeyMgr();
	~CKeyMgr();
};

