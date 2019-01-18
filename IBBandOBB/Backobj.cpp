#include "stdafx.h"
#include "Backobj.h"


void CBackobj::Draw(float & _fX, float & _fY, int & _iColor)
{
	if (_iColor > 0)
	{
		if (m_tInfo.iType == 14)				// 구름
		{
			m_pDevice->GetSprite()->Draw(pTexture->pTexture,
				NULL,
				&D3DXVECTOR3(_fX, _fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, m_arRGB[0] + (_iColor / 2), m_arRGB[1], m_arRGB[2] - _iColor));
		}
		else if (m_tInfo.iType >= 12)			// 링
		{
			m_pDevice->GetSprite()->Draw(pTexture->pTexture,
				NULL,
				&D3DXVECTOR3(_fX, _fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, m_arRGB[0] + _iColor, m_arRGB[1] - (2 * _iColor), m_arRGB[2] - (2 * _iColor)));
		}
		else if (m_tInfo.iType >= 9)			// 덩쿨
		{
			m_pDevice->GetSprite()->Draw(pTexture->pTexture,
				NULL,
				&D3DXVECTOR3(_fX, _fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, m_arRGB[0] + _iColor * 2, m_arRGB[1] + _iColor, m_arRGB[2] + _iColor));
		}
		else if (m_tInfo.iType >= 5)			// 나무, 야자수
		{
			m_pDevice->GetSprite()->Draw(pTexture->pTexture,
				NULL,
				&D3DXVECTOR3(_fX, _fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, m_arRGB[0] - _iColor * 2, m_arRGB[1], m_arRGB[2]) + _iColor);
		}
		else									// 산, 풀
		{
			m_pDevice->GetSprite()->Draw(pTexture->pTexture,
				NULL,
				&D3DXVECTOR3(_fX, _fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, m_arRGB[0] - _iColor, m_arRGB[1], m_arRGB[2] - _iColor));
		}
	}
	else
	{
		_iColor *= -1;
		if (m_tInfo.iType == 14)				// 구름
		{
			m_pDevice->GetSprite()->Draw(pTexture->pTexture,
				NULL,
				&D3DXVECTOR3(_fX, _fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, m_arRGB[0] - (_iColor / 2), m_arRGB[1] + _iColor*2, m_arRGB[2]));
		}
		else if (m_tInfo.iType >= 12)			// 링
		{
			m_pDevice->GetSprite()->Draw(pTexture->pTexture,
				NULL,
				&D3DXVECTOR3(_fX, _fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, m_arRGB[0] + _iColor, m_arRGB[1] - (2 * _iColor), m_arRGB[2] - (2 * _iColor)));
		}
		else if (m_tInfo.iType >= 9)			// 덩쿨
		{
			m_pDevice->GetSprite()->Draw(pTexture->pTexture,
				NULL,
				&D3DXVECTOR3(_fX, _fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, m_arRGB[0] + _iColor/2, m_arRGB[1] + _iColor*2, m_arRGB[2] - _iColor));
		}
		else if (m_tInfo.iType >= 5)			// 나무, 야자수
		{
			m_pDevice->GetSprite()->Draw(pTexture->pTexture,
				NULL,
				&D3DXVECTOR3(_fX, _fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, m_arRGB[0] - _iColor, m_arRGB[1]+ _iColor*2, m_arRGB[2] + 100));
		}
		else									// 산, 풀
		{
			m_pDevice->GetSprite()->Draw(pTexture->pTexture,
				NULL,
				&D3DXVECTOR3(_fX, _fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, m_arRGB[0] - _iColor, m_arRGB[1], m_arRGB[2] + _iColor));
		}
	}
}

CBackobj::CBackobj()
{
}

CBackobj::~CBackobj()
{
}

