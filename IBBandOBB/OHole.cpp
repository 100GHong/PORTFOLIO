#include "stdafx.h"
#include "OHole.h"


COHole::COHole()
{
}


COHole::~COHole()
{
}

HRESULT COHole::Initialize(void)
{
	pTexture = CTextureMgr::GetInstance()->GetTexture(m_tInfo.ObjKey, m_tInfo.StateKey, 0);
	m_tFrame = { 0.f, 16.f, 32.f };
	return S_OK;
}

int COHole::Progress(void)
{
	if (m_tFrame.fFrame > m_tFrame.fMax)
	{
		m_tFrame.fCount *= -1.f;
		m_tFrame.fFrame = m_tFrame.fMax;
	}
	else if (m_tFrame.fFrame < 0.f)
	{
		m_tFrame.fCount *= -1.f;
		m_tFrame.fFrame = 0.f;
	}
	m_tFrame.fFrame += m_tFrame.fCount * GET_TIME;
	return 0;
}

void COHole::Render(void)
{

	D3DXMATRIX			matScale, matTrans;
	D3DXMatrixIdentity(&m_tInfo.matWorld);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + g_vScroll.x, m_tInfo.vPos.y + g_vScroll.y, 0.f);
	D3DXMatrixScaling(&matScale, g_vZoom.x, g_vZoom.y, 0.f);
	m_tInfo.matWorld = matTrans * matScale;
	m_pDevice->GetSprite()->SetTransform(&m_tInfo.matWorld);
	RECT rc;
	if (m_tInfo.vSize.x > m_tInfo.vSize.y)
	{
		rc = { 0, LONG(m_tFrame.fFrame), LONG(m_tInfo.vSize.x), LONG(m_tFrame.fFrame + m_tInfo.vSize.y + 4.f) };
		m_pDevice->GetSprite()->Draw(
			pTexture->pTexture,
			&rc,
			&D3DXVECTOR3(m_tInfo.vSize.x / 2.f, (m_tInfo.vSize.y / 2.f) + 2.f, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else
	{
		rc = { LONG(m_tFrame.fFrame), 2, LONG(m_tFrame.fFrame + m_tInfo.vSize.x), LONG(m_tInfo.vSize.y + 8.f) };
		m_pDevice->GetSprite()->Draw(
			pTexture->pTexture,
			&rc,
			&D3DXVECTOR3((m_tInfo.vSize.x / 2.f) + 2.f, m_tInfo.vSize.y / 2.f, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void COHole::Release(void)
{
}
