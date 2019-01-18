#pragma once

#include "Include.h"
#include "Obj.h"

class CScene
{
protected:
	list<CObj*>				m_Objlist;

public:
	virtual HRESULT		Initialize(void)PURE;
	virtual int			Progress(void)PURE;
	virtual void		Render(void)PURE;
	virtual void		Release(void)PURE;

public:
	CScene();
	virtual ~CScene();
};

