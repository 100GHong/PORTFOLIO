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
