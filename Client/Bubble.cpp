#include "stdafx.h"
#include "Bubble.h"


CBubble::CBubble()
{
}


CBubble::~CBubble()
{
}

HRESULT CBubble::Initialize(void)
{
	pTexture = CTextureMgr::GetInstance()->GetTexture(L"EFFECT", L"Mouse", 0);
	m_tFrame = { 0.f, 12.f, 12.f };
	m_tInfo.vPos.x = m_tInfo.vPos.x - 5.f + rand() % 10;
	m_tInfo.vPos.y = m_tInfo.vPos.y - 5.f + rand() % 10;
	float fRand = ((rand() % 5) / 20.f);
	m_tInfo.vScale = { 0.4f + fRand, 0.4f + fRand, 0.f };
	return S_OK;
}

int CBubble::Progress(void)
{
	m_tFrame.fFrame += m_tFrame.fCount * GET_TIME;

	if (m_tFrame.fFrame > m_tFrame.fMax)
	{
		m_tFrame.fFrame = 0.f;
		return 1;
	}

	return 0;
}

void CBubble::Render(void)
{
	D3DXMATRIX			matTrans, matScale;
	D3DXMatrixIdentity(&m_tInfo.matWorld);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	D3DXMatrixScaling(&matScale, m_tInfo.vScale.x, m_tInfo.vScale.y, 0.f);
	m_tInfo.matWorld = matScale * matTrans;
	D3DXMatrixScaling(&matScale, g_vZoom.x, g_vZoom.y, 0.f);
	m_tInfo.matWorld *= matScale;
	m_pDevice->GetSprite()->SetTransform(&m_tInfo.matWorld);
	float	fX = float(pTexture->tImgInfo.Width) / 2.f;
	float	fY = float(pTexture->tImgInfo.Height) / 2.f;
	m_pDevice->GetSprite()->Draw(pTexture->pTexture,
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255 - (int(m_tFrame.fFrame)), 255, 255 - (int(m_tFrame.fFrame))));
}

void CBubble::Release(void)
{
}
