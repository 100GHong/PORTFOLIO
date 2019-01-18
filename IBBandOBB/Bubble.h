#pragma once
#include "Obj.h"
class CBubble :
	public CObj
{
private:
	FRAME		m_tFrame;

public:
	void		SetPos(D3DXVECTOR3 vpos) { m_tInfo.vPos = vpos; }

public:
	CBubble();
	~CBubble();

	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize(void) override;
	virtual int Progress(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;
};

