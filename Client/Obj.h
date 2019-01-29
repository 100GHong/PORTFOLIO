#pragma once

#include "Include.h"
#include "Device.h"

class CObj
{
protected:
	INFO				m_tInfo;
	CDevice*			m_pDevice = CDevice::GetInstance();
	const TEXINFO*		pTexture;

public:
	INFO&			GetInfo(void) { return m_tInfo; }
	RECT			GetRect(void)
	{
		RECT rc = 
		{
			LONG(m_tInfo.vPos.x - m_tInfo.vSize.x /2.f),
			LONG(m_tInfo.vPos.y - m_tInfo.vSize.y /2.f),
			LONG(m_tInfo.vPos.x + m_tInfo.vSize.x /2.f),
			LONG(m_tInfo.vPos.y + m_tInfo.vSize.y /2.f),
		};
		return rc;
	}
	void			AddXPos(float _fX) { m_tInfo.vPos.x += _fX; }

public:
	virtual HRESULT		Initialize(void)PURE;
	virtual int			Progress(void)PURE;
	virtual void		Render(void)PURE;
	virtual void		Release(void)PURE;

public:
	CObj();
	virtual ~CObj();
};

