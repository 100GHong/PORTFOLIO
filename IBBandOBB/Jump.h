#pragma once
#include "Obj.h"
class CJump :
	public CObj
{
public:
	CJump();
	~CJump();

	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize(void) override;
	virtual int Progress(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;
};

