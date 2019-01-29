#include "stdafx.h"
#include "MainGame.h"

D3DXVECTOR3		g_vZoom;
D3DXVECTOR3		g_vScroll;
int				g_iFPS;

HRESULT CMainGame::Initialize(void)
{
	srand(unsigned(time(NULL)));
	if (FAILED(m_pDevice->InitDevice()))
	{
		ERR_MSG(L"MainGame Init Failed");
		return E_FAIL;
	}

	CTimeMgr::GetInstance()->InitTime();
	m_pSceneMgr->SetScene(SC_LOGO);

	g_vZoom = { 1.f, 1.f, 0.f };
	g_vScroll = { 0.f, -300.f, 0.f };

	CSoundMgr::GetInst()->LoadSoundFile();
	m_pNetworkMgr->Initialize();

	ShowCursor(false);

	return S_OK;
}

void CMainGame::Progress(void)
{
	CSoundMgr::GetInst()->Update();
	CTimeMgr::GetInstance()->SetTime();
	m_pNetworkMgr->Update();
	m_pSceneMgr->Progress();


	D3DXMatrixTranslation(&m_matTrans, 600.f, 50.f, 0.f);
}

void CMainGame::Render(void)
{
	++g_iFPS;

	m_fTime += GET_TIME;

	//if (m_fTime > 1.f)
	//{
	//	m_fTime = 0.f;
	//	wsprintf(m_szFPS, L"FPS : %d", g_iFPS);
	//	g_iFPS = 0;
	//}
	m_pDevice->GetDevice()->Clear(0,
		NULL,
		D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_ARGB(0, 0, 0, 0),
		1.f,  // z버퍼의 초기화 값
		0);   // 스텐실 버퍼의 초기화 값

	m_pDevice->Render_Begin();

	m_pSceneMgr->Render();

	m_pDevice->GetSprite()->SetTransform(&m_matTrans);
	m_pDevice->GetFont()->DrawTextW(m_pDevice->GetSprite(),
		m_szFPS,
		lstrlen(m_szFPS),
		NULL,
		NULL,
		D3DCOLOR_ARGB(255, 255, 0, 0));

	m_pDevice->Render_End();

	m_pDevice->GetDevice()->Present(NULL, NULL, NULL, NULL);
}

void CMainGame::Release(void)
{
	CKeyMgr::GetInstance()->DestroyInstance();
	CTimeMgr::GetInstance()->DestroyInstance();
	CTextureMgr::GetInstance()->DestroyInstance();
	CSoundMgr::GetInst()->DestroyInst();
	m_pSceneMgr->DestroyInstance();
	m_pDevice->DestroyInstance();

	m_pNetworkMgr->DestroyInstance();
}

CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
	Release();
}
