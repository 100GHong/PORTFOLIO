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

	// IBB 충돌렉트 생성
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
	// OBB 충돌렉트 생성
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

	// IBB <-> OBB 충돌
	if (!(rDir.x == 0.f && rDir.y == 0 && rODir.x == 0 && rDir.y == 0))
	{
		RECT rc;
		// 나머지 충돌
		if (IntersectRect(&rc, &m_pIbb->GetRect(), &m_pObb->GetRect()))
		{
			// 좌, 우 충돌
			if (rc.right - rc.left < rc.bottom - rc.top)
			{
				if ((m_pIbb->GetInfo().vPos.x - m_pObb->GetInfo().vPos.x < 0 && rDir.x > 0.f && rODir.x < 0.f) ||		// 서로 밀어낼때
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
				else if (rDir.x == 0)											// OBB만 움직이는 경우
				{
					if (((m_pIbb->GetInfo().vPos.x - m_pObb->GetInfo().vPos.x) > 0.f && rODir.x > 0.f) ||	// OBB가 IBB쪽으로 움직일때 멈추기
						(m_pIbb->GetInfo().vPos.x - m_pObb->GetInfo().vPos.x < 0.f && rODir.x < 0.f) )
					{
						static_cast<CObb*>(m_pObb)->SetXdir(0.f);
					}
				}
				else if (rODir.x == 0)									// IBB만 움직이는 경우
				{
					if (((m_pIbb->GetInfo().vPos.x - m_pObb->GetInfo().vPos.x) > 0.f && rDir.x < 0.f) ||	// IBB가 OBB쪽으로 움직일때 멈추기
						(m_pIbb->GetInfo().vPos.x - m_pObb->GetInfo().vPos.x < 0.f && rDir.x > 0.f))
					{
						static_cast<CIbb*>(m_pIbb)->SetXdir(0.f);
					}
				}
			}
			// 상, 하 충돌
			else
			{
				if (m_pIbb->GetInfo().vPos.y < m_pObb->GetInfo().vPos.y)			// IBB가 위에있고
				{
					static_cast<CIbb*>(m_pIbb)->SetOnObb();
					static_cast<CObb*>(m_pObb)->SetOnIbb();
					if (static_cast<CObb*>(m_pObb)->GetGravity() > 0.f)				// 중력은 아래로 적용될 때
					{
						if (rODir.y < 0.f)											// OBB가 점프하려면
						{
							static_cast<CIbb*>(m_pIbb)->SetYdir(rODir.y);					// 같이해라
							static_cast<CIbb*>(m_pIbb)->SetYPos(-(rc.bottom - rc.top) + 1);
						}
						else															// 점프하는게 아니면
						{
							static_cast<CIbb*>(m_pIbb)->SetYdir(0.f);						// ibb도 멈춰
							static_cast<CIbb*>(m_pIbb)->SetYPos(-(rc.bottom - rc.top) + 1);		// 겹친부분 밀어내기
							if (rODir.x != 0)												// 이동은 같이
								static_cast<CIbb*>(m_pIbb)->SetXdir(rODir.x);
						}
					}
					else															// 중력은 위쪽으로
					{
						if (rDir.y > 0.f)												// IBB가 점프하면
						{															
							static_cast<CObb*>(m_pObb)->SetYdir(rDir.y);					// 같이해라
							static_cast<CObb*>(m_pObb)->SetYPos((rc.bottom - rc.top) - 1);
						}
						else															// 점프가 아니면
						{
							static_cast<CObb*>(m_pObb)->SetYdir(0.f);					// OBB도 멈춰
							static_cast<CObb*>(m_pObb)->SetYPos((rc.bottom - rc.top) - 1);		// 밀어주고
							static_cast<CObb*>(m_pObb)->SetCollison(0.f, D3DXVECTOR3(0.f, 0.f, 0.f), 0);
							if (rDir.x != 0)												// 이동은 같이
								static_cast<CObb*>(m_pObb)->SetXdir(rDir.x);
						}
					}
				}
				else															// OBB가 위에있고
				{
					if (static_cast<CIbb*>(m_pIbb)->GetGravity() > 0.f)				// 중력은 아래로 적용될 때
					{
						if (rDir.y < 0.f)												// IBB가 점프하려면
						{
							static_cast<CObb*>(m_pObb)->SetYdir(rDir.y);						// 같이해라
							static_cast<CObb*>(m_pObb)->SetYPos(-(rc.bottom - rc.top) + 1);
						}
						else															// 점프하는게 아니면
						{
							static_cast<CObb*>(m_pObb)->SetYdir(0.f);						// Obb도 멈춰
							static_cast<CObb*>(m_pObb)->SetYPos(-(rc.bottom - rc.top) + 1);		// 겹친부분 밀어내기
							if (rDir.x != 0)												// 이동은 같이
								static_cast<CObb*>(m_pObb)->SetXdir(rDir.x);
						}
					}
					else															// 중력은 위쪽으로
					{
						if (rODir.y > 0.f)												// OBB가 점프하면
						{
							static_cast<CIbb*>(m_pIbb)->SetYdir(rODir.y);					// 같이해라
							static_cast<CIbb*>(m_pIbb)->SetYPos(rc.bottom-rc.top - 1);
						}
						else															// 점프가 아니면
						{
							static_cast<CIbb*>(m_pIbb)->SetYdir(0.f);							// IBB도 멈춰
							static_cast<CIbb*>(m_pIbb)->SetYPos((rc.bottom - rc.top) - 1);		// 밀어주고
							static_cast<CIbb*>(m_pIbb)->SetCollison(0.f, D3DXVECTOR3(0.f, 0.f, 0.f), 0);
							if (rODir.x != 0)												// 이동은 같이
								static_cast<CIbb*>(m_pIbb)->SetXdir(rODir.x);
						}
					}
				}
			}
		}
	}

	// IBB 충돌처리
	if (!(rDir.x == 0.f && rDir.y == 0.f))
	{
		RECT rc;
		////   가로형 트랙 ccd
		for (auto& tile : m_Objlist[OBJ_TRACK])
		{
			INFO&	tileInfo = tile->GetInfo();
			if (rDir.y != 0.f)// && tileInfo.vSize.x >= tileInfo.vSize.y)						// 타일이 가로형인애들만 ccd
			{
				if (IntersectRect(&rc, &ccd, &(tile->GetRect())))
				{
					if (rc.right - rc.left <= 2) continue;								// 이미지사이즈 찡김방지
					float fDistance = rIbb.vPos.y - tileInfo.vPos.y;
					float fColTime = 0.f;
					if (fDistance < 0.f)												// 트랙이 밑에있음
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
					else													// 트랙이 위에있음
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
		////   세로형 트랙
		for (auto& tile : m_Objlist[OBJ_TRACK])							// 세로형 타일 일반 밀어내기 충돌처리
		{
			INFO&	tileInfo = tile->GetInfo();
			if (tileInfo.vSize.x < tileInfo.vSize.y)
			{
				if (IntersectRect(&rc, &ccdx, &(tile->GetRect())))
				{
					float fDistance = rIbb.vPos.x - tileInfo.vPos.x;
					float fColTime = 0.f;
					if (fDistance < 0.f)											// 트랙이 오른쪽에있음
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
					else													// 트랙이 왼쪽에있음
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
		////   구멍
		bool bCheck = false;
		for (auto& hole : m_Objlist[OBJ_HOLE])
		{
			INFO&	tileInfo = hole->GetInfo();
			if (rDir.y != 0.f && tileInfo.vSize.x >= tileInfo.vSize.y)						// 타일이 가로형인애들만 ccd
			{
				if (IntersectRect(&rc, &ccd, &(hole->GetRect())))
				{
					float fDistance = rIbb.vPos.y - tileInfo.vPos.y;
					float fColTime = fDistance / (rDir.y * 0.05f);
					if (fDistance < 0.f)												// 트랙이 밑에있음
					{
						static_cast<CIbb*>(m_pIbb)->SetHoleState(1);
						bCheck = true;
					}
					else													// 트랙이 위에있음
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
					if (fDistance < 0.f)												// 트랙이 오른쪽에있음
					{
						static_cast<CIbb*>(m_pIbb)->SetHoleState(3);
						bCheck = true;
					}
					else																// 트랙이 왼쪽에있음
					{
						static_cast<CIbb*>(m_pIbb)->SetHoleState(4);
						bCheck = true;
					}
				}
			}
		}
		////  IBB 구멍
		for (auto& hole : m_Objlist[OBJ_IHOLE])
		{
			INFO&	tileInfo = hole->GetInfo();
			if (rDir.y != 0.f && tileInfo.vSize.x >= tileInfo.vSize.y)						// 타일이 가로형인애들만 ccd
			{
				if (IntersectRect(&rc, &ccd, &(hole->GetRect())))
				{
					float fDistance = rIbb.vPos.y - tileInfo.vPos.y;
					float fColTime = fDistance / (rDir.y * 0.05f);
					if (fDistance < 0.f)												// 트랙이 밑에있음
					{
						static_cast<CIbb*>(m_pIbb)->SetHoleState(1);
						bCheck = true;
					}
					else													// 트랙이 위에있음
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
					if (fDistance < 0.f)												// 트랙이 오른쪽에있음
					{
						static_cast<CIbb*>(m_pIbb)->SetHoleState(3);
						bCheck = true;
					}
					else																// 트랙이 왼쪽에있음
					{
						static_cast<CIbb*>(m_pIbb)->SetHoleState(4);
						bCheck = true;
					}
				}
			}
		}
		////  OBB 구멍
		for (auto& hole : m_Objlist[OBJ_OHOLE])
		{
			INFO&	tileInfo = hole->GetInfo();
			if (tileInfo.vSize.x < tileInfo.vSize.y)
			{
				if (IntersectRect(&rc, &ccdx, &(hole->GetRect())))
				{
					float fDistance = rIbb.vPos.x - tileInfo.vPos.x;
					float fColTime = 0.f;
					if (fDistance < 0.f)											// 트랙이 오른쪽에있음
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
					else													// 트랙이 왼쪽에있음
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
				if (rDir.y != 0.f)// && tileInfo.vSize.x >= tileInfo.vSize.y)						// 타일이 가로형인애들만 ccd
				{
					if (IntersectRect(&rc, &ccd, &(hole->GetRect())))
					{
						if (rc.right - rc.left <= 2) continue;								// 이미지사이즈 찡김방지
						float fDistance = rIbb.vPos.y - tileInfo.vPos.y;
						float fColTime = 0.f;
						if (fDistance < 0.f)												// 트랙이 밑에있음
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
						else													// 트랙이 위에있음
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
		////   점프
		static_cast<CIbb*>(m_pIbb)->SetOnJump(0);	 // 초기화
		for (auto& jump : m_Objlist[OBJ_JUMP])
		{
			INFO&	tileInfo = jump->GetInfo();
			if (rDir.y != 0.f)// && tileInfo.vSize.x >= tileInfo.vSize.y)						// 타일이 가로형인애들만 ccd
			{
				if (IntersectRect(&rc, &ccd, &(jump->GetRect())))
				{
					if (rc.right - rc.left <= 2) continue;								// 이미지사이즈 찡김방지
					float fDistance = rIbb.vPos.y - tileInfo.vPos.y;
					float fColTime = 0.f;
					if (fDistance < 0.f)												// 트랙이 밑에있음
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
					else													// 트랙이 위에있음
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
		//     발판
		for (auto& sup : m_Objlist[OBJ_SUPPORT])
		{
			INFO&	tileInfo = sup->GetInfo();
			if (static_cast<CIbb*>(m_pIbb)->GetGravity() > 0)				// 중력이 아래방향일때
			{
				if (IntersectRect(&rc, &ccd, &(sup->GetRect())))
				{
					if (rc.right - rc.left <= 3)	continue;								// 이미지사이즈 찡김방지
					if (rDir.y < 0.f)				continue;								// 플레이어가 위쪽으로 이동할때
					float fDistance = ((int)tileInfo.vPos.y - (int)tileInfo.vSize.y / 2.f) - ((int)rIbb.vPos.y + (int)rIbb.vSize.y / 2.f);	// 발판머리와 플레이어 발 사이 거리
					float fColTime = fDistance / (rDir.y * 0.05f);
					if (fDistance > 0.f)			// 거리가 벌어져있으면
					{
						if (0.4f > fColTime)		// 박을 예정이면
						{
							D3DXVECTOR3 vColPos = { (rIbb.vPos.x), (tileInfo.vPos.y - tileInfo.vSize.y / 2.f - rIbb.vSize.y / 2.f), 0.f };
							static_cast<CIbb*>(m_pIbb)->SetCollison(fColTime, vColPos, 0);
						}
					}
					else if (fDistance == 0.f)		// 닿아있으면
					{
						static_cast<CIbb*>(m_pIbb)->SetYdir(0.f);
					}
					else							// 겹쳐있으면
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
			else																// 중력이 위쪽일때
			{
				if (IntersectRect(&rc, &ccd, &(sup->GetRect())))
				{
					if (rc.right - rc.left <= 3)	continue;								// 이미지사이즈 찡김방지
					if (rDir.y > 0.f)				continue;								// 플레이어가 아래쪽으로 이동할때
					float fDistance = ((int)rIbb.vPos.y - (int)rIbb.vSize.y / 2.f) -  ((int)tileInfo.vPos.y + (int)tileInfo.vSize.y / 2.f);	// 발판머리와 플레이어 발 사이 거리
					float fColTime = fDistance / (rDir.y * 0.05f);
					if (fDistance > 0.f)			// 거리가 벌어져있으면
					{
						if (0.4f > fColTime)		// 박을 예정이면
						{
							D3DXVECTOR3 vColPos = { (rIbb.vPos.x), (tileInfo.vPos.y + tileInfo.vSize.y / 2.f + rIbb.vSize.y / 2.f), 0.f };
							static_cast<CIbb*>(m_pIbb)->SetCollison(fColTime, vColPos, 0);
						}
					}
					else if (fDistance == 0.f)		// 닿아있으면
					{
						static_cast<CIbb*>(m_pIbb)->SetYdir(0.f);
					}
					else							// 겹쳐있으면
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

	// OBB 충돌처리
	if (!(rODir.x == 0.f && rODir.y == 0.f))
	{
		RECT rc;
		////   가로형 트랙 occd
		for (auto& tile : m_Objlist[OBJ_TRACK])
		{
			INFO&	tileInfo = tile->GetInfo();
			if (rODir.y != 0.f)// && tileInfo.vSize.x >= tileInfo.vSize.y)						// 타일이 가로형인애들만 occd
			{
				if (IntersectRect(&rc, &occd, &(tile->GetRect())))
				{
					if (rc.right - rc.left <= 2) continue;								// 이미지사이즈 찡김방지
					float fDistance = rObb.vPos.y - tileInfo.vPos.y;
					float fColTime = 0.f;
					if (fDistance < 0.f)												// 트랙이 밑에있음
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
					else													// 트랙이 위에있음
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
		////   세로형 트랙
		for (auto& tile : m_Objlist[OBJ_TRACK])							// 세로형 타일 일반 밀어내기 충돌처리
		{
			INFO&	tileInfo = tile->GetInfo();
			if (tileInfo.vSize.x < tileInfo.vSize.y)
			{
				if (IntersectRect(&rc, &occdx, &(tile->GetRect())))
				{
					float fDistance = rObb.vPos.x - tileInfo.vPos.x;
					float fColTime = 0.f;
					if (fDistance < 0.f)											// 트랙이 오른쪽에있음
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
					else													// 트랙이 왼쪽에있음
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
		////   구멍
		bool bCheck = false;
		for (auto& hole : m_Objlist[OBJ_HOLE])
		{
			INFO&	tileInfo = hole->GetInfo();
			if (rODir.y != 0.f && tileInfo.vSize.x >= tileInfo.vSize.y)						// 타일이 가로형인애들만 occd
			{
				if (IntersectRect(&rc, &occd, &(hole->GetRect())))
				{
					float fDistance = rObb.vPos.y - tileInfo.vPos.y;
					float fColTime = fDistance / (rODir.y * 0.05f);
					if (fDistance < 0.f)												// 트랙이 밑에있음
					{
						static_cast<CObb*>(m_pObb)->SetHoleState(1);
						bCheck = true;
					}
					else													// 트랙이 위에있음
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
					if (fDistance < 0.f)												// 트랙이 오른쪽에있음
					{
						static_cast<CObb*>(m_pObb)->SetHoleState(3);
						bCheck = true;
					}
					else																// 트랙이 왼쪽에있음
					{
						static_cast<CObb*>(m_pObb)->SetHoleState(4);
						bCheck = true;
					}
				}
			}
		}
		//  IBB 구멍
		for (auto& hole : m_Objlist[OBJ_IHOLE])
		{
			INFO&	tileInfo = hole->GetInfo();
			if (tileInfo.vSize.x < tileInfo.vSize.y)
			{
				if (IntersectRect(&rc, &occdx, &(hole->GetRect())))
				{
					float fDistance = rObb.vPos.x - tileInfo.vPos.x;
					float fColTime = 0.f;
					if (fDistance < 0.f)											// 트랙이 오른쪽에있음
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
					else													// 트랙이 왼쪽에있음
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
				if (rODir.y != 0.f)// && tileInfo.vSize.x >= tileInfo.vSize.y)						// 타일이 가로형인애들만 occd
				{
					if (IntersectRect(&rc, &occd, &(hole->GetRect())))
					{
						if (rc.right - rc.left <= 2) continue;								// 이미지사이즈 찡김방지
						float fDistance = rObb.vPos.y - tileInfo.vPos.y;
						float fColTime = 0.f;
						if (fDistance < 0.f)												// 트랙이 밑에있음
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
						else													// 트랙이 위에있음
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
		//  OBB 구멍
		for (auto& hole : m_Objlist[OBJ_OHOLE])
		{
			INFO&	tileInfo = hole->GetInfo();
			if (rODir.y != 0.f && tileInfo.vSize.x >= tileInfo.vSize.y)						// 타일이 가로형인애들만 ccd
			{
				if (IntersectRect(&rc, &occdx, &(hole->GetRect())))
				{
					float fDistance = rObb.vPos.y - tileInfo.vPos.y;
					float fColTime = fDistance / (rODir.y * 0.05f);
					if (fDistance < 0.f)												// 트랙이 밑에있음
					{
						static_cast<CObb*>(m_pObb)->SetHoleState(1);
						bCheck = true;
					}
					else													// 트랙이 위에있음
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
					if (fDistance < 0.f)												// 트랙이 오른쪽에있음
					{
						static_cast<CObb*>(m_pObb)->SetHoleState(3);
						bCheck = true;
					}
					else																// 트랙이 왼쪽에있음
					{
						static_cast<CObb*>(m_pObb)->SetHoleState(4);
						bCheck = true;
					}
				}
			}
		}
		if (!bCheck) static_cast<CObb*>(m_pObb)->SetHoleState(0);
		////   점프
		static_cast<CObb*>(m_pObb)->SetOnJump(0);	 // 초기화
		for (auto& jump : m_Objlist[OBJ_JUMP])
		{
			INFO&	tileInfo = jump->GetInfo();
			if (rODir.y != 0.f)// && tileInfo.vSize.x >= tileInfo.vSize.y)						// 타일이 가로형인애들만 occd
			{
				if (IntersectRect(&rc, &occd, &(jump->GetRect())))
				{
					if (rc.right - rc.left <= 2) continue;								// 이미지사이즈 찡김방지
					float fDistance = rObb.vPos.y - tileInfo.vPos.y;
					float fColTime = 0.f;
					if (fDistance < 0.f)												// 트랙이 밑에있음
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
					else													// 트랙이 위에있음
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
		//     발판
		for (auto& sup : m_Objlist[OBJ_SUPPORT])
		{
			INFO&	tileInfo = sup->GetInfo();
			if (static_cast<CObb*>(m_pObb)->GetGravity() > 0)				// 중력이 아래방향일때
			{
				if (IntersectRect(&rc, &occd, &(sup->GetRect())))
				{
					if (rc.right - rc.left <= 3)	continue;								// 이미지사이즈 찡김방지
					if (rODir.y < 0.f)				continue;								// 플레이어가 위쪽으로 이동할때
					float fDistance = ((int)tileInfo.vPos.y - (int)tileInfo.vSize.y / 2.f) - ((int)rObb.vPos.y + (int)rObb.vSize.y / 2.f);	// 발판머리와 플레이어 발 사이 거리
					float fColTime = fDistance / (rODir.y * 0.05f);
					if (fDistance > 0.f)			// 거리가 벌어져있으면
					{
						if (0.4f > fColTime)		// 박을 예정이면
						{
							D3DXVECTOR3 vColPos = { (rObb.vPos.x), (tileInfo.vPos.y - tileInfo.vSize.y / 2.f - rObb.vSize.y / 2.f), 0.f };
							static_cast<CObb*>(m_pObb)->SetCollison(fColTime, vColPos, 0);
						}
					}
					else if (fDistance == 0.f)		// 닿아있으면
					{
						static_cast<CObb*>(m_pObb)->SetYdir(0.f);
					}
					else							// 겹쳐있으면
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
			else																// 중력이 위쪽일때
			{
				if (IntersectRect(&rc, &occd, &(sup->GetRect())))
				{
					if (rc.right - rc.left <= 3)	continue;								// 이미지사이즈 찡김방지
					if (rODir.y > 0.f)				continue;								// 플레이어가 아래쪽으로 이동할때
					float fDistance = ((int)rObb.vPos.y - (int)rObb.vSize.y / 2.f) - ((int)tileInfo.vPos.y + (int)tileInfo.vSize.y / 2.f);	// 발판머리와 플레이어 발 사이 거리
					float fColTime = fDistance / (rODir.y * 0.05f);
					if (fDistance > 0.f)			// 거리가 벌어져있으면
					{
						if (0.4f > fColTime)		// 박을 예정이면
						{
							D3DXVECTOR3 vColPos = { (rObb.vPos.x), (tileInfo.vPos.y + tileInfo.vSize.y / 2.f + rObb.vSize.y / 2.f), 0.f };
							static_cast<CObb*>(m_pObb)->SetCollison(fColTime, vColPos, 0);
						}
					}
					else if (fDistance == 0.f)		// 닿아있으면
					{
						static_cast<CObb*>(m_pObb)->SetYdir(0.f);
					}
					else							// 겹쳐있으면
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

