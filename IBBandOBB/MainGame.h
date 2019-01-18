#include "Include.h"
#include "Device.h"
#include "SceneMgr.h"

#pragma once
class CMainGame
{
private:
	CDevice*	m_pDevice = CDevice::GetInstance();
	CSceneMgr*  m_pSceneMgr = CSceneMgr::GetInstance();

	float m_fTime = 0.f;
	D3DXMATRIX		m_matTrans;
	TCHAR m_szFPS[MIN_STR] = L"";

public:
	HRESULT		Initialize(void);
	void		Progress(void);
	void		Render(void);
	void		Release(void);

public:
	CMainGame();
	~CMainGame();
};

