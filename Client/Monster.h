#pragma once
#include "Obj.h"
class CMonster :
	public CObj
{
public:
	CMonster();
	~CMonster();

	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize(void) override;
	virtual int Progress(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;
};

