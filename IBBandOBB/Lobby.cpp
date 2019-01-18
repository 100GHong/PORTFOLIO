#include "stdafx.h"
#include "Lobby.h"
#include "ObjInclude.h"

CLobby::CLobby()
{
}


CLobby::~CLobby()
{
	Release();
}

HRESULT CLobby::Initialize(void)
{
	LoadData();

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		m_Objlist[i].sort([](CObj*& obj1, CObj*& obj2) -> bool
		{
			const INFO&	a = obj1->GetInfo();
			const INFO& b = obj2->GetInfo();
			return a.vPos.x < b.vPos.x;
		});
	}

//	CSoundMgr::GetInst()->PlayBGM(L"aa.mp3", 0.5f);

	return S_OK;
}

void CLobby::CollisionCheck(void)
{
	INFO&	rIbb = m_pIbb->GetInfo();
	INFO&	rObb = m_pObb->GetInfo();
	const D3DXVECTOR3&	 rDir = static_cast<CIbb*>(m_pIbb)->GetDir();
	const D3DXVECTOR3&	 rODir = static_cast<CObb*>(m_pObb)->GetDir();
	RECT ccd;
	RECT ccdx;
	RECT occd;
	RECT occdx;

	// IBB �浹��Ʈ ����
	if (rDir.y > 0.f)
	{
		ccd = { LONG(rIbb.vPos.x - rIbb.vSize.x / 2.f),
			LONG(rIbb.vPos.y - rIbb.vSize.y / 2.f),
			LONG((rIbb.vPos.x + rIbb.vSize.x / 2.f)),
			LONG((rIbb.vPos.y + rIbb.vSize.y / 2.f) + (rDir.y * 0.05f)) };
	}
	else
	{
		ccd = { LONG(rIbb.vPos.x - rIbb.vSize.x / 2.f),
			LONG((rIbb.vPos.y - rIbb.vSize.y / 2.f) + (rDir.y * 0.05f)),
			LONG((rIbb.vPos.x + rIbb.vSize.x / 2.f)),
			LONG(rIbb.vPos.y + rIbb.vSize.y / 2.f) };
	}
	if (rDir.x > 0.f)
	{
		ccdx = { LONG(rIbb.vPos.x - rIbb.vSize.x / 2.f),
			LONG(rIbb.vPos.y - rIbb.vSize.y / 2.f),
			LONG((rIbb.vPos.x + rIbb.vSize.x / 2.f) + (rDir.x * 0.05f)),
			LONG((rIbb.vPos.y + rIbb.vSize.y / 2.f)) };
	}
	else
	{
		ccdx = { LONG((rIbb.vPos.x - rIbb.vSize.x / 2.f) + (rDir.x * 0.05f)),
			LONG((rIbb.vPos.y - rIbb.vSize.y / 2.f)),
			LONG((rIbb.vPos.x + rIbb.vSize.x / 2.f)),
			LONG(rIbb.vPos.y + rIbb.vSize.y / 2.f) };
	}
	// OBB �浹��Ʈ ����
	if (rODir.y > 0.f)
	{
		occd = { LONG(rObb.vPos.x - rObb.vSize.x / 2.f),
			LONG(rObb.vPos.y - rObb.vSize.y / 2.f),
			LONG((rObb.vPos.x + rObb.vSize.x / 2.f)),
			LONG((rObb.vPos.y + rObb.vSize.y / 2.f) + (rODir.y * 0.05f)) };
	}
	else
	{
		occd = { LONG(rObb.vPos.x - rObb.vSize.x / 2.f),
			LONG((rObb.vPos.y - rObb.vSize.y / 2.f) + (rODir.y * 0.05f)),
			LONG((rObb.vPos.x + rObb.vSize.x / 2.f)),
			LONG(rObb.vPos.y + rObb.vSize.y / 2.f) };
	}
	if (rODir.x > 0.f)
	{
		occdx = { LONG(rObb.vPos.x - rObb.vSize.x / 2.f),
			LONG(rObb.vPos.y - rObb.vSize.y / 2.f),
			LONG((rObb.vPos.x + rObb.vSize.x / 2.f) + (rODir.x * 0.05f)),
			LONG((rObb.vPos.y + rObb.vSize.y / 2.f)) };
	}
	else
	{
		occdx = { LONG((rObb.vPos.x - rObb.vSize.x / 2.f) + (rODir.x * 0.05f)),
			LONG((rObb.vPos.y - rObb.vSize.y / 2.f)),
			LONG((rObb.vPos.x + rObb.vSize.x / 2.f)),
			LONG(rObb.vPos.y + rObb.vSize.y / 2.f) };
	}

	// IBB <-> OBB �浹
	if (!(rDir.x == 0.f && rDir.y == 0 && rODir.x == 0 && rDir.y == 0))
	{
		RECT rc;
		// ������ �浹
		if (IntersectRect(&rc, &m_pIbb->GetRect(), &m_pObb->GetRect()))
		{
			// ��, �� �浹
			if (rc.right - rc.left < rc.bottom - rc.top)
			{
				if ((m_pIbb->GetInfo().vPos.x - m_pObb->GetInfo().vPos.x < 0 && rDir.x > 0.f && rODir.x < 0.f) ||		// ���� �о��
					(m_pIbb->GetInfo().vPos.x - m_pObb->GetInfo().vPos.x > 0 && rDir.x < 0.f && rODir.x > 0.f))
				{
					static_cast<CIbb*>(m_pIbb)->SetXdir(0.f);
					static_cast<CObb*>(m_pObb)->SetXdir(0.f);
					if (m_pIbb->GetInfo().vPos.x > m_pObb->GetInfo().vPos.x)
					{
						static_cast<CIbb*>(m_pIbb)->SetXPos(((rc.right - rc.left) / 2));
						static_cast<CObb*>(m_pObb)->SetXPos(-((rc.right - rc.left) / 2));
					}
					else
					{
						static_cast<CIbb*>(m_pIbb)->SetXPos(-((rc.right - rc.left) / 2));
						static_cast<CObb*>(m_pObb)->SetXPos(((rc.right - rc.left) / 2));
					}
				}
				else if (rDir.x == 0)											// OBB�� �����̴� ���
				{
					if (((m_pIbb->GetInfo().vPos.x - m_pObb->GetInfo().vPos.x) > 0.f && rODir.x > 0.f) ||	// OBB�� IBB������ �����϶� ���߱�
						(m_pIbb->GetInfo().vPos.x - m_pObb->GetInfo().vPos.x < 0.f && rODir.x < 0.f) )
					{
						static_cast<CObb*>(m_pObb)->SetXdir(0.f);
					}
				}
				else if (rODir.x == 0)									// IBB�� �����̴� ���
				{
					if (((m_pIbb->GetInfo().vPos.x - m_pObb->GetInfo().vPos.x) > 0.f && rDir.x < 0.f) ||	// IBB�� OBB������ �����϶� ���߱�
						(m_pIbb->GetInfo().vPos.x - m_pObb->GetInfo().vPos.x < 0.f && rDir.x > 0.f))
					{
						static_cast<CIbb*>(m_pIbb)->SetXdir(0.f);
					}
				}
			}
			// ��, �� �浹
			else
			{
				if (m_pIbb->GetInfo().vPos.y < m_pObb->GetInfo().vPos.y)			// IBB�� �����ְ�
				{
					static_cast<CIbb*>(m_pIbb)->SetOnObb();
					static_cast<CObb*>(m_pObb)->SetOnIbb();
					if (static_cast<CObb*>(m_pObb)->GetGravity() > 0.f)				// �߷��� �Ʒ��� ����� ��
					{
						if (rODir.y < 0.f)											// OBB�� �����Ϸ���
						{
							static_cast<CIbb*>(m_pIbb)->SetYdir(rODir.y);					// �����ض�
							static_cast<CIbb*>(m_pIbb)->SetYPos(-(rc.bottom - rc.top) + 1);
						}
						else															// �����ϴ°� �ƴϸ�
						{
							static_cast<CIbb*>(m_pIbb)->SetYdir(0.f);						// ibb�� ����
							static_cast<CIbb*>(m_pIbb)->SetYPos(-(rc.bottom - rc.top) + 1);		// ��ģ�κ� �о��
							if (rODir.x != 0)												// �̵��� ����
								static_cast<CIbb*>(m_pIbb)->SetXdir(rODir.x);
						}
					}
					else															// �߷��� ��������
					{
						if (rDir.y > 0.f)												// IBB�� �����ϸ�
						{															
							static_cast<CObb*>(m_pObb)->SetYdir(rDir.y);					// �����ض�
							static_cast<CObb*>(m_pObb)->SetYPos((rc.bottom - rc.top) - 1);
						}
						else															// ������ �ƴϸ�
						{
							static_cast<CObb*>(m_pObb)->SetYdir(0.f);					// OBB�� ����
							static_cast<CObb*>(m_pObb)->SetYPos((rc.bottom - rc.top) - 1);		// �о��ְ�
							static_cast<CObb*>(m_pObb)->SetCollison(0.f, D3DXVECTOR3(0.f, 0.f, 0.f), 0);
							if (rDir.x != 0)												// �̵��� ����
								static_cast<CObb*>(m_pObb)->SetXdir(rDir.x);
						}
					}
				}
				else															// OBB�� �����ְ�
				{
					if (static_cast<CIbb*>(m_pIbb)->GetGravity() > 0.f)				// �߷��� �Ʒ��� ����� ��
					{
						if (rDir.y < 0.f)												// IBB�� �����Ϸ���
						{
							static_cast<CObb*>(m_pObb)->SetYdir(rDir.y);						// �����ض�
							static_cast<CObb*>(m_pObb)->SetYPos(-(rc.bottom - rc.top) + 1);
						}
						else															// �����ϴ°� �ƴϸ�
						{
							static_cast<CObb*>(m_pObb)->SetYdir(0.f);						// Obb�� ����
							static_cast<CObb*>(m_pObb)->SetYPos(-(rc.bottom - rc.top) + 1);		// ��ģ�κ� �о��
							if (rDir.x != 0)												// �̵��� ����
								static_cast<CObb*>(m_pObb)->SetXdir(rDir.x);
						}
					}
					else															// �߷��� ��������
					{
						if (rODir.y > 0.f)												// OBB�� �����ϸ�
						{
							static_cast<CIbb*>(m_pIbb)->SetYdir(rODir.y);					// �����ض�
							static_cast<CIbb*>(m_pIbb)->SetYPos(rc.bottom-rc.top - 1);
						}
						else															// ������ �ƴϸ�
						{
							static_cast<CIbb*>(m_pIbb)->SetYdir(0.f);							// IBB�� ����
							static_cast<CIbb*>(m_pIbb)->SetYPos((rc.bottom - rc.top) - 1);		// �о��ְ�
							static_cast<CIbb*>(m_pIbb)->SetCollison(0.f, D3DXVECTOR3(0.f, 0.f, 0.f), 0);
							if (rODir.x != 0)												// �̵��� ����
								static_cast<CIbb*>(m_pIbb)->SetXdir(rODir.x);
						}
					}
				}
			}
		}
	}

	// IBB �浹ó��
	if (!(rDir.x == 0.f && rDir.y == 0.f))
	{
		RECT rc;
		////   ������ Ʈ�� ccd
		for (auto& tile : m_Objlist[OBJ_TRACK])
		{
			INFO&	tileInfo = tile->GetInfo();
			if (rDir.y != 0.f)// && tileInfo.vSize.x >= tileInfo.vSize.y)						// Ÿ���� �������ξֵ鸸 ccd
			{
				if (IntersectRect(&rc, &ccd, &(tile->GetRect())))
				{
					if (rc.right - rc.left <= 2) continue;								// �̹��������� �������
					float fDistance = rIbb.vPos.y - tileInfo.vPos.y;
					float fColTime = 0.f;
					if (fDistance < 0.f)												// Ʈ���� �ؿ�����
					{
						fDistance = ((int)tileInfo.vPos.y - (int)tileInfo.vSize.y / 2.f) - ((int)rIbb.vPos.y + (int)rIbb.vSize.y / 2.f);
						if (fDistance <= 0.f && rDir.y > 0.f)
						{
							static_cast<CIbb*>(m_pIbb)->SetYPos(fDistance);
							static_cast<CIbb*>(m_pIbb)->SetYdir(0.f);
							continue;
						}
						fColTime = fDistance / (rDir.y * 0.05f);
						if (0.17f > fColTime)
						{
							D3DXVECTOR3 vColPos = { (rIbb.vPos.x), (tileInfo.vPos.y - tileInfo.vSize.y / 2.f - rIbb.vSize.y / 2.f), 0.f };
							static_cast<CIbb*>(m_pIbb)->SetCollison(fColTime, vColPos, 0);
						}
					}
					else													// Ʈ���� ��������
					{
						fDistance = ((int)rIbb.vPos.y - (int)rIbb.vSize.y / 2.f) - ((int)tileInfo.vPos.y + (int)tileInfo.vSize.y / 2.f);
						if (fDistance <= 0.f && rDir.y < 0.f)
						{
							static_cast<CIbb*>(m_pIbb)->SetYPos(-fDistance);
							static_cast<CIbb*>(m_pIbb)->SetYdir(0.f);
							continue;
						}
						fColTime = fDistance / (rDir.y * -0.05f);
						if (0.17f > fColTime)
						{
							D3DXVECTOR3 vColPos = { (rIbb.vPos.x), (tileInfo.vPos.y + tileInfo.vSize.y / 2.f + rIbb.vSize.y / 2.f), 0.f };
							static_cast<CIbb*>(m_pIbb)->SetCollison(fColTime, vColPos, 0);
						}
					}
				}
			}
		}
		////   ������ Ʈ��
		for (auto& tile : m_Objlist[OBJ_TRACK])							// ������ Ÿ�� �Ϲ� �о�� �浹ó��
		{
			INFO&	tileInfo = tile->GetInfo();
			if (tileInfo.vSize.x < tileInfo.vSize.y)
			{
				if (IntersectRect(&rc, &ccdx, &(tile->GetRect())))
				{
					float fDistance = rIbb.vPos.x - tileInfo.vPos.x;
					float fColTime = 0.f;
					if (fDistance < 0.f)											// Ʈ���� �����ʿ�����
					{
						fDistance = ((int)tileInfo.vPos.x - (int)tileInfo.vSize.x / 2.f) - ((int)rIbb.vPos.x + (int)rIbb.vSize.x / 2.f);
						if (fDistance <= 0.f && rDir.x < 0.f)
						{
							continue;
						}
						fColTime = fDistance / (rDir.x * 0.05f);
						if (0.17f > fColTime)
						{
							static_cast<CIbb*>(m_pIbb)->SetXdir(0);
						}
					}
					else													// Ʈ���� ���ʿ�����
					{
						fDistance = ((int)rIbb.vPos.x - (int)rIbb.vSize.x / 2.f) - ((int)tileInfo.vPos.x + (int)tileInfo.vSize.x / 2.f);
						if (fDistance <= 0.f && rDir.x > 0.f)
						{
							continue;
						}
						fColTime = fDistance / (rDir.x * -0.05f);
						if (0.17f > fColTime)
						{
							static_cast<CIbb*>(m_pIbb)->SetXdir(0);
						}
					}
				}
			}
		}
		////   ����
		bool bCheck = false;
		for (auto& hole : m_Objlist[OBJ_HOLE])
		{
			INFO&	tileInfo = hole->GetInfo();
			if (rDir.y != 0.f && tileInfo.vSize.x >= tileInfo.vSize.y)						// Ÿ���� �������ξֵ鸸 ccd
			{
				if (IntersectRect(&rc, &ccd, &(hole->GetRect())))
				{
					float fDistance = rIbb.vPos.y - tileInfo.vPos.y;
					float fColTime = fDistance / (rDir.y * 0.05f);
					if (fDistance < 0.f)												// Ʈ���� �ؿ�����
					{
						static_cast<CIbb*>(m_pIbb)->SetHoleState(1);
						bCheck = true;
					}
					else													// Ʈ���� ��������
					{
						static_cast<CIbb*>(m_pIbb)->SetHoleState(2);
						bCheck = true;
					}
				}
			}
			else
			{
				if (IntersectRect(&rc, &ccdx, &(hole->GetRect())))
				{
					float fDistance = rIbb.vPos.x - tileInfo.vPos.x;
					float fColTime = 0.f;
					if (fDistance < 0.f)												// Ʈ���� �����ʿ�����
					{
						static_cast<CIbb*>(m_pIbb)->SetHoleState(3);
						bCheck = true;
					}
					else																// Ʈ���� ���ʿ�����
					{
						static_cast<CIbb*>(m_pIbb)->SetHoleState(4);
						bCheck = true;
					}
				}
			}
		}
		////  IBB ����
		for (auto& hole : m_Objlist[OBJ_IHOLE])
		{
			INFO&	tileInfo = hole->GetInfo();
			if (rDir.y != 0.f && tileInfo.vSize.x >= tileInfo.vSize.y)						// Ÿ���� �������ξֵ鸸 ccd
			{
				if (IntersectRect(&rc, &ccd, &(hole->GetRect())))
				{
					float fDistance = rIbb.vPos.y - tileInfo.vPos.y;
					float fColTime = fDistance / (rDir.y * 0.05f);
					if (fDistance < 0.f)												// Ʈ���� �ؿ�����
					{
						static_cast<CIbb*>(m_pIbb)->SetHoleState(1);
						bCheck = true;
					}
					else													// Ʈ���� ��������
					{
						static_cast<CIbb*>(m_pIbb)->SetHoleState(2);
						bCheck = true;
					}
				}
			}
			else
			{
				if (IntersectRect(&rc, &ccdx, &(hole->GetRect())))
				{
					float fDistance = rIbb.vPos.x - tileInfo.vPos.x;
					float fColTime = 0.f;
					if (fDistance < 0.f)												// Ʈ���� �����ʿ�����
					{
						static_cast<CIbb*>(m_pIbb)->SetHoleState(3);
						bCheck = true;
					}
					else																// Ʈ���� ���ʿ�����
					{
						static_cast<CIbb*>(m_pIbb)->SetHoleState(4);
						bCheck = true;
					}
				}
			}
		}
		////  OBB ����
		for (auto& hole : m_Objlist[OBJ_OHOLE])
		{
			INFO&	tileInfo = hole->GetInfo();
			if (tileInfo.vSize.x < tileInfo.vSize.y)
			{
				if (IntersectRect(&rc, &ccdx, &(hole->GetRect())))
				{
					float fDistance = rIbb.vPos.x - tileInfo.vPos.x;
					float fColTime = 0.f;
					if (fDistance < 0.f)											// Ʈ���� �����ʿ�����
					{
						fDistance = ((int)tileInfo.vPos.x - (int)tileInfo.vSize.x / 2.f) - ((int)rIbb.vPos.x + (int)rIbb.vSize.x / 2.f);
						if (fDistance <= 0.f && rDir.x < 0.f)
						{
							continue;
						}
						fColTime = fDistance / (rDir.x * 0.05f);
						if (0.17f > fColTime)
						{
							static_cast<CIbb*>(m_pIbb)->SetXdir(0);
						}
					}
					else													// Ʈ���� ���ʿ�����
					{
						fDistance = ((int)rIbb.vPos.x - (int)rIbb.vSize.x / 2.f) - ((int)tileInfo.vPos.x + (int)tileInfo.vSize.x / 2.f);
						if (fDistance <= 0.f && rDir.x > 0.f)
						{
							continue;
						}
						fColTime = fDistance / (rDir.x * -0.05f);
						if (0.17f > fColTime)
						{
							static_cast<CIbb*>(m_pIbb)->SetXdir(0);
						}
					}
				}
			}
			else
			{
				if (rDir.y != 0.f)// && tileInfo.vSize.x >= tileInfo.vSize.y)						// Ÿ���� �������ξֵ鸸 ccd
				{
					if (IntersectRect(&rc, &ccd, &(hole->GetRect())))
					{
						if (rc.right - rc.left <= 2) continue;								// �̹��������� �������
						float fDistance = rIbb.vPos.y - tileInfo.vPos.y;
						float fColTime = 0.f;
						if (fDistance < 0.f)												// Ʈ���� �ؿ�����
						{
							fDistance = ((int)tileInfo.vPos.y - (int)tileInfo.vSize.y / 2.f) - ((int)rIbb.vPos.y + (int)rIbb.vSize.y / 2.f);
							if (fDistance <= 0.f && rDir.y > 0.f)
							{
								static_cast<CIbb*>(m_pIbb)->SetYPos(fDistance);
								static_cast<CIbb*>(m_pIbb)->SetYdir(0.f);
								continue;
							}
							fColTime = fDistance / (rDir.y * 0.05f);
							if (0.17f > fColTime)
							{
								D3DXVECTOR3 vColPos = { (rIbb.vPos.x), (tileInfo.vPos.y - tileInfo.vSize.y / 2.f - rIbb.vSize.y / 2.f), 0.f };
								static_cast<CIbb*>(m_pIbb)->SetCollison(fColTime, vColPos, 0);
							}
						}
						else													// Ʈ���� ��������
						{
							fDistance = ((int)rIbb.vPos.y - (int)rIbb.vSize.y / 2.f) - ((int)tileInfo.vPos.y + (int)tileInfo.vSize.y / 2.f);
							if (fDistance <= 0.f && rDir.y < 0.f)
							{
								static_cast<CIbb*>(m_pIbb)->SetYPos(-fDistance);
								static_cast<CIbb*>(m_pIbb)->SetYdir(0.f);
								continue;
							}
							fColTime = fDistance / (rDir.y * -0.05f);
							if (0.17f > fColTime)
							{
								D3DXVECTOR3 vColPos = { (rIbb.vPos.x), (tileInfo.vPos.y + tileInfo.vSize.y / 2.f + rIbb.vSize.y / 2.f), 0.f };
								static_cast<CIbb*>(m_pIbb)->SetCollison(fColTime, vColPos, 0);
							}
						}
					}
				}
			}
		}
		if (!bCheck) static_cast<CIbb*>(m_pIbb)->SetHoleState(0);
		////   ����
		static_cast<CIbb*>(m_pIbb)->SetOnJump(0);	 // �ʱ�ȭ
		for (auto& jump : m_Objlist[OBJ_JUMP])
		{
			INFO&	tileInfo = jump->GetInfo();
			if (rDir.y != 0.f)// && tileInfo.vSize.x >= tileInfo.vSize.y)						// Ÿ���� �������ξֵ鸸 ccd
			{
				if (IntersectRect(&rc, &ccd, &(jump->GetRect())))
				{
					if (rc.right - rc.left <= 2) continue;								// �̹��������� �������
					float fDistance = rIbb.vPos.y - tileInfo.vPos.y;
					float fColTime = 0.f;
					if (fDistance < 0.f)												// Ʈ���� �ؿ�����
					{
						fDistance = ((int)tileInfo.vPos.y - (int)tileInfo.vSize.y / 2.f) - ((int)rIbb.vPos.y + (int)rIbb.vSize.y / 2.f);
						if (fDistance <= 0.f && rDir.y > 0.f)
						{
							static_cast<CIbb*>(m_pIbb)->SetYPos(fDistance);
							static_cast<CIbb*>(m_pIbb)->SetYdir(0.f);
							static_cast<CIbb*>(m_pIbb)->SetOnJump(1);
							continue;
						}
						fColTime = fDistance / (rDir.y * 0.05f);
						if (0.17f > fColTime)
						{
							if (static_cast<CObb*>(m_pObb)->GetOnJump()) static_cast<CObb*>(m_pObb)->SetYdir(rDir.y);
							D3DXVECTOR3 vColPos = { (rIbb.vPos.x), (tileInfo.vPos.y - tileInfo.vSize.y / 2.f - rIbb.vSize.y / 2.f), 0.f };
							static_cast<CIbb*>(m_pIbb)->SetCollison(fColTime, vColPos, 0);
							static_cast<CIbb*>(m_pIbb)->SetOnJump(1);
						}
						else if (0.5f > fColTime)
						{
							if (static_cast<CObb*>(m_pObb)->GetOnJump()) static_cast<CObb*>(m_pObb)->SetYdir(rDir.y);
						}
					}
					else													// Ʈ���� ��������
					{
						fDistance = ((int)rIbb.vPos.y - (int)rIbb.vSize.y / 2.f) - ((int)tileInfo.vPos.y + (int)tileInfo.vSize.y / 2.f);
						if (fDistance <= 0.f && rDir.y < 0.f)
						{
							static_cast<CIbb*>(m_pIbb)->SetYPos(-fDistance);
							static_cast<CIbb*>(m_pIbb)->SetYdir(0.f);
							static_cast<CIbb*>(m_pIbb)->SetOnJump(1);
							continue;
						}
						fColTime = fDistance / (rDir.y * -0.05f);
						if (0.17f > fColTime)
						{
							if (static_cast<CObb*>(m_pObb)->GetOnJump()) static_cast<CObb*>(m_pObb)->SetYdir(rDir.y);
							D3DXVECTOR3 vColPos = { (rIbb.vPos.x), (tileInfo.vPos.y + tileInfo.vSize.y / 2.f + rIbb.vSize.y / 2.f), 0.f };
							static_cast<CIbb*>(m_pIbb)->SetCollison(fColTime, vColPos, 0);
							static_cast<CIbb*>(m_pIbb)->SetOnJump(1);
						}
						else if( 0.5f > fColTime)
						{
							if (static_cast<CObb*>(m_pObb)->GetOnJump()) static_cast<CObb*>(m_pObb)->SetYdir(rDir.y);
						}
					}
				}
			}
		}
		//     ����
		for (auto& sup : m_Objlist[OBJ_SUPPORT])
		{
			INFO&	tileInfo = sup->GetInfo();
			if (static_cast<CIbb*>(m_pIbb)->GetGravity() > 0)				// �߷��� �Ʒ������϶�
			{
				if (IntersectRect(&rc, &ccd, &(sup->GetRect())))
				{
					if (rc.right - rc.left <= 3)	continue;								// �̹��������� �������
					if (rDir.y < 0.f)				continue;								// �÷��̾ �������� �̵��Ҷ�
					float fDistance = ((int)tileInfo.vPos.y - (int)tileInfo.vSize.y / 2.f) - ((int)rIbb.vPos.y + (int)rIbb.vSize.y / 2.f);	// ���ǸӸ��� �÷��̾� �� ���� �Ÿ�
					float fColTime = fDistance / (rDir.y * 0.05f);
					if (fDistance > 0.f)			// �Ÿ��� ������������
					{
						if (0.4f > fColTime)		// ���� �����̸�
						{
							D3DXVECTOR3 vColPos = { (rIbb.vPos.x), (tileInfo.vPos.y - tileInfo.vSize.y / 2.f - rIbb.vSize.y / 2.f), 0.f };
							static_cast<CIbb*>(m_pIbb)->SetCollison(fColTime, vColPos, 0);
						}
					}
					else if (fDistance == 0.f)		// ���������
					{
						static_cast<CIbb*>(m_pIbb)->SetYdir(0.f);
					}
					else							// ����������
					{
						if (-fDistance < rDir.y * GET_TIME)
						{
							static_cast<CIbb*>(m_pIbb)->SetYPos(fDistance);
							static_cast<CIbb*>(m_pIbb)->SetYdir(0.f);
							continue;
						}
					}
				}
			}
			else																// �߷��� �����϶�
			{
				if (IntersectRect(&rc, &ccd, &(sup->GetRect())))
				{
					if (rc.right - rc.left <= 3)	continue;								// �̹��������� �������
					if (rDir.y > 0.f)				continue;								// �÷��̾ �Ʒ������� �̵��Ҷ�
					float fDistance = ((int)rIbb.vPos.y - (int)rIbb.vSize.y / 2.f) -  ((int)tileInfo.vPos.y + (int)tileInfo.vSize.y / 2.f);	// ���ǸӸ��� �÷��̾� �� ���� �Ÿ�
					float fColTime = fDistance / (rDir.y * 0.05f);
					if (fDistance > 0.f)			// �Ÿ��� ������������
					{
						if (0.4f > fColTime)		// ���� �����̸�
						{
							D3DXVECTOR3 vColPos = { (rIbb.vPos.x), (tileInfo.vPos.y + tileInfo.vSize.y / 2.f + rIbb.vSize.y / 2.f), 0.f };
							static_cast<CIbb*>(m_pIbb)->SetCollison(fColTime, vColPos, 0);
						}
					}
					else if (fDistance == 0.f)		// ���������
					{
						static_cast<CIbb*>(m_pIbb)->SetYdir(0.f);
					}
					else							// ����������
					{
						if (-fDistance < rDir.y * GET_TIME)
						{
							static_cast<CIbb*>(m_pIbb)->SetYPos(fDistance);
							static_cast<CIbb*>(m_pIbb)->SetYdir(0.f);
							continue;
						}
					}
				}
			}
		}
	}

	// OBB �浹ó��
	if (!(rODir.x == 0.f && rODir.y == 0.f))
	{
		RECT rc;
		////   ������ Ʈ�� occd
		for (auto& tile : m_Objlist[OBJ_TRACK])
		{
			INFO&	tileInfo = tile->GetInfo();
			if (rODir.y != 0.f)// && tileInfo.vSize.x >= tileInfo.vSize.y)						// Ÿ���� �������ξֵ鸸 occd
			{
				if (IntersectRect(&rc, &occd, &(tile->GetRect())))
				{
					if (rc.right - rc.left <= 2) continue;								// �̹��������� �������
					float fDistance = rObb.vPos.y - tileInfo.vPos.y;
					float fColTime = 0.f;
					if (fDistance < 0.f)												// Ʈ���� �ؿ�����
					{
						fDistance = ((int)tileInfo.vPos.y - (int)tileInfo.vSize.y / 2.f) - ((int)rObb.vPos.y + (int)rObb.vSize.y / 2.f);
						if (fDistance <= 0.f && rODir.y > 0.f)
						{
							static_cast<CObb*>(m_pObb)->SetYPos(fDistance);
							static_cast<CObb*>(m_pObb)->SetYdir(0.f);
							continue;
						}
						fColTime = fDistance / (rODir.y * 0.05f);
						if (0.17f > fColTime)
						{
							D3DXVECTOR3 vColPos = { (rObb.vPos.x), (tileInfo.vPos.y - tileInfo.vSize.y / 2.f - rObb.vSize.y / 2.f), 0.f };
							static_cast<CObb*>(m_pObb)->SetCollison(fColTime, vColPos, 0);
						}
					}
					else													// Ʈ���� ��������
					{
						fDistance = ((int)rObb.vPos.y - (int)rObb.vSize.y / 2.f) - ((int)tileInfo.vPos.y + (int)tileInfo.vSize.y / 2.f);
						if (fDistance <= 0.f && rODir.y < 0.f)
						{
							static_cast<CObb*>(m_pObb)->SetYPos(-fDistance);
							static_cast<CObb*>(m_pObb)->SetYdir(0.f);
							continue;
						}
						fColTime = fDistance / (rODir.y * -0.05f);
						if (0.17f > fColTime)
						{
							D3DXVECTOR3 vColPos = { (rObb.vPos.x), (tileInfo.vPos.y + tileInfo.vSize.y / 2.f + rObb.vSize.y / 2.f), 0.f };
							static_cast<CObb*>(m_pObb)->SetCollison(fColTime, vColPos, 0);
						}
					}
				}
			}
		}
		////   ������ Ʈ��
		for (auto& tile : m_Objlist[OBJ_TRACK])							// ������ Ÿ�� �Ϲ� �о�� �浹ó��
		{
			INFO&	tileInfo = tile->GetInfo();
			if (tileInfo.vSize.x < tileInfo.vSize.y)
			{
				if (IntersectRect(&rc, &occdx, &(tile->GetRect())))
				{
					float fDistance = rObb.vPos.x - tileInfo.vPos.x;
					float fColTime = 0.f;
					if (fDistance < 0.f)											// Ʈ���� �����ʿ�����
					{
						fDistance = ((int)tileInfo.vPos.x - (int)tileInfo.vSize.x / 2.f) - ((int)rObb.vPos.x + (int)rObb.vSize.x / 2.f);
						if (fDistance <= 0.f && rODir.x < 0.f)
						{
							continue;
						}
						fColTime = fDistance / (rODir.x * 0.05f);
						if (0.17f > fColTime)
						{
							static_cast<CObb*>(m_pObb)->SetXdir(0);
						}
					}
					else													// Ʈ���� ���ʿ�����
					{
						fDistance = ((int)rObb.vPos.x - (int)rObb.vSize.x / 2.f) - ((int)tileInfo.vPos.x + (int)tileInfo.vSize.x / 2.f);
						if (fDistance <= 0.f && rODir.x > 0.f)
						{
							continue;
						}
						fColTime = fDistance / (rODir.x * -0.05f);
						if (0.17f > fColTime)
						{
							static_cast<CObb*>(m_pObb)->SetXdir(0);
						}
					}
				}
			}
		}
		////   ����
		bool bCheck = false;
		for (auto& hole : m_Objlist[OBJ_HOLE])
		{
			INFO&	tileInfo = hole->GetInfo();
			if (rODir.y != 0.f && tileInfo.vSize.x >= tileInfo.vSize.y)						// Ÿ���� �������ξֵ鸸 occd
			{
				if (IntersectRect(&rc, &occd, &(hole->GetRect())))
				{
					float fDistance = rObb.vPos.y - tileInfo.vPos.y;
					float fColTime = fDistance / (rODir.y * 0.05f);
					if (fDistance < 0.f)												// Ʈ���� �ؿ�����
					{
						static_cast<CObb*>(m_pObb)->SetHoleState(1);
						bCheck = true;
					}
					else													// Ʈ���� ��������
					{
						static_cast<CObb*>(m_pObb)->SetHoleState(2);
						bCheck = true;
					}
				}
			}
			else
			{
				if (IntersectRect(&rc, &occdx, &(hole->GetRect())))
				{
					float fDistance = rObb.vPos.x - tileInfo.vPos.x;
					float fColTime = 0.f;
					if (fDistance < 0.f)												// Ʈ���� �����ʿ�����
					{
						static_cast<CObb*>(m_pObb)->SetHoleState(3);
						bCheck = true;
					}
					else																// Ʈ���� ���ʿ�����
					{
						static_cast<CObb*>(m_pObb)->SetHoleState(4);
						bCheck = true;
					}
				}
			}
		}
		//  IBB ����
		for (auto& hole : m_Objlist[OBJ_IHOLE])
		{
			INFO&	tileInfo = hole->GetInfo();
			if (tileInfo.vSize.x < tileInfo.vSize.y)
			{
				if (IntersectRect(&rc, &occdx, &(hole->GetRect())))
				{
					float fDistance = rObb.vPos.x - tileInfo.vPos.x;
					float fColTime = 0.f;
					if (fDistance < 0.f)											// Ʈ���� �����ʿ�����
					{
						fDistance = ((int)tileInfo.vPos.x - (int)tileInfo.vSize.x / 2.f) - ((int)rObb.vPos.x + (int)rObb.vSize.x / 2.f);
						if (fDistance <= 0.f && rODir.x < 0.f)
						{
							continue;
						}
						fColTime = fDistance / (rODir.x * 0.05f);
						if (0.17f > fColTime)
						{
							static_cast<CObb*>(m_pObb)->SetXdir(0);
						}
					}
					else													// Ʈ���� ���ʿ�����
					{
						fDistance = ((int)rObb.vPos.x - (int)rObb.vSize.x / 2.f) - ((int)tileInfo.vPos.x + (int)tileInfo.vSize.x / 2.f);
						if (fDistance <= 0.f && rODir.x > 0.f)
						{
							continue;
						}
						fColTime = fDistance / (rODir.x * -0.05f);
						if (0.17f > fColTime)
						{
							static_cast<CIbb*>(m_pObb)->SetXdir(0);
						}
					}
				}
			}
			else
			{
				if (rODir.y != 0.f)// && tileInfo.vSize.x >= tileInfo.vSize.y)						// Ÿ���� �������ξֵ鸸 occd
				{
					if (IntersectRect(&rc, &occd, &(hole->GetRect())))
					{
						if (rc.right - rc.left <= 2) continue;								// �̹��������� �������
						float fDistance = rObb.vPos.y - tileInfo.vPos.y;
						float fColTime = 0.f;
						if (fDistance < 0.f)												// Ʈ���� �ؿ�����
						{
							fDistance = ((int)tileInfo.vPos.y - (int)tileInfo.vSize.y / 2.f) - ((int)rObb.vPos.y + (int)rObb.vSize.y / 2.f);
							if (fDistance <= 0.f && rODir.y > 0.f)
							{
								static_cast<CObb*>(m_pObb)->SetYPos(fDistance);
								static_cast<CObb*>(m_pObb)->SetYdir(0.f);
								continue;
							}
							fColTime = fDistance / (rODir.y * 0.05f);
							if (0.17f > fColTime)
							{
								D3DXVECTOR3 vColPos = { (rObb.vPos.x), (tileInfo.vPos.y - tileInfo.vSize.y / 2.f - rObb.vSize.y / 2.f), 0.f };
								static_cast<CObb*>(m_pObb)->SetCollison(fColTime, vColPos, 0);
							}
						}
						else													// Ʈ���� ��������
						{
							fDistance = ((int)rObb.vPos.y - (int)rObb.vSize.y / 2.f) - ((int)tileInfo.vPos.y + (int)tileInfo.vSize.y / 2.f);
							if (fDistance <= 0.f && rODir.y < 0.f)
							{
								static_cast<CObb*>(m_pObb)->SetYPos(-fDistance);
								static_cast<CObb*>(m_pObb)->SetYdir(0.f);
								continue;
							}
							fColTime = fDistance / (rODir.y * -0.05f);
							if (0.17f > fColTime)
							{
								D3DXVECTOR3 vColPos = { (rObb.vPos.x), (tileInfo.vPos.y + tileInfo.vSize.y / 2.f + rObb.vSize.y / 2.f), 0.f };
								static_cast<CObb*>(m_pObb)->SetCollison(fColTime, vColPos, 0);
							}
						}
					}
				}
			}
		}
		//  OBB ����
		for (auto& hole : m_Objlist[OBJ_OHOLE])
		{
			INFO&	tileInfo = hole->GetInfo();
			if (rODir.y != 0.f && tileInfo.vSize.x >= tileInfo.vSize.y)						// Ÿ���� �������ξֵ鸸 ccd
			{
				if (IntersectRect(&rc, &occdx, &(hole->GetRect())))
				{
					float fDistance = rObb.vPos.y - tileInfo.vPos.y;
					float fColTime = fDistance / (rODir.y * 0.05f);
					if (fDistance < 0.f)												// Ʈ���� �ؿ�����
					{
						static_cast<CObb*>(m_pObb)->SetHoleState(1);
						bCheck = true;
					}
					else													// Ʈ���� ��������
					{
						static_cast<CObb*>(m_pObb)->SetHoleState(2);
						bCheck = true;
					}
				}
			}
			else
			{
				if (IntersectRect(&rc, &occdx, &(hole->GetRect())))
				{
					float fDistance = rObb.vPos.x - tileInfo.vPos.x;
					float fColTime = 0.f;
					if (fDistance < 0.f)												// Ʈ���� �����ʿ�����
					{
						static_cast<CObb*>(m_pObb)->SetHoleState(3);
						bCheck = true;
					}
					else																// Ʈ���� ���ʿ�����
					{
						static_cast<CObb*>(m_pObb)->SetHoleState(4);
						bCheck = true;
					}
				}
			}
		}
		if (!bCheck) static_cast<CObb*>(m_pObb)->SetHoleState(0);
		////   ����
		static_cast<CObb*>(m_pObb)->SetOnJump(0);	 // �ʱ�ȭ
		for (auto& jump : m_Objlist[OBJ_JUMP])
		{
			INFO&	tileInfo = jump->GetInfo();
			if (rODir.y != 0.f)// && tileInfo.vSize.x >= tileInfo.vSize.y)						// Ÿ���� �������ξֵ鸸 occd
			{
				if (IntersectRect(&rc, &occd, &(jump->GetRect())))
				{
					if (rc.right - rc.left <= 2) continue;								// �̹��������� �������
					float fDistance = rObb.vPos.y - tileInfo.vPos.y;
					float fColTime = 0.f;
					if (fDistance < 0.f)												// Ʈ���� �ؿ�����
					{
						fDistance = ((int)tileInfo.vPos.y - (int)tileInfo.vSize.y / 2.f) - ((int)rObb.vPos.y + (int)rObb.vSize.y / 2.f);
						if (fDistance <= 0.f && rODir.y > 0.f)
						{
							static_cast<CObb*>(m_pObb)->SetYPos(fDistance);
							static_cast<CObb*>(m_pObb)->SetYdir(0.f);
							static_cast<CObb*>(m_pObb)->SetOnJump(1);
							continue;
						}
						fColTime = fDistance / (rODir.y * 0.05f);
						if (0.17f > fColTime)
						{
							if (static_cast<CIbb*>(m_pIbb)->GetOnJump()) static_cast<CIbb*>(m_pIbb)->SetYdir(rODir.y);
							D3DXVECTOR3 vColPos = { (rObb.vPos.x), (tileInfo.vPos.y - tileInfo.vSize.y / 2.f - rObb.vSize.y / 2.f), 0.f };
							static_cast<CObb*>(m_pObb)->SetCollison(fColTime, vColPos, 0);
							static_cast<CObb*>(m_pObb)->SetOnJump(1);
						}
						else if (0.5f > fColTime)
						{
							if (static_cast<CIbb*>(m_pIbb)->GetOnJump()) static_cast<CIbb*>(m_pIbb)->SetYdir(rODir.y);
						}
					}
					else													// Ʈ���� ��������
					{
						fDistance = ((int)rObb.vPos.y - (int)rObb.vSize.y / 2.f) - ((int)tileInfo.vPos.y + (int)tileInfo.vSize.y / 2.f);
						if (fDistance <= 0.f && rODir.y < 0.f)
						{
							static_cast<CObb*>(m_pObb)->SetYPos(-fDistance);
							static_cast<CObb*>(m_pObb)->SetYdir(0.f);
							static_cast<CObb*>(m_pObb)->SetOnJump(1);
							continue;
						}
						fColTime = fDistance / (rODir.y * -0.05f);
						if (0.17f > fColTime)
						{
							if (static_cast<CIbb*>(m_pIbb)->GetOnJump()) static_cast<CIbb*>(m_pIbb)->SetYdir(rODir.y);
							D3DXVECTOR3 vColPos = { (rObb.vPos.x), (tileInfo.vPos.y + tileInfo.vSize.y / 2.f + rObb.vSize.y / 2.f), 0.f };
							static_cast<CObb*>(m_pObb)->SetCollison(fColTime, vColPos, 0);
							static_cast<CObb*>(m_pObb)->SetOnJump(1);
						}
						else if (0.5f > fColTime)
						{
							if (static_cast<CIbb*>(m_pIbb)->GetOnJump()) static_cast<CIbb*>(m_pIbb)->SetYdir(rODir.y);
						}
					}
				}
			}
		}
		//     ����
		for (auto& sup : m_Objlist[OBJ_SUPPORT])
		{
			INFO&	tileInfo = sup->GetInfo();
			if (static_cast<CObb*>(m_pObb)->GetGravity() > 0)				// �߷��� �Ʒ������϶�
			{
				if (IntersectRect(&rc, &occd, &(sup->GetRect())))
				{
					if (rc.right - rc.left <= 3)	continue;								// �̹��������� �������
					if (rODir.y < 0.f)				continue;								// �÷��̾ �������� �̵��Ҷ�
					float fDistance = ((int)tileInfo.vPos.y - (int)tileInfo.vSize.y / 2.f) - ((int)rObb.vPos.y + (int)rObb.vSize.y / 2.f);	// ���ǸӸ��� �÷��̾� �� ���� �Ÿ�
					float fColTime = fDistance / (rODir.y * 0.05f);
					if (fDistance > 0.f)			// �Ÿ��� ������������
					{
						if (0.4f > fColTime)		// ���� �����̸�
						{
							D3DXVECTOR3 vColPos = { (rObb.vPos.x), (tileInfo.vPos.y - tileInfo.vSize.y / 2.f - rObb.vSize.y / 2.f), 0.f };
							static_cast<CObb*>(m_pObb)->SetCollison(fColTime, vColPos, 0);
						}
					}
					else if (fDistance == 0.f)		// ���������
					{
						static_cast<CObb*>(m_pObb)->SetYdir(0.f);
					}
					else							// ����������
					{
						if (-fDistance < rODir.y * GET_TIME)
						{
							static_cast<CObb*>(m_pObb)->SetYPos(fDistance);
							static_cast<CObb*>(m_pObb)->SetYdir(0.f);
							continue;
						}
					}
				}
			}
			else																// �߷��� �����϶�
			{
				if (IntersectRect(&rc, &occd, &(sup->GetRect())))
				{
					if (rc.right - rc.left <= 3)	continue;								// �̹��������� �������
					if (rODir.y > 0.f)				continue;								// �÷��̾ �Ʒ������� �̵��Ҷ�
					float fDistance = ((int)rObb.vPos.y - (int)rObb.vSize.y / 2.f) - ((int)tileInfo.vPos.y + (int)tileInfo.vSize.y / 2.f);	// ���ǸӸ��� �÷��̾� �� ���� �Ÿ�
					float fColTime = fDistance / (rODir.y * 0.05f);
					if (fDistance > 0.f)			// �Ÿ��� ������������
					{
						if (0.4f > fColTime)		// ���� �����̸�
						{
							D3DXVECTOR3 vColPos = { (rObb.vPos.x), (tileInfo.vPos.y + tileInfo.vSize.y / 2.f + rObb.vSize.y / 2.f), 0.f };
							static_cast<CObb*>(m_pObb)->SetCollison(fColTime, vColPos, 0);
						}
					}
					else if (fDistance == 0.f)		// ���������
					{
						static_cast<CObb*>(m_pObb)->SetYdir(0.f);
					}
					else							// ����������
					{
						if (-fDistance < rODir.y * GET_TIME)
						{
							static_cast<CObb*>(m_pObb)->SetYPos(fDistance);
							static_cast<CObb*>(m_pObb)->SetYdir(0.f);
							continue;
						}
					}
				}
			}
		}
	}

}

