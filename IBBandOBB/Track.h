#pragma once
#include "Obj.h"
class CTrack :
	public CObj
{
public:
	CTrack();
	~CTrack();

	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize(void) override;
	virtual int Progress(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;
};

