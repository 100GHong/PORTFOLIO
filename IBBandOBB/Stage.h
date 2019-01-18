#pragma once

#include "Include.h"

class CObj;

class CStage
{
protected:
	CObj*				m_pIbb = nullptr;
	CObj*				m_pObb = nullptr;
	list<CObj*>			m_Objlist[OBJ_END];

public:
	void		SetPlayer(CObj* pibb, CObj* pobb) { m_pIbb = pibb; m_pObb = pobb; }

public:
	CStage();
	virtual ~CStage();

public:
	virtual HRESULT		Initialize(void)PURE;
	virtual int			Progress(void)PURE;
	virtual void		Render(void)PURE;
	virtual void		Release(void)PURE;
};