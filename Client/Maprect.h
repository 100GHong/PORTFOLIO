#pragma once
#include "Obj.h"
class CMaprect :
	public CObj
{
public:
	CMaprect();
	~CMaprect();

	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize(void) override;
	virtual int Progress(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;
	void		Render(int iStage);
};

