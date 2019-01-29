#include "stdafx.h"
#include "CriticalSection.h"
#include "CBuffer.h"

SData CBuffer::GetSData()
{
	SData		ret;
	CSLOCK(m_csSData)
	{
		memcpy(&ret, &m_sData, sizeof(SData));
	}
	
	return ret;
}

void CBuffer::SetCData(CData data, CHARACTERID eId)
{
	switch (eId)
	{
	case CHAR_IBB:
		CSLOCK(m_csSData)
		{
			memcpy(&m_cIBB, &data, sizeof(CData));
		}
		break;
	case CHAR_OBB:
		CSLOCK(m_csSData)
		{
			memcpy(&m_cOBB, &data, sizeof(CData));
		}
		break;
	case CHAR_END:
		break;
	default:
		break;
	}
}

void CBuffer::SetSData()
{
}


CBuffer::CBuffer()
{
	ZeroMemory(&m_sData, sizeof(m_sData));
	ZeroMemory(&m_cIBB, sizeof(m_cIBB));
	ZeroMemory(&m_cOBB, sizeof(m_cOBB));

}

CBuffer::~CBuffer()
{
}

CData CBuffer::GetCData(CHARACTERID eId)
{
	CData		data;
	
	switch (eId)
	{
	case CHAR_IBB:
		CSLOCK(m_csIBBData)
		{
			memcpy(&data, &m_cIBB,sizeof(CData));
		}
		break;
	case CHAR_OBB:
		CSLOCK(m_csOBBData)
		{
			memcpy(&data, &m_cOBB, sizeof(CData));
		}
		break;
	case CHAR_END:
		break;
	default:
		break;
	}
	
	return data;
}
