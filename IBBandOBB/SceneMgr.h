#pragma once

#include "Include.h"

class CScene;
class CSceneMgr
{
	DECLARE_SINGLETON(CSceneMgr)
private:
	CScene*			m_pScene = nullptr;
	CScene*			m_pGame = nullptr;

public:
	CScene*	GetGame(void) { return m_pGame; }

public:
	void	SetScene(SCENEID eScene);
	void	Progress(void);
	void	Render(void);
	void	Release(void);

private:
	CSceneMgr();
	~CSceneMgr();
};

