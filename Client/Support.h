#pragma once
#include "Obj.h"
class CSupport :
	public CObj
{
public:
	CSupport();
	~CSupport();

	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize(void) override;
	virtual int Progress(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;
};

