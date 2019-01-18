#pragma once
#include "Scene.h"
class CLogo :
	public CScene
{
private:
	HANDLE				m_hThread;
	CRITICAL_SECTION	m_Crt;

public:
	void				LoadData(void);
	CRITICAL_SECTION	GetCrt(void) { return m_Crt; }

public:
	CLogo();
	~CLogo();

public:
	// CScene��(��) ���� ��ӵ�
	virtual HRESULT Initialize(void) override;
	virtual int Progress(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;
};

