#pragma once
#include "Obj.h"
class CIHole :
	public CObj
{
private:
	FRAME			m_tFrame;

public:
	CIHole();
	~CIHole();

	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize(void) override;
	virtual int Progress(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;
};

