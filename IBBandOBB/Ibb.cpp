#include "stdafx.h"
#include "Ibb.h"


void CIbb::CheckDirection(void)
{
	m_vDir.x = 0.f;
	//m_vDir.y = 0.f;
	
	if (0.f < m_fJumpTime) m_fJumpTime -= GET_TIME;

	if (GetAsyncKeyState(VK_LEFT))
	{
		m_vDir.x = -m_fXSpeed;
		m_tInfo.vScale.x = -1.f * (fabsf(m_tInfo.vScale.x));
		if (!(m_dwState & 0x0001))
		{
			m_dwState |= 0x0001;
			lstrcpy(m_tInfo.StateKey, L"I_move");
			m_tFrame = { 0.f, 24.f, 8.f };
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		m_vDir.x = m_fXSpeed;
		m_tInfo.vScale.x = (fabsf(m_tInfo.vScale.x));
		if (!(m_dwState & 0x0001))
		{
			m_dwState |= 0x0001;
			lstrcpy(m_tInfo.StateKey, L"I_move");
			m_tFrame = { 0.f, 24.f, 8.f };
		}
	}
	else
	{
		m_dwState &= 0x0000;
		lstrcpy(m_tInfo.StateKey, L"I_stand");
		m_tFrame = { 0.f, 0.f, 0.f };
		m_tInfo.vScale.x = fabsf(m_tInfo.vScale.x);
	}
	if (GetAsyncKeyState(VK_UP))
	{
		if ((m_fJumpTime <= 0.f))
		{
			if (m_vDir.y == 0.f)
			{
				if (m_fGravity > 0.f)
				{
					CSoundMgr::GetInst()->PlaySound(L"jump.mp3", CHANNEL_EFFECT, 0.9f);
					m_fJumpTime = 0.3f;
					m_vDir.y -= 660.f;
					m_tInfo.vPos.y -= 2.f;
					if (m_bOnObb) m_tInfo.vPos.y -= 8.f;
				}
				else
				{
					CSoundMgr::GetInst()->PlaySound(L"jump.mp3", CHANNEL_EFFECT, 0.9f);
					m_fJumpTime = 0.3f;
					m_vDir.y += 660.f;
					m_tInfo.vPos.y += 2.f;
					if (m_bOnObb) m_tInfo.vPos.y += 8.f;
				}
			}
			
		}
	}
	if (GetAsyncKeyState(VK_SPACE))
		m_vDir.y -= 100.f;
	

	//printf("위에있음 : %d \n", (int)m_bOnObb);
	m_vDir.y += m_fGravity;
	m_bOnObb = false;
}

void CIbb::SetHoleState(int _istate)
{
	if (m_iHoleState == 1 && _istate == 2)		{ m_fGravity *= -1.f; m_tInfo.vScale.y *= -1.f; m_vDir.y += m_fGravity * 2.f; }
	else if (m_iHoleState == 2 && _istate == 1) { m_fGravity *= -1.f; m_tInfo.vScale.y *= -1.f; m_vDir.y += m_fGravity * 2.f; }
	else if (m_iHoleState == 3 && _istate == 4) { m_fGravity *= -1.f; m_tInfo.vScale.y *= -1.f; m_vDir.y += m_fGravity * 2.f; }
	else if (m_iHoleState == 4 && _istate == 3) { m_fGravity *= -1.f; m_tInfo.vScale.y *= -1.f; m_vDir.y += m_fGravity * 2.f; }
	m_iHoleState = _istate;
}

void CIbb::SetCollison(float ftime, D3DXVECTOR3 vcolpos, int inum)
{
 	if (inum == 0)					// 가로 타일하고 충돌
	{
		if (m_fGravity > 0.f)		// 위에서 아래로 떨어질때
		{
			if (m_fCollisionTime > ftime ||			// 박을 예정이었던곳보다 더 빨리 박을때
				m_vCollisionPos.y == 0)			// 박을 예정이 없었을 때
			{
				m_fCollisionTime = ftime;
				m_vCollisionPos = vcolpos;
			}
		}
		else					 // 아래에서 위로
		{
			if (vcolpos.y > m_vCollisionPos.y || m_vCollisionPos.y == 0)
			{
				m_fCollisionTime = ftime;
				m_vCollisionPos = vcolpos;
			}
		}
	}
}

void CIbb::WorldMatrix(void)
{
	D3DXMATRIX		matTrans, matScale;
	D3DXMatrixIdentity(&m_tInfo.matWorld);
	D3DXMatrixTranslation(&matTrans, floor(m_tInfo.vPos.x) + g_vScroll.x, floor(m_tInfo.vPos.y) + g_vScroll.y, 0.f);
	D3DXMatrixScaling(&matScale, m_tInfo.vScale.x, m_tInfo.vScale.y, 0.f);
	m_tInfo.matWorld = matScale * matTrans;
}

void CIbb::FrameMove(void)
{
	m_tFrame.fFrame += m_tFrame.fCount * GET_TIME;

	if (m_tFrame.fFrame > m_tFrame.fMax)
		m_tFrame.fFrame = 0.f;
}

void CIbb::Move(void)
{
	m_tInfo.vPos.x += m_vDir.x * GET_TIME;
	m_tInfo.vPos.y += m_vDir.y * GET_TIME;
}

void CIbb::CCDCheck(void)
{
	if (m_fCollisionTime != 0.00f)
	{
		m_fCollisionTime -= GET_TIME;
		if (m_fCollisionTime < 0.17f)
		{
			m_tInfo.vPos.y = m_vCollisionPos.y;
			m_fCollisionTime = 0.f;
			m_vCollisionPos = { 0.f, 0.f, 0.f };
			m_vDir = { 0.f, 0.f, 0.f };
			m_iHoleState = 0;
		}
		if (m_fCollisionTime > 0.f)
		{
			Move();
		}
	}
	else
	{
		Move();
	}
}

CIbb::CIbb()
{
}

CIbb::~CIbb()
{
}

HRESULT CIbb::Initialize(void)
{
	m_tInfo.vPos = { 440.f, 500.f, 0.f };
	m_tFrame = { 0.f, 0.f, 0.f };
	lstrcpy(m_tInfo.StateKey, L"I_stand");
	lstrcpy(m_tInfo.ObjKey, L"PLAYER");
	m_dwState = 0;
	m_tInfo.vScale = { 0.45f, 0.45f, 0.f };
	m_fXSpeed = 300.f;
	m_tInfo.vSize.x = ceil((CTextureMgr::GetInstance()->GetTexture(m_tInfo.ObjKey, m_tInfo.StateKey, m_tFrame.fFrame)->tImgInfo.Width -  40.f) * m_tInfo.vScale.x);
	m_tInfo.vSize.y = ceil((CTextureMgr::GetInstance()->GetTexture(m_tInfo.ObjKey, m_tInfo.StateKey, m_tFrame.fFrame)->tImgInfo.Height - 32.f) * m_tInfo.vScale.y);
	m_fCollisionTime = 0.f;
	g_vScroll.x = 0.f;
	g_vScroll.y = -200.f;
	m_fGravity = 25.f;
	m_vDir = { 0.f, 0.f, 0.f };
	m_fJumpTime = 0.f;
	m_fGravityTime = 0.f;

	return S_OK;
}

int CIbb::Progress(void)
{
	if (GetAsyncKeyState('Q') & 0x0001)
	{
		g_vZoom.x -= 0.1;
		g_vZoom.y -= 0.1;
		g_vScroll.x += (WINCX / 2.f) * 0.1f;
		g_vScroll.y += (WINCY / 2.f) * 0.1f;
	}
	if (GetAsyncKeyState('E') & 0x0001)
	{
		g_vZoom.x += 0.1;
		g_vZoom.y += 0.1;
		g_vScroll.x -= (WINCX / 2.f) * 0.1f;
		g_vScroll.y -= (WINCY / 2.f) * 0.1f;
	}

	FrameMove();
	CCDCheck();

	WorldMatrix();

	
	//printf("위치 : %f, %f \n", m_tInfo.vPos.x, m_tInfo.vPos.y);
	//printf("속도 : %f, %f \n", m_vDir.x, m_vDir.y);
	


	return 0;
}

void CIbb::Render(void)
{
	const TEXINFO*	pTexture = CTextureMgr::GetInstance()->GetTexture(m_tInfo.ObjKey, m_tInfo.StateKey, m_tFrame.fFrame);

	if (nullptr == pTexture)
		return;

	D3DXMATRIX	matZoom;
	D3DXMatrixScaling(&matZoom, g_vZoom.x, g_vZoom.y, 0.f);
	m_tInfo.matWorld *= matZoom;

	if (m_tInfo.vPos.y < 0.f || m_tInfo.vPos.y > MAPY)
	{
		pTexture = CTextureMgr::GetInstance()->GetTexture(m_tInfo.ObjKey, L"I_jump", 0);
		D3DXMATRIX matRender, matSclae;
		if (m_tInfo.vPos.y < 0.f)
		{
			D3DXMatrixScaling(&matSclae, 1.f, g_vZoom.y, 0.f);
			D3DXMatrixTranslation(&matRender, m_tInfo.vPos.x + g_vScroll.x, 16.f, 0.f);
		}
		else
		{
			D3DXMatrixScaling(&matSclae, 1.f, -g_vZoom.y, 0.f);
			D3DXMatrixTranslation(&matRender, m_tInfo.vPos.x + g_vScroll.x, WINCY - 20.f, 0.f);
		}
		D3DXMatrixScaling(&matZoom, g_vZoom.x, 1.f, 0.f);

		float fX = pTexture->tImgInfo.Width / 2.f;
		float fY = pTexture->tImgInfo.Height / 2.f;
		matRender = matSclae * matRender * matZoom;
		CDevice::GetInstance()->GetSprite()->SetTransform(&matRender);
		CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, nullptr, &D3DXVECTOR3(fX, fY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else
	{
		float fX = pTexture->tImgInfo.Width / 2.f;
		float fY = pTexture->tImgInfo.Height / 2.f;
		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, nullptr, &D3DXVECTOR3(fX, fY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CIbb::Release(void)
{
}
