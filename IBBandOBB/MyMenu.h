#pragma once
#include "Scene.h"
class CMyMenu :
	public CScene
{
public:
	CMyMenu();
	~CMyMenu();

	// CScene��(��) ���� ��ӵ�
	virtual HRESULT Initialize(void) override;
	virtual int Progress(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;
};

