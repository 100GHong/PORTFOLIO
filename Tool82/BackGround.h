#pragma once

#include "Tool82View.h"

class CBackGround
{
private:
	CTool82View*		m_pMainView = nullptr;
	CDevice*			m_pDevice = nullptr;

	list<tRECT*>*		m_pRectlist = nullptr;
	list<tRECT*>*		m_pMap2list = nullptr;
	list<bOBJ*>*		m_pBObjlist = nullptr;
	list<SUP*>*			m_pSuplist = nullptr;
	list<MON*>*			m_pMonlist = nullptr;
	bOBJ*				m_pSampleImg = nullptr;
	SUP*				m_pSampleSup = nullptr;
	MON*				m_pSampleMon = nullptr;

private:
	void				RectRender(void);
	void				ObjRender(void);
	void				SupportRender(void);
	void				MonsterRender(void);
	void				SampleRender(void);
	void				SampleSupRender(void);
	void				SampleMonRender(void);

public:
	void	SetMainView(CTool82View* pMainView) { m_pMainView = pMainView; }

public:
	CBackGround();
	virtual ~CBackGround();

public:
	HRESULT		Initialize(void);
	void		Progress(void);
	void		Render(void);
	void		Release(void);
};

