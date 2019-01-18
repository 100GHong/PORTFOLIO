#pragma once
#include "Obj.h"

class CBackobj :
	public CObj
{
	int		m_arRGB[3];

private:
	void	Draw(float& _fX, float& _fY, int& _iColor);

public:
	CBackobj();
	~CBackobj();

	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize(void) override;
	virtual int Progress(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;
};

