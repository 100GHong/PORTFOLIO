#include "stdafx.h"
#include "Track.h"


CTrack::CTrack()
{
}


CTrack::~CTrack()
{
}

HRESULT CTrack::Initialize(void)
{
	pTexture = CTextureMgr::GetInstance()->GetTexture(m_tInfo.ObjKey, m_tInfo.StateKey, 0);
	return S_OK;
}

int CTrack::Progress(void)
{
	return 0;
}

void CTrack::Render(void)
{
	D3DXMATRIX			matScale, matTrans;
	D3DXMatrixIdentity(&m_tInfo.matWorld);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + g_vScroll.x, m_tInfo.vPos.y + g_vScroll.y, 0.f);
	D3DXMatrixScaling(&matScale, g_vZoom.x, g_vZoom.y, 0.f);
	m_tInfo.matWorld = matTrans * matScale;
	m_pDevice->GetSprite()->SetTransform(&m_tInfo.matWorld);
	RECT rc = { 0, 0, LONG(m_tInfo.vSize.x), LONG(m_tInfo.vSize.y) };
	m_pDevice->GetSprite()->Draw(
		pTexture->pTexture,
		&rc,
		&D3DXVECTOR3(m_tInfo.vSize.x / 2.f, m_tInfo.vSize.y / 2.f, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CTrack::Release(void)
{
}