int CLobby::Progress(void)
{
	int iResult = 0;

	CollisionCheck();

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		list<CObj*>::iterator iter = m_Objlist[i].begin();
		list<CObj*>::iterator iter_end = m_Objlist[i].end();
		for (iter; iter != iter_end;)
		{
			iResult = (*iter)->Progress();
			if (iResult == 1)
			{
				Safe_Delete((*iter));
				m_Objlist[i].erase(iter);
			}

			if (iter == iter_end)	break;
			else					++iter;
		}
	}
	return 0;
}

void CLobby::Render(void)
{
	for (auto& map2 : m_Objlist[OBJ_MAPRECT])
		static_cast<CMaprect*>(map2)->Render(0);

	for (auto& bobj : m_Objlist[OBJ_BACKOBJ])
		bobj->Render();

	RenderBack();
	
	for (size_t i = 0; i < OBJ_MAPRECT; ++i)
		for (auto& obj : m_Objlist[i])
			obj->Render();

	for (size_t i = OBJ_SUPPORT; i < OBJ_END; ++i)
		for (auto& obj : m_Objlist[i])
			obj->Render();


}

void CLobby::Release(void)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& obj : m_Objlist[i])
			Safe_Delete(obj);
		m_Objlist[i].clear();
	}
}

void CLobby::LoadData(void)
{
	HANDLE	hFile = CreateFile(L"../Data/Lobby.dat",
		GENERIC_READ,
		0,
		nullptr,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	DWORD		dwByte = 0;
	tRECT		tempRT;
	bOBJ		tempBO;
	SUP			tempSP;
	MON			tempMON;
	
	// MAPRECT
	{
		int iCount = 0;
		ReadFile(hFile, &iCount, sizeof(int), &dwByte, nullptr);
		for (int i = 0; i < iCount; ++i)
		{
			ReadFile(hFile, &tempRT, sizeof(tRECT), &dwByte, nullptr);
			CObj*	ptemp = new CMaprect;
			INFO&	tInfo = ptemp->GetInfo();
			tInfo.vPos  = tempRT.vPos;
			tInfo.vSize = tempRT.vSize;
			tInfo.iType = (UINT)OBJ_MAPRECT;
			lstrcpyW(ptemp->GetInfo().ObjKey, L"MAP");
			lstrcpyW(ptemp->GetInfo().StateKey, L"Map");
			ptemp->Initialize();
			m_Objlist[OBJ_MAPRECT].push_back(ptemp);
		}
	}
	// TRACK
	{
		int iCount = 0;
		ReadFile(hFile, &iCount, sizeof(int), &dwByte, nullptr);
		for (int j = 0; j < iCount; ++j)
		{
			ReadFile(hFile, &tempRT, sizeof(tRECT), &dwByte, nullptr);
			CObj*	ptemp = new CTrack;
			INFO&	tInfo = ptemp->GetInfo();
			tInfo.vPos = tempRT.vPos;
			tInfo.vSize = tempRT.vSize;
			tInfo.iType = (UINT)OBJ_TRACK;
			lstrcpyW(ptemp->GetInfo().ObjKey, L"MAP");
			lstrcpyW(ptemp->GetInfo().StateKey, L"Track");
			ptemp->Initialize();
			m_Objlist[OBJ_TRACK].push_back(ptemp);
		}
	}
	// HOLE
	{
		int iCount = 0;
		ReadFile(hFile, &iCount, sizeof(int), &dwByte, nullptr);
		for (int j = 0; j < iCount; ++j)
		{
			ReadFile(hFile, &tempRT, sizeof(tRECT), &dwByte, nullptr);
			CObj*	ptemp = new CHole;
			INFO&	tInfo = ptemp->GetInfo();
			tInfo.vPos = tempRT.vPos;
			tInfo.vSize = tempRT.vSize;
			tInfo.iType = (UINT)OBJ_HOLE;
			lstrcpyW(ptemp->GetInfo().ObjKey, L"MAP");
			lstrcpyW(ptemp->GetInfo().StateKey, L"Hole");
			ptemp->Initialize();
			m_Objlist[OBJ_HOLE].push_back(ptemp);
		}
	}
	// Ibb HOle
	{
		int iCount = 0;
		ReadFile(hFile, &iCount, sizeof(int), &dwByte, nullptr);
		for (int j = 0; j < iCount; ++j)
		{
			ReadFile(hFile, &tempRT, sizeof(tRECT), &dwByte, nullptr);
			CObj*	ptemp = new CIHole;
			INFO&	tInfo = ptemp->GetInfo();
			tInfo.vPos = tempRT.vPos;
			tInfo.vSize = tempRT.vSize;
			tInfo.iType = (UINT)OBJ_IHOLE;
			lstrcpyW(ptemp->GetInfo().ObjKey, L"MAP");
			lstrcpyW(ptemp->GetInfo().StateKey, L"IHole");
			ptemp->Initialize();
			m_Objlist[OBJ_IHOLE].push_back(ptemp);
		}
	}	
	// Obb HOle
	{
		int iCount = 0;
		ReadFile(hFile, &iCount, sizeof(int), &dwByte, nullptr);
		for (int j = 0; j < iCount; ++j)
		{
			ReadFile(hFile, &tempRT, sizeof(tRECT), &dwByte, nullptr);
			CObj*	ptemp = new COHole;
			INFO&	tInfo = ptemp->GetInfo();
			tInfo.vPos = tempRT.vPos;
			tInfo.vSize = tempRT.vSize;
			tInfo.iType = (UINT)OBJ_OHOLE;
			lstrcpyW(ptemp->GetInfo().ObjKey, L"MAP");
			lstrcpyW(ptemp->GetInfo().StateKey, L"OHole");
			ptemp->Initialize();
			m_Objlist[OBJ_OHOLE].push_back(ptemp);
		}
	}
	// Jump
	{
		int iCount = 0;
		ReadFile(hFile, &iCount, sizeof(int), &dwByte, nullptr);
		for (int j = 0; j < iCount; ++j)
		{
			ReadFile(hFile, &tempRT, sizeof(tRECT), &dwByte, nullptr);
			CObj*	ptemp = new CJump;
			INFO&	tInfo = ptemp->GetInfo();
			tInfo.vPos = tempRT.vPos;
			tInfo.vSize = tempRT.vSize;
			tInfo.iType = (UINT)OBJ_JUMP;
			lstrcpyW(ptemp->GetInfo().ObjKey, L"MAP");
			lstrcpyW(ptemp->GetInfo().StateKey, L"Jump");
			ptemp->Initialize();
			m_Objlist[OBJ_JUMP].push_back(ptemp);
		}
	}
	// BackGround OBj
	{
		int iCount = 0;
		ReadFile(hFile, &iCount, sizeof(int), &dwByte, nullptr);
		for (int i = 0; i < iCount; ++i)
		{
			ReadFile(hFile, &tempBO, sizeof(bOBJ), &dwByte, nullptr);
			CObj*	ptemp = new CBackobj;
			INFO& tInfo = ptemp->GetInfo();
			tInfo.vPos = tempBO.vPos;
			tInfo.vScale = tempBO.vScale;
			tInfo.iType = tempBO.iDrawID;
			lstrcpyW(ptemp->GetInfo().ObjKey, L"MAP");
			lstrcpyW(ptemp->GetInfo().StateKey, L"Fixed");
			ptemp->Initialize();
			m_Objlist[OBJ_BACKOBJ].push_back(ptemp);
		}
	}
	int itemp = 0;
	ReadFile(hFile, &itemp, sizeof(int), &dwByte, nullptr);
	// Support
	for (size_t i = 0; i < SP_END; ++i)
	{
		int iCount = 0;
		ReadFile(hFile, &iCount, sizeof(int), &dwByte, nullptr);
		for (int j = 0; j < iCount; ++j)
		{
			CObj*	ptemp = new CSupport;
			ReadFile(hFile, &tempSP, sizeof(SUP), &dwByte, nullptr);
			INFO& tInfo = ptemp->GetInfo();
			tInfo.vPos = tempSP.vPos;
			tInfo.vScale = tempSP.vScale;
			tInfo.iType = (UINT)tempSP.eType;
			lstrcpyW(ptemp->GetInfo().ObjKey, L"MONSTER");
			lstrcpyW(ptemp->GetInfo().StateKey, L"Support");
			ptemp->Initialize();
			m_Objlist[OBJ_SUPPORT].push_back(ptemp);
		}
	}
	// Monster
	{
		int iCount = 0;
		ReadFile(hFile, &iCount, sizeof(int), &dwByte, nullptr);
		for (int j = 0; j < iCount; ++j)
		{
			CObj*	ptemp = new CMonster;
			ReadFile(hFile, &tempMON, sizeof(MON), &dwByte, nullptr);
			INFO& tInfo = ptemp->GetInfo();
			tInfo.vPos = tempMON.vPos;
			tInfo.vScale = tempMON.vScale;
			tInfo.iType =  (UINT)tempMON.eType;
			lstrcpyW(ptemp->GetInfo().ObjKey, L"MONSTER");
			lstrcpyW(ptemp->GetInfo().StateKey, L"Enemy");
			ptemp->Initialize();
			m_Objlist[OBJ_MONSTER].push_back(ptemp);
		}
	}
	CloseHandle(hFile);
}

void CLobby::RenderBack(void)
{
	CDevice*	m_pDevice = CDevice::GetInstance();

	D3DXMATRIX		matWorld, matScale, matTrans;
	RECT			rc;
	const TEXINFO*	pTexture = CTextureMgr::GetInstance()->GetTexture(L"MAP", L"Map", 0);
	for (int i = 0; i < 30; ++i)
	{
		m_pDevice->GetSprite()->End();
		m_pDevice->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
		m_pDevice->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pDevice->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVDESTALPHA);
		m_pDevice->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTALPHA);
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixTranslation(&matTrans, i*(MAPX / 30) + 40 + g_vScroll.x, MAPY / 2 + g_vScroll.y, 0.f);
		D3DXMatrixScaling(&matScale, g_vZoom.x, g_vZoom.y, 0.f);
		matWorld = matTrans * matScale;
		m_pDevice->GetSprite()->SetTransform(&matWorld);
		rc = {
			LONG(i*(MAPX / 30)),
			LONG(0),
			LONG((i + 1)*(MAPX / 30)),
			LONG(MAPY),
		};
		m_pDevice->GetSprite()->Draw(
			pTexture->pTexture,
			&rc,
			&D3DXVECTOR3((MAPX / 30) / 2.f, MAPY/2.f, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 50, 50, 50));
		m_pDevice->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		m_pDevice->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

		m_pDevice->GetSprite()->End();
		m_pDevice->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
	}

}

