#pragma once
#include "Include.h"

class CBuffer
{
private:						// Server to Client
	SData		m_sIBB;
	SData		m_sOBB;
								// Client to Server
	CData		m_cIBB;
	CData		m_cOBB;
};