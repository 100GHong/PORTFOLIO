#include "stdafx.h"
#include "Maprect.h"


CMaprect::CMaprect()
{
}


CMaprect::~CMaprect()
{
}

HRESULT CMaprect::Initialize(void)
{
	pTexture = CTextureMgr::GetInstance()->GetTexture(m_tInfo.ObjKey, m_tInfo.StateKey, 1);
	return S_OK;
}

int CMaprect::Progress(void)
{
	return 0;
}

void CMaprect::Render(void)
{
}

void CMaprect::Release(void)
{
}

void CMaprect::Render(int iStage)
{
	D3DXMATRIX		matScale, matTrans;
	RECT			rc;
	D3DXMatrixIdentity(&m_tInfo.matWorld);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + g_vScroll.x, m_tInfo.vPos.y + g_vScroll.y, 0.f);
	D3DXMatrixScaling(&matScale, g_vZoom.x, g_vZoom.y, 0.f);
	m_tInfo.matWorld = matTrans * matScale;
	m_pDevice->GetSprite()->SetTransform(&m_tInfo.matWorld);
	rc = {
		LONG(m_tInfo.vPos.x - m_tInfo.vSize.x / 2.f),
		LONG(m_tInfo.vPos.y - m_tInfo.vSize.y / 2.f),
		LONG(m_tInfo.vPos.x + m_tInfo.vSize.x / 2.f),
		LONG(m_tInfo.vPos.y + m_tInfo.vSize.y / 2.f),
	};
	switch (iStage)
	{
	case 0:
		m_pDevice->GetSprite()->Draw(
			pTexture->pTexture,
			&rc,
			&D3DXVECTOR3(m_tInfo.vSize.x / 2.f, m_tInfo.vSize.y / 2.f, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 200, 200, 200));
		break;
	case 1:
		m_pDevice->GetSprite()->Draw(
			pTexture->pTexture,
			&rc,
			&D3DXVECTOR3(m_tInfo.vSize.x / 2.f, m_tInfo.vSize.y / 2.f, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 100, 150, 240));
		break;
	case 2:
		m_pDevice->GetSprite()->Draw(
			pTexture->pTexture,
			&rc,
			&D3DXVECTOR3(m_tInfo.vSize.x / 2.f, m_tInfo.vSize.y / 2.f, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 200, 150));
		break;
	case 3:
		m_pDevice->GetSprite()->Draw(
			pTexture->pTexture,
			&rc,
			&D3DXVECTOR3(m_tInfo.vSize.x / 2.f, m_tInfo.vSize.y / 2.f, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 230, 230, 250));
		break;
	}

}
