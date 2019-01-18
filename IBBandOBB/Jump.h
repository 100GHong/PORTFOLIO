#pragma once
#include "Obj.h"
class CJump :
	public CObj
{
public:
	CJump();
	~CJump();

	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize(void) override;
	virtual int Progress(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;
};

