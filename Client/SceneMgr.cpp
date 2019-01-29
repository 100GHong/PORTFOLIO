#include "stdafx.h"
#include "SceneMgr.h"
#include "Logo.h"
#include "MyMenu.h"
#include "Stage.h"
#include "Game.h"

IMPLEMENT_SINGLETON(CSceneMgr)

CSceneMgr::CSceneMgr()
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
	if (nullptr != m_pGame)
		Safe_Delete(m_pGame);
}

void CSceneMgr::SetScene(SCENEID eScene)
{

	if (nullptr != m_pScene)
		Release();

	switch (eScene)
	{
	case SC_LOGO:
		m_pScene = new CLogo;
		if (m_pGame == nullptr)
		{
			m_pGame = new CGame;
		}
		m_pScene->Initialize();
		break;
	case SC_MENU:
		m_pScene = new CMyMenu;
		m_pScene->Initialize();
		break;
	case SC_GAME:
		m_pScene = m_pGame;
		m_pGame = nullptr;
		break;
	}

}

void CSceneMgr::Progress(void)
{
	if (nullptr != m_pScene)
		m_pScene->Progress();
}

void CSceneMgr::Render(void)
{
	if (nullptr != m_pScene)
		m_pScene->Render();
}

void CSceneMgr::Release(void)
{
	if (nullptr != m_pScene)
		Safe_Delete(m_pScene);
}

