#include "stdafx.h"
#include "Support.h"


CSupport::CSupport()
{
}


CSupport::~CSupport()
{
}

HRESULT CSupport::Initialize(void)
{
	pTexture = CTextureMgr::GetInstance()->GetTexture(m_tInfo.ObjKey, m_tInfo.StateKey, m_tInfo.iType);
	switch (m_tInfo.iType)
	{
	case 0:
		m_tInfo.vSize.x = fabsf(round((CTextureMgr::GetInstance()->GetTexture(m_tInfo.ObjKey, m_tInfo.StateKey, m_tInfo.iType)->tImgInfo.Width - 22.f) * m_tInfo.vScale.x));
		m_tInfo.vSize.y = fabsf(round((CTextureMgr::GetInstance()->GetTexture(m_tInfo.ObjKey, m_tInfo.StateKey, m_tInfo.iType)->tImgInfo.Height - 16.f) * m_tInfo.vScale.y));
		break;			
	case 1:				
		m_tInfo.vSize.x = fabsf(round((CTextureMgr::GetInstance()->GetTexture(m_tInfo.ObjKey, m_tInfo.StateKey, m_tInfo.iType)->tImgInfo.Width - 32.f) * m_tInfo.vScale.x));
		m_tInfo.vSize.y = fabsf(round((CTextureMgr::GetInstance()->GetTexture(m_tInfo.ObjKey, m_tInfo.StateKey, m_tInfo.iType)->tImgInfo.Height - 20.f) * m_tInfo.vScale.y));
		break;			
	case 2:				
		m_tInfo.vSize.x = fabsf(round((CTextureMgr::GetInstance()->GetTexture(m_tInfo.ObjKey, m_tInfo.StateKey, m_tInfo.iType)->tImgInfo.Width - 38.f) * m_tInfo.vScale.x));
		m_tInfo.vSize.y = fabsf(round((CTextureMgr::GetInstance()->GetTexture(m_tInfo.ObjKey, m_tInfo.StateKey, m_tInfo.iType)->tImgInfo.Height - 6.f) * m_tInfo.vScale.y));
		break;
	}
	
	if (int(m_tInfo.vSize.x) % 2 == 1) m_tInfo.vSize.x -= 1.f;
	if (int(m_tInfo.vSize.y) % 2 == 1) m_tInfo.vSize.y -= 1.f;


	return S_OK;
}

int CSupport::Progress(void)
{
	return 0;
}

void CSupport::Render(void)
{
	D3DXMATRIX			matTrans, matScale;

	D3DXMatrixIdentity(&m_tInfo.matWorld);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + g_vScroll.x, m_tInfo.vPos.y + g_vScroll.y, 0.f);
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
		D3DCOLOR_ARGB(255, 255, 255, 255));

	//D3DXVECTOR2	vPoint[5] = {
	//	D3DXVECTOR2(m_tInfo.vPos.x - m_tInfo.vSize.x / 2.f + g_vScroll.x, m_tInfo.vPos.y - m_tInfo.vSize.y / 2.f + g_vScroll.y),
	//	D3DXVECTOR2(m_tInfo.vPos.x + m_tInfo.vSize.x / 2.f + g_vScroll.x,m_tInfo.vPos.y - m_tInfo.vSize.y / 2.f + g_vScroll.y),
	//	D3DXVECTOR2(m_tInfo.vPos.x + m_tInfo.vSize.x / 2.f + g_vScroll.x,m_tInfo.vPos.y + m_tInfo.vSize.y / 2.f + g_vScroll.y),
	//	D3DXVECTOR2(m_tInfo.vPos.x - m_tInfo.vSize.x / 2.f + g_vScroll.x, m_tInfo.vPos.y + m_tInfo.vSize.y / 2.f + g_vScroll.y),
	//	D3DXVECTOR2(m_tInfo.vPos.x - m_tInfo.vSize.x / 2.f + g_vScroll.x, m_tInfo.vPos.y - m_tInfo.vSize.y / 2.f + g_vScroll.y)
	//};
	//CDevice::GetInstance()->Render_End();
	//CDevice::GetInstance()->Render_Begin();
	//CDevice::GetInstance()->GetLine()->Draw(vPoint, 5, D3DCOLOR_ARGB(255, 0, 0, 255));
	//CDevice::GetInstance()->Render_End();
	//CDevice::GetInstance()->Render_Begin();
}

void CSupport::Release(void)
{
}
