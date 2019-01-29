#pragma once
#include "Include.h"

class CBuffer
{
private:						// Server to Client
	CRITICAL_SECTION	m_csSData;
	SData				m_sData;
								// Client to Server
	CRITICAL_SECTION	m_csIBBData;
	CData				m_cIBB;
	CRITICAL_SECTION	m_csOBBData;
	CData				m_cOBB;

public:
	SData				GetSData();
	void				SetSData();
	CData				GetCData(CHARACTERID eId);
	void				SetCData(CData data, CHARACTERID eId);

public:
	CBuffer();
	~CBuffer();
};