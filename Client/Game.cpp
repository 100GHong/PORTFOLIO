#include "stdafx.h"
#include "Game.h"
#include "Lobby.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "ObjInclude.h"

void CGame::CameraProgress(void)
{

	// 배율 조정
	// 기본배율 1 배율에 거리 100당 0.1씩
	float fDistancex = fabsf(m_pIbb->GetInfo().vPos.x - m_pObb->GetInfo().vPos.x);
	float fDistancey = fabsf(m_pIbb->GetInfo().vPos.y - m_pObb->GetInfo().vPos.y);
	float fDistance = sqrtf(fDistancex*fDistancex + fDistancey * fDistancey);
	if (fDistance <= 300.f)	fDistance = 300.f;
	if (fDistance >= 700.f) fDistance = 700.f;
	g_vZoom = D3DXVECTOR3((1.f - ((fDistance - 300.f) / 1000.f)), (1.f - ((fDistance - 300.f) / 1000.f)), 0.f);

	// 카메라
	float		fAdjustX = ((WINCX / 2) - (WINCX / 2) / g_vZoom.x);
	float		fAdjustY = ((WINCY / 2) - (WINCY / 2) / g_vZoom.y);
	D3DXVECTOR2 vCenterPos = { fabsf((m_pIbb->GetInfo().vPos.x + m_pObb->GetInfo().vPos.x) / 2.f) - WINCX / 2 + fAdjustX, ((m_pIbb->GetInfo().vPos.y + (m_pObb->GetInfo().vPos.y)) / 2.f) - WINCY / 2 + fAdjustY };

	// 카메라 이동(보간)
	if (g_vScroll.x != -(vCenterPos.x))
		g_vScroll.x -= (g_vScroll.x + vCenterPos.x) / 5.f;
	if (g_vScroll.y != -(vCenterPos.y))
		g_vScroll.y -= (g_vScroll.y + vCenterPos.y) / 5.f;

	if (g_vScroll.y > 0)   // 위쪽
		g_vScroll.y = 0;
	else if (g_vScroll.y < (-600.f - fAdjustY))		// 아래쪽
		g_vScroll.y = -fAdjustY - 600.f;

}

CGame::CGame()
{

}

CGame::~CGame()
{
	Release();
}

HRESULT CGame::Initialize(void)
{
	if (m_pLobby == nullptr) m_pLobby = new CLobby;
	if (m_pStage1 == nullptr) m_pStage1 = new CStage1;
	if (m_pStage2 == nullptr) m_pStage2 = new CStage2;
	if (m_pStage3 == nullptr) m_pStage3 = new CStage3;
	m_pLobby->Initialize();
	m_pStage1->Initialize();
	m_pStage2->Initialize();
	m_pStage3->Initialize();

	m_pIbb = new CIbb;
	m_pObb = new CObb;
	m_pIbb->Initialize();
	m_pObb->Initialize();

	m_pLobby->SetPlayer(m_pIbb, m_pObb);
	m_pStage1->SetPlayer(m_pIbb, m_pObb);
	m_pStage2->SetPlayer(m_pIbb, m_pObb);
	m_pStage3->SetPlayer(m_pIbb, m_pObb);

	CSoundMgr::GetInst()->PlayBGM(L"bgm2.mp3", 1.f);
	m_vMouse = GetMouse();

	return S_OK;
}

int CGame::Progress(void)
{

	if (GetMouse() != m_vMouse)
	{
		m_vMouse = GetMouse();
		for (int i = 0; i < 4; ++i)
		{
			CBubble* ptemp = new CBubble;
			ptemp->SetPos(GetMouse());
			ptemp->Initialize();
			m_Effectlist.push_back(ptemp);
		}
	}

	// 이펙트
	list<CBubble*>::iterator iter = m_Effectlist.begin();
	list<CBubble*>::iterator iter_end = m_Effectlist.end();
	for (iter; iter != iter_end;)
	{
		int iResult = 0;
		iResult = (*iter)->Progress();
		if (1 == iResult)
		{
			Safe_Delete((*iter));
			iter = m_Effectlist.erase(iter);
		}
		else ++iter;
	}

	m_iCurStage = int(m_pIbb->GetInfo().vPos.x) / MAPX;
	int iObbStage = int(m_pObb->GetInfo().vPos.x) / MAPX;

	// 방향 설정
	static_cast<CIbb*>(m_pIbb)->CheckDirection();
	static_cast<CObb*>(m_pObb)->CheckDirection();

	// 스테이지 프로그레스 & 충돌체크
	switch (m_iCurStage)
	{
	case 0:		// 로비
		m_pLobby->Progress();
		break;
	case 1:
		m_pStage1->Progress();
		break;
	case 2:
		m_pStage2->Progress();
		break;
	case 3:
		m_pStage3->Progress();
		break;
	}
	if (m_iCurStage != iObbStage)
	{
		switch (iObbStage)
		{
		case 0:
			static_cast<CLobby*>(m_pLobby)->CollisionCheck();
			break;
		case 1:
			static_cast<CStage1*>(m_pStage1)->CollisionCheck();
			break;
		case 2:
			static_cast<CStage2*>(m_pStage2)->CollisionCheck();
			break;
		case 3:
			static_cast<CStage3*>(m_pStage3)->CollisionCheck();
			break;
		}
	}
	
	// 카메라 - 줌 & 스크롤
	CameraProgress();

	// 캐릭터 프로그레스
	m_pIbb->Progress();
	m_pObb->Progress();












	if (GetAsyncKeyState('1'))
	{
		m_pIbb->Initialize();
	}
	if (GetAsyncKeyState('2'))
	{
		m_pObb->Initialize();
	}
	if (GetAsyncKeyState('3') & 0x0001)
	{
		m_pIbb->AddXPos(MAPX);
		m_pObb->AddXPos(MAPX);
	}


	return 0;
}

void CGame::Render(void)
{
	float m_fCurStage = m_pIbb->GetInfo().vPos.x / float(MAPX);
	
	if( 0.66f >= m_fCurStage )
		m_pLobby->Render();
	else if (1.33 >= m_fCurStage)
	{
		m_pLobby->Render();
		m_pStage1->Render();
	}
	else if (1.66 >= m_fCurStage)
	{
		m_pStage1->Render();
	}
	else if (2.33 >= m_fCurStage)
	{
		m_pStage1->Render();
		m_pStage2->Render();
	}
	else if (2.66 >= m_fCurStage)
	{
		m_pStage2->Render();
	}
	else if (3.33 >= m_fCurStage)
	{
		m_pStage2->Render();
		m_pStage3->Render();
	}
	else
	{
		m_pStage3->Render();
	}
	m_pIbb->Render();
	m_pObb->Render();

	for (auto& effect : m_Effectlist)
		effect->Render();
}

void CGame::Release(void)
{
	for (auto& effect : m_Effectlist)
		Safe_Delete(effect);
	Safe_Delete(m_pIbb);
	Safe_Delete(m_pObb);
	Safe_Delete(m_pLobby);
	Safe_Delete(m_pStage1);
	Safe_Delete(m_pStage2);
	Safe_Delete(m_pStage3);
}