HRESULT CBackobj::Initialize(void)
{
	pTexture = CTextureMgr::GetInstance()->GetTexture(m_tInfo.ObjKey, m_tInfo.StateKey, m_tInfo.iType);
	if (m_tInfo.iType == 14)				// 구름
	{
		m_arRGB[0] = 145 + rand()%10;
		m_arRGB[1] = 120;
		m_arRGB[2] = 215 + rand()%10;
	}
	else if (m_tInfo.iType >= 12)			// 링
	{
		m_arRGB[0] = 0;
		m_arRGB[1] = 245 + rand() % 10;
		m_arRGB[2] = 245 + rand() % 10;
	}
	else if (m_tInfo.iType >= 9)			// 덩쿨
	{
		m_arRGB[0] = 0;
		m_arRGB[1] = rand() % 10;
		m_arRGB[2] = 125 + rand() % 10;
	}
	else if (m_tInfo.iType >= 5)			// 나무, 야자수
	{
		m_arRGB[0] = 255;
		m_arRGB[1] = 110 + rand() % 10;
		m_arRGB[2] = 70 + rand() % 10;
	}
	else									// 산, 풀
	{
		m_arRGB[0] = 140 + rand() % 10;
		m_arRGB[1] = 250;
		m_arRGB[2] = 140 + rand() % 10;
	}
	return S_OK;
}

int CBackobj::Progress(void)
{
	return 0;
}

void CBackobj::Render(void)
{
	D3DXMATRIX		matTrans, matScale;

	if (m_tInfo.vScale.y < 0.f)
	{
		m_pDevice->GetSprite()->End();
		m_pDevice->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
		m_pDevice->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pDevice->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTALPHA);
		m_pDevice->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		D3DXMatrixIdentity(&m_tInfo.matWorld);
		if(m_tInfo.iType == 14 || m_tInfo.iType == 13)
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + g_vScroll.x, m_tInfo.vPos.y + g_vScroll.y, 0.f);
		else
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + g_vScroll.x, m_tInfo.vPos.y + g_vScroll.y, 0.f);
		D3DXMatrixScaling(&matScale, m_tInfo.vScale.x, m_tInfo.vScale.y, 0.f);
		m_tInfo.matWorld = matScale * matTrans;
		D3DXMatrixScaling(&matScale, g_vZoom.x, g_vZoom.y, 0.f);
		m_tInfo.matWorld *= matScale;

		m_pDevice->GetSprite()->SetTransform(&m_tInfo.matWorld);

		float	fX = float(pTexture->tImgInfo.Width) / 2.f;
		float	fY = float(pTexture->tImgInfo.Height) / 2.f;

		int iColor = 0;
		if (0 == (LONG(g_vScroll.x / 500)) % 2)
		{
			iColor = (LONG(-g_vScroll.x) % 500) / 5;
		}
		else
		{
			iColor = 100 - ((LONG(-g_vScroll.x) % 500) / 5);
		}
		iColor *= -1;

		Draw(fX, fY, iColor);

		m_pDevice->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		m_pDevice->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

		m_pDevice->GetSprite()->End();
		m_pDevice->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
	}
	else //if (m_tInfo.vScale.y >= 0.f)
	{
		m_pDevice->GetSprite()->End();
		m_pDevice->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
		m_pDevice->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pDevice->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVDESTALPHA);
		m_pDevice->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		pTexture = CTextureMgr::GetInstance()->GetTexture(L"MAP", L"Fixed", m_tInfo.iType);
		D3DXMatrixIdentity(&m_tInfo.matWorld);
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + g_vScroll.x, m_tInfo.vPos.y + g_vScroll.y, 0.f);
		D3DXMatrixScaling(&matScale, m_tInfo.vScale.x, m_tInfo.vScale.y, 0.f);
		m_tInfo.matWorld = matScale * matTrans;
		D3DXMatrixScaling(&matScale, g_vZoom.x, g_vZoom.y, 0.f);
		m_tInfo.matWorld *= matScale;

		m_pDevice->GetSprite()->SetTransform(&m_tInfo.matWorld);

		float	fX = float(pTexture->tImgInfo.Width) / 2.f;
		float	fY = float(pTexture->tImgInfo.Height) / 2.f;

		int iColor = 0;
		if (0 == (LONG(g_vScroll.x / 500)) % 2)
		{
			iColor = (LONG(-g_vScroll.x) % 500) / 5;
		}
		else
		{
			iColor = 100 - ((LONG(-g_vScroll.x) % 500) / 5);
		}

		Draw(fX, fY, iColor);

		m_pDevice->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		m_pDevice->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

		m_pDevice->GetSprite()->End();
		m_pDevice->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
	}


}

void CBackobj::Release(void)
{
}
