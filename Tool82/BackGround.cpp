#include "stdafx.h"
#include "BackGround.h"
#include "TextureMgr.h"
#include "MainFrm.h"

void CBackGround::RectRender(void)
{
	const TEXINFO*		pTexture;
	D3DXMATRIX			matWorld, matScale, matTrans, matRotZ;
	D3DXMatrixIdentity(&matWorld);

	RECT rc = {
		0 + m_pMainView->GetScrollPos(0),
		0 + m_pMainView->GetScrollPos(1),
		WINCX + m_pMainView->GetScrollPos(0),
		WINCY + m_pMainView->GetScrollPos(1)
	};

	pTexture = CTextureMgr::GetInstance()->GetTexture(L"MAP", L"Track", 0);
	for (auto& track : m_pRectlist[RT_TRACK])
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixTranslation(&matTrans, track->vPos.x - m_pMainView->GetScrollPos(0), track->vPos.y - m_pMainView->GetScrollPos(1), 0.f);
		D3DXMatrixScaling(&matScale, g_vZoom.x, g_vZoom.y, 0.f);
		matWorld = matTrans * matScale;
		m_pDevice->GetSprite()->SetTransform(&matWorld);
		rc = { 0, 0, LONG(track->vSize.x), LONG(track->vSize.y) };
		m_pDevice->GetSprite()->Draw(
			pTexture->pTexture,
			&rc,
			&D3DXVECTOR3(track->vSize.x / 2.f, track->vSize.y / 2.f, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	pTexture = CTextureMgr::GetInstance()->GetTexture(L"MAP", L"Hole", 0);
	for (auto& hole : m_pRectlist[RT_HOLE])
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixTranslation(&matTrans, hole->vPos.x - m_pMainView->GetScrollPos(0), hole->vPos.y - m_pMainView->GetScrollPos(1), 0.f);
		D3DXMatrixScaling(&matScale, g_vZoom.x, g_vZoom.y, 0.f);
		matWorld = matTrans * matScale;
		m_pDevice->GetSprite()->SetTransform(&matWorld);
		rc = { 0, 0, LONG(hole->vSize.x), LONG(hole->vSize.y) };
		m_pDevice->GetSprite()->Draw(
			pTexture->pTexture,
			&rc,
			&D3DXVECTOR3(hole->vSize.x / 2.f, hole->vSize.y / 2.f, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	pTexture = CTextureMgr::GetInstance()->GetTexture(L"MAP", L"Hole", 1);
	for (auto& hole : m_pRectlist[RT_IHOLE])
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixTranslation(&matTrans, hole->vPos.x - m_pMainView->GetScrollPos(0), hole->vPos.y - m_pMainView->GetScrollPos(1), 0.f);
		D3DXMatrixScaling(&matScale, g_vZoom.x, g_vZoom.y, 0.f);
		matWorld = matTrans * matScale;
		m_pDevice->GetSprite()->SetTransform(&matWorld);
		rc = { 0, 0, LONG(hole->vSize.x), LONG(hole->vSize.y) };
		m_pDevice->GetSprite()->Draw(
			pTexture->pTexture,
			&rc,
			&D3DXVECTOR3(hole->vSize.x / 2.f, hole->vSize.y / 2.f, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	pTexture = CTextureMgr::GetInstance()->GetTexture(L"MAP", L"Hole", 2);
	for (auto& hole : m_pRectlist[RT_OHOLE])
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixTranslation(&matTrans, hole->vPos.x - m_pMainView->GetScrollPos(0), hole->vPos.y - m_pMainView->GetScrollPos(1), 0.f);
		D3DXMatrixScaling(&matScale, g_vZoom.x, g_vZoom.y, 0.f);
		matWorld = matTrans * matScale;
		m_pDevice->GetSprite()->SetTransform(&matWorld);
		rc = { 0, 0, LONG(hole->vSize.x), LONG(hole->vSize.y) };
		m_pDevice->GetSprite()->Draw(
			pTexture->pTexture,
			&rc,
			&D3DXVECTOR3(hole->vSize.x / 2.f, hole->vSize.y / 2.f, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	pTexture = CTextureMgr::GetInstance()->GetTexture(L"MAP", L"Track", 1);
	for (auto& hole : m_pRectlist[RT_JUMP])
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixTranslation(&matTrans, hole->vPos.x - m_pMainView->GetScrollPos(0), hole->vPos.y - m_pMainView->GetScrollPos(1), 0.f);
		D3DXMatrixScaling(&matScale, g_vZoom.x, g_vZoom.y, 0.f);
		matWorld = matTrans * matScale;
		m_pDevice->GetSprite()->SetTransform(&matWorld);
		rc = { 0, 0, LONG(hole->vSize.x), LONG(hole->vSize.y) };
		m_pDevice->GetSprite()->Draw(
			pTexture->pTexture,
			&rc,
			&D3DXVECTOR3(hole->vSize.x / 2.f, hole->vSize.y / 2.f, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixTranslation(&matTrans, 10.f, float(MAPY/2) - m_pMainView->GetScrollPos(1), 0.f);
	D3DXMatrixScaling(&matScale, g_vZoom.x, g_vZoom.y, 0.f);
	matWorld = matTrans * matScale;
	m_pDevice->GetSprite()->SetTransform(&matWorld);
	rc = { 0, 0, 10, 10 };
	m_pDevice->GetSprite()->Draw(
		pTexture->pTexture,
		&rc,
		&D3DXVECTOR3(5.f, 5.f, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixTranslation(&matTrans, float(MAPX/2) - m_pMainView->GetScrollPos(0), float(MAPY / 2) - m_pMainView->GetScrollPos(1), 0.f);
	D3DXMatrixScaling(&matScale, g_vZoom.x, g_vZoom.y, 0.f);
	matWorld = matTrans * matScale;
	m_pDevice->GetSprite()->SetTransform(&matWorld);
	rc = { 0, 0, 10, 10 };
	m_pDevice->GetSprite()->Draw(
		pTexture->pTexture,
		&rc,
		&D3DXVECTOR3(5.f, 5.f, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CBackGround::ObjRender(void)
{
	const TEXINFO*		pTexture;
	D3DXMATRIX		matTrans, matWorld, matScale;

	for (auto& bobj : *m_pBObjlist)
	{
		if (bobj->vScale.y < 0.f)
		{
			m_pDevice->GetSprite()->End();
			m_pDevice->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
			m_pDevice->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			m_pDevice->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTALPHA);
			m_pDevice->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			pTexture = CTextureMgr::GetInstance()->GetTexture(L"MAP", L"Fixed", bobj->iDrawID);
			D3DXMatrixIdentity(&matWorld);
			D3DXMatrixTranslation(&matTrans, bobj->vPos.x - m_pMainView->GetScrollPos(0), bobj->vPos.y - m_pMainView->GetScrollPos(1), 0.f);
			D3DXMatrixScaling(&matScale, bobj->vScale.x, bobj->vScale.y, 0.f);
			matWorld = matScale * matTrans;

			D3DXMatrixScaling(&matScale, g_vZoom.x, g_vZoom.y, 0.f);
			matWorld = matWorld * matScale;

			m_pDevice->GetSprite()->SetTransform(&matWorld);

			float	fX = float(pTexture->tImgInfo.Width) / 2.f;
			float	fY = float(pTexture->tImgInfo.Height) / 2.f;

			int iColor = m_pMainView->GetScrollPos(0);
			iColor = (iColor % 1000) / 10;
			m_pDevice->GetSprite()->Draw(pTexture->pTexture,
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 55 + iColor * 2, iColor, 255 - iColor));

			m_pDevice->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
			m_pDevice->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

			m_pDevice->GetSprite()->End();
			m_pDevice->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
			D3DXMatrixIdentity(&matWorld);
			m_pDevice->GetSprite()->SetTransform(&matWorld);
		}
	}
	for (auto& bobj : *m_pBObjlist)
	{
		if (bobj->vScale.y >= 0.f)
		{
			m_pDevice->GetSprite()->End();
			m_pDevice->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
			m_pDevice->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			m_pDevice->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVDESTALPHA);
			m_pDevice->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			pTexture = CTextureMgr::GetInstance()->GetTexture(L"MAP", L"Fixed", bobj->iDrawID);
			D3DXMatrixIdentity(&matWorld);
			D3DXMatrixTranslation(&matTrans, bobj->vPos.x - m_pMainView->GetScrollPos(0), bobj->vPos.y - m_pMainView->GetScrollPos(1), 0.f);
			D3DXMatrixScaling(&matScale, bobj->vScale.x, bobj->vScale.y, 0.f);
			matWorld = matScale * matTrans;

			D3DXMatrixScaling(&matScale, g_vZoom.x, g_vZoom.y, 0.f);
			matWorld = matWorld * matScale;

			m_pDevice->GetSprite()->SetTransform(&matWorld);

			float	fX = float(pTexture->tImgInfo.Width) / 2.f;
			float	fY = float(pTexture->tImgInfo.Height) / 2.f;

			int iColor = m_pMainView->GetScrollPos(0);
			iColor = (iColor % 1000) / 10;
			m_pDevice->GetSprite()->Draw(pTexture->pTexture,
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255 - iColor, iColor, 55 + iColor * 2));

			m_pDevice->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
			m_pDevice->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

			m_pDevice->GetSprite()->End();
			m_pDevice->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

			D3DXMatrixIdentity(&matWorld);
			m_pDevice->GetSprite()->SetTransform(&matWorld);
		}

	}
}

#pragma region dk
void CBackGround::SampleRender(void)
{
	D3DXMATRIX		matTrans, matWorld, matScale;
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(L"MAP", L"Fixed", m_pSampleImg->iDrawID);

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixTranslation(&matTrans, m_pSampleImg->vPos.x, m_pSampleImg->vPos.y, 0.f);
	D3DXMatrixScaling(&matScale, m_pSampleImg->vScale.x, m_pSampleImg->vScale.y, 0.f);
	matWorld = matScale * matTrans;

	D3DXMatrixScaling(&matScale, g_vZoom.x, g_vZoom.y, 0.f);
	matWorld = matWorld * matScale;

	m_pDevice->GetSprite()->SetTransform(&matWorld);

	float	fX = float(pTexture->tImgInfo.Width) / 2.f;
	float	fY = float(pTexture->tImgInfo.Height) / 2.f;

	m_pDevice->GetSprite()->Draw(pTexture->pTexture,
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(155, 255, 255, 255));


	RECT rc = { 0,0,LONG(10 * g_vZoom.x), LONG(10 * g_vZoom.y) };

	pTexture = CTextureMgr::GetInstance()->GetTexture(L"MAP", L"Track", 0);
	m_pDevice->GetSprite()->SetTransform(&matWorld);
	m_pDevice->GetSprite()->Draw(pTexture->pTexture,
		&rc,
		NULL,
		NULL,
		D3DCOLOR_ARGB(155, 255, 255, 255));

	m_pDevice->GetSprite()->SetTransform(&matWorld);

}

void CBackGround::SupportRender(void)
{
	const TEXINFO*		pTexture;
	D3DXMATRIX			matTrans, matWorld, matScale;

	for (size_t i = 0; i < SP_END; ++i)
	{
		for (auto& sup : m_pSuplist[i])
		{
			pTexture = CTextureMgr::GetInstance()->GetTexture(L"MONSTER", L"Support", sup->eType);
			D3DXMatrixIdentity(&matWorld);
			D3DXMatrixTranslation(&matTrans, sup->vPos.x - m_pMainView->GetScrollPos(0), sup->vPos.y - m_pMainView->GetScrollPos(1), 0.f);
			D3DXMatrixScaling(&matScale, sup->vScale.x, sup->vScale.y, 0.f);
			matWorld = matScale * matTrans;

			D3DXMatrixScaling(&matScale, g_vZoom.x, g_vZoom.y, 0.f);
			matWorld = matWorld * matScale;

			m_pDevice->GetSprite()->SetTransform(&matWorld);

			float	fX = float(pTexture->tImgInfo.Width) / 2.f;
			float	fY = float(pTexture->tImgInfo.Height) / 2.f;
			m_pDevice->GetSprite()->Draw(pTexture->pTexture,
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}

void CBackGround::MonsterRender(void)
{
	const TEXINFO*		pTexture = nullptr;
	D3DXMATRIX			matTrans, matWorld, matScale;

	for (auto& mon : *m_pMonlist)
	{
		// º»Ã¼(½ÃÀÛÁ¡)
		pTexture = CTextureMgr::GetInstance()->GetTexture(L"MONSTER", L"Enemy", mon->eType);
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixTranslation(&matTrans, mon->ptStart.x - m_pMainView->GetScrollPos(0), mon->ptStart.y - m_pMainView->GetScrollPos(1), 0.f);
		D3DXMatrixScaling(&matScale, mon->vScale.x, mon->vScale.y, 0.f);
		matWorld = matScale * matTrans;

		D3DXMatrixScaling(&matScale, g_vZoom.x, g_vZoom.y, 0.f);
		matWorld = matWorld * matScale;

		m_pDevice->GetSprite()->SetTransform(&matWorld);

		float	fX = float(pTexture->tImgInfo.Width) / 2.f;
		float	fY = float(pTexture->tImgInfo.Height) / 2.f;
		m_pDevice->GetSprite()->Draw(pTexture->pTexture,
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));

		// ±×¸²ÀÚ(½ÃÀÛÁ¡)
		pTexture = CTextureMgr::GetInstance()->GetTexture(L"MONSTER", L"Shadow", mon->eType);
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixTranslation(&matTrans, mon->ptStart.x - m_pMainView->GetScrollPos(0), mon->ptStart.y - m_pMainView->GetScrollPos(1) + TRACKCXY + 2 * fY, 0.f);
		D3DXMatrixScaling(&matScale, mon->vScale.x, mon->vScale.y, 0.f);
		matWorld = matScale * matTrans;
		D3DXMatrixScaling(&matScale, g_vZoom.x, g_vZoom.y, 0.f);
		matWorld = matWorld * matScale;
		m_pDevice->GetSprite()->SetTransform(&matWorld);
		fX = float(pTexture->tImgInfo.Width) / 2.f;
		fY = float(pTexture->tImgInfo.Height) / 2.f;
		m_pDevice->GetSprite()->Draw(pTexture->pTexture,
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CBackGround::SampleSupRender(void)
{
	D3DXMATRIX		matTrans, matWorld, matScale;
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(L"MONSTER", L"Support", m_pSampleSup->eType);

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixTranslation(&matTrans, m_pSampleSup->vPos.x, m_pSampleSup->vPos.y, 0.f);
	D3DXMatrixScaling(&matScale, m_pSampleSup->vScale.x, m_pSampleSup->vScale.y, 0.f);
	matWorld = matScale * matTrans;

	D3DXMatrixScaling(&matScale, g_vZoom.x, g_vZoom.y, 0.f);
	matWorld = matWorld * matScale;

	m_pDevice->GetSprite()->SetTransform(&matWorld);

	float	fX = float(pTexture->tImgInfo.Width) / 2.f;
	float	fY = float(pTexture->tImgInfo.Height) / 2.f;

	m_pDevice->GetSprite()->Draw(pTexture->pTexture,
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(155, 255, 255, 255));

	RECT rc = { 0,0,LONG(10 * g_vZoom.x), LONG(10 * g_vZoom.y) };

	pTexture = CTextureMgr::GetInstance()->GetTexture(L"MAP", L"Track", 0);
	m_pDevice->GetSprite()->SetTransform(&matWorld);
	m_pDevice->GetSprite()->Draw(pTexture->pTexture,
		&rc,
		NULL,
		NULL,
		D3DCOLOR_ARGB(155, 255, 255, 255));

	m_pDevice->GetSprite()->SetTransform(&matWorld);

}

void CBackGround::SampleMonRender(void)
{
	D3DXMATRIX		matTrans, matWorld, matScale;
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(L"MONSTER", L"Enemy", m_pSampleMon->eType);

	// ÇöÀç »ùÇÃ
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixTranslation(&matTrans, m_pSampleMon->vPos.x, m_pSampleMon->vPos.y, 0.f);
	D3DXMatrixScaling(&matScale, g_vZoom.x, g_vZoom.y, 0.f);
	matWorld = matTrans * matScale;
	m_pDevice->GetSprite()->SetTransform(&matWorld);

	float	fX = float(pTexture->tImgInfo.Width) / 2.f;
	float	fY = float(pTexture->tImgInfo.Height) / 2.f;

	m_pDevice->GetSprite()->Draw(pTexture->pTexture,
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(155, 255, 255, 255));

	// ½ÃÀÛÀ§Ä¡ »ùÇÃ
	if (m_pSampleMon->ptStart.x != 0 && m_pSampleMon->ptStart.y != 0)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixTranslation(&matTrans, m_pSampleMon->ptStart.x - m_pMainView->GetScrollPos(0), m_pSampleMon->ptStart.y - m_pMainView->GetScrollPos(1), 0.f);
		D3DXMatrixScaling(&matScale, g_vZoom.x, g_vZoom.y, 0.f);
		matWorld = matTrans * matScale;
		m_pDevice->GetSprite()->SetTransform(&matWorld);
		fX = float(pTexture->tImgInfo.Width) / 2.f;
		fY = float(pTexture->tImgInfo.Height) / 2.f;
		m_pDevice->GetSprite()->Draw(pTexture->pTexture,
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(130, 0, 0, 255));
	}
}

CBackGround::CBackGround()
{
}

CBackGround::~CBackGround()
{
}

HRESULT CBackGround::Initialize(void)
{
	m_pDevice = CDevice::GetInstance();
	m_pMainView = ((CMainFrame*)AfxGetMainWnd())->m_pMainView;
	m_pRectlist = m_pMainView->m_Rectlist;
	m_pBObjlist = m_pMainView->m_BObjlist;
	m_pMap2list = &(m_pMainView->m_Map2list);
	m_pSampleImg = m_pMainView->m_pSampleImg;
	m_pSuplist = m_pMainView->m_Suplist;
	m_pMonlist = &(m_pMainView->m_Monlist);

	return S_OK;
}

void CBackGround::Progress(void)
{
}
#pragma endregion

void CBackGround::Render(void)
{
	D3DXMATRIX		matScale, matTrans, matWorld;
	D3DXMatrixIdentity(&matWorld);

	const TEXINFO*		pTexture;
	RECT			rc;

	// ¹è°æ 2 ·»´õ
	D3DXMatrixIdentity(&matWorld);
	pTexture = CTextureMgr::GetInstance()->GetTexture(L"MAP", L"Map", 1);
	for (auto& map : (*m_pMap2list))
	{
		D3DXMatrixTranslation(&matTrans, map->vPos.x - m_pMainView->GetScrollPos(0), map->vPos.y - m_pMainView->GetScrollPos(1), 0.f);
		D3DXMatrixScaling(&matScale, g_vZoom.x, g_vZoom.y, 0.f);
		matWorld = matTrans * matScale;
		m_pDevice->GetSprite()->SetTransform(&matWorld);
		rc = {
			LONG(map->vPos.x - map->vSize.x / 2.f),
			LONG(map->vPos.y - map->vSize.y / 2.f),
			LONG(map->vPos.x + map->vSize.x / 2.f),
			LONG(map->vPos.y + map->vSize.y / 2.f),
		};
		m_pDevice->GetSprite()->Draw(
			pTexture->pTexture,
			&rc,
			&D3DXVECTOR3(map->vSize.x / 2.f, map->vSize.y / 2.f, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 200, 255, 200));
		m_pDevice->GetSprite()->SetTransform(&matWorld);
	}

	// obj·»´õ
	ObjRender();

	//¹è°æ 1 ·»´õ
	m_pDevice->GetSprite()->End();
	m_pDevice->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
	m_pDevice->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pDevice->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVDESTALPHA);
	m_pDevice->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTALPHA);
	pTexture = CTextureMgr::GetInstance()->GetTexture(L"MAP", L"Map", 0);
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matScale, g_vZoom.x, g_vZoom.y, 0.f);
	matWorld = matScale;

	m_pDevice->GetSprite()->SetTransform(&matWorld);

	float	fX = float(pTexture->tImgInfo.Width);
	float	fY = float(pTexture->tImgInfo.Height);
	rc = { m_pMainView->GetScrollPos(0), m_pMainView->GetScrollPos(1), m_pMainView->GetScrollPos(0) + LONG(WINCX / g_vZoom.x), m_pMainView->GetScrollPos(1) + LONG(WINCY / g_vZoom.y) };

	m_pDevice->GetSprite()->Draw(pTexture->pTexture,
		&rc,
		NULL,
		NULL,
		D3DCOLOR_ARGB(255, 255, 200, 200));
	m_pDevice->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	m_pDevice->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	m_pDevice->GetSprite()->End();
	m_pDevice->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	// ·ºÆ® ·»´õ
	RectRender();

	// ¹ßÆÇ ·»´õ
	SupportRender();

	// ¸ó½ºÅÍ ·»´õ
	MonsterRender();

	// »ùÇÃ ·»´õ
	m_pSampleImg = m_pMainView->m_pSampleImg;
	if (m_pSampleImg != nullptr)	SampleRender();
	m_pSampleSup = m_pMainView->m_pSampleSup;
	if (m_pSampleSup != nullptr)	SampleSupRender();
	m_pSampleMon = m_pMainView->m_pSampleMon;
	if (m_pSampleMon != nullptr)	SampleMonRender();
}

void CBackGround::Release(void)
{
}
