
// Tool82View.cpp : CTool82View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Tool82.h"
#endif

#include "Tool82Doc.h"
#include "Tool82View.h"
#include "MainFrm.h"
#include "BackGround.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND		g_hWnd	= nullptr;
D3DXVECTOR3		g_vZoom = { 1.f, 1.f, 0.f };


// CTool82View

IMPLEMENT_DYNCREATE(CTool82View, CScrollView)

BEGIN_MESSAGE_MAP(CTool82View, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_DESTROY()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CTool82View 생성/소멸

CTool82View::CTool82View()
	: m_pDevice(CDevice::GetInstance())
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

void CTool82View::ImageLoad(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/MAP/Track/track_0%d.png",
		L"MAP",
		TEX_MULTI,
		L"Track",
		2)))
	{
		AfxMessageBox(L"멀티 텍스쳐 생성 실패");
		return;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/MAP/Map/map_0%d.png",
		L"MAP",
		TEX_MULTI,
		L"Map",
		2)))
	{
		AfxMessageBox(L"멀티 텍스쳐 생성 실패");
		return;
	}
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/MAP/Hole/hole_0%d.png",
		L"MAP",
		TEX_MULTI,
		L"Hole",
		3)))
	{
		AfxMessageBox(L"멀티 텍스쳐 생성 실패");
		return;
	}
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/MAP/Fixed/fixed_0%d.png",
		L"MAP",
		TEX_MULTI,
		L"Fixed",
		15)))
	{
		AfxMessageBox(L"멀티 텍스쳐 생성 실패");
		return;
	}
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/MONSTER/Support/support_0%d.png",
		L"MONSTER",
		TEX_MULTI,
		L"Support",
		3)))
	{
		AfxMessageBox(L"멀티 텍스쳐 생성 실패");
		return;
	}
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/MONSTER/Enemy/monster_0%d.png",
		L"MONSTER",
		TEX_MULTI,
		L"Enemy",
		2)))
	{
		AfxMessageBox(L"멀티 텍스쳐 생성 실패");
		return;
	}
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/MONSTER/Shadow/shadow_0%d.png",
		L"MONSTER",
		TEX_MULTI,
		L"Shadow",
		2)))
	{
		AfxMessageBox(L"멀티 텍스쳐 생성 실패");
		return;
	}
}


CTool82View::~CTool82View()
{
	Release();
}

////////////////////////////////////////////////////////////////////////
#pragma region 접

BOOL CTool82View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CTool82View 그리기

// CTool82View 인쇄

BOOL CTool82View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CTool82View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CTool82View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

// CTool82View 진단

#ifdef _DEBUG
	void CTool82View::AssertValid() const
	{
		CView::AssertValid();
	}

	void CTool82View::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}

	CTool82Doc* CTool82View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTool82Doc)));
		return (CTool82Doc*)m_pDocument;
	}
#endif //_DEBUG

void CTool82View::OnDestroy()
{
	CScrollView::OnDestroy();
}

// CTool82View 메시지 처리기

BOOL CTool82View::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CScrollView::DoMouseWheel(nFlags, zDelta, pt);
}

#pragma endregion

void CTool82View::OnDraw(CDC* /*pDC*/)
{
	CTool82Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	m_pDevice->Render_Begin();

	m_pBackGround->Render();

	m_pDevice->Render_End();

}


void CTool82View::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	m_pBackGround = new CBackGround;
	m_pBackGround->Initialize();

	SetScrollSizes(MM_TEXT, CSize(4800, 1500));

	CMainFrame*		pMainFrm = ((CMainFrame*)AfxGetMainWnd());
	m_pStateNum = &(pMainFrm->m_pMyForm->m_Radio);
	m_pIndexNum = &(pMainFrm->m_pMyForm->m_iCombo);
	m_pMyForm = pMainFrm->m_pMyForm;

	RECT	rcWindow{};

	pMainFrm->GetWindowRect(&rcWindow);	// 현재 창의 전체 프레임 사이즈를 얻어오는 함수

	SetRect(&rcWindow,
		0,
		0,
		rcWindow.right - rcWindow.left,
		rcWindow.bottom - rcWindow.top);

	RECT	rcMainView{};
	GetClientRect(&rcMainView); // 순수 뷰 창의 크기를 얻어오는 함수

	float	fRowFrm = float(rcWindow.right - rcMainView.right);
	float	fColFrm = float(rcWindow.bottom - rcMainView.bottom);

	pMainFrm->SetWindowPos(nullptr,
		100,
		100,
		int(WINCX + fRowFrm),
		int(WINCY + fColFrm + 17),
		SWP_NOZORDER);


	g_hWnd = m_hWnd;

	if (FAILED(CDevice::GetInstance()->InitDevice()))
	{
		AfxMessageBox(L"디바이스 초기화 실패");
		return;
	}

	ImageLoad();
}

POINT CTool82View::GetCur(void)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(&pt);

	pt.x += GetScrollPos(0);
	pt.y += GetScrollPos(1);

	pt.x = int(float(pt.x) / g_vZoom.x);
	pt.y = int(float(pt.y) / g_vZoom.y);

	if (pt.x % TRACKCXY >= TRACKCXY / 2)
	{
		pt.x += TRACKCXY - pt.x % TRACKCXY;
	}
	else
	{
		pt.x -= pt.x % TRACKCXY;
	}

	if (pt.y % TRACKCXY >= TRACKCXY / 2)
	{
		pt.y += TRACKCXY - pt.y % TRACKCXY;
	}
	else
	{
		pt.y -= pt.y % TRACKCXY;
	}

	return pt;
}

void CTool82View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	UpdateData(TRUE);
	POINT pt = GetCur();

	switch ((*m_pStateNum))
	{
	case 1:
		if (m_pStartPT != nullptr)
		{
			CDC* pDC = this->GetDC();
			pDC->SetROP2(R2_NOTXORPEN);
			pDC->Rectangle(&m_rt);
			m_rt.right = (pt.x - GetScrollPos(0)) * g_vZoom.x;
			m_rt.bottom = (pt.y - GetScrollPos(1)) * g_vZoom.y;
			m_pBackGround->Render();
			pDC->Rectangle(&m_rt);
			this->ReleaseDC(pDC);
		}
		break;
	case 2:
		if (m_pStartPT != nullptr)
		{
			CDC* pDC = this->GetDC();
			pDC->SetROP2(R2_NOTXORPEN);
			pDC->Rectangle(&m_rt);
			m_rt.right = (pt.x - GetScrollPos(0)) * g_vZoom.x;
			m_rt.bottom = (pt.y - GetScrollPos(1)) * g_vZoom.y;
			m_pBackGround->Render();
			pDC->Rectangle(&m_rt);
			this->ReleaseDC(pDC);
		}
		break;
	case 3:
		if (m_pSampleImg != nullptr)
		{
			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(&pt);
			pt.x = int(float(pt.x) / g_vZoom.x);
			pt.y = int(float(pt.y) / g_vZoom.y);
			m_pSampleImg->vPos = { float(pt.x), float(pt.y), 0.f };
			Invalidate(FALSE);
		}
		break;
	case 4:
		if (m_pSampleSup != nullptr)
		{
			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(&pt);
			pt.x = int(float(pt.x) / g_vZoom.x);
			pt.y = int(float(pt.y) / g_vZoom.y);
			m_pSampleSup->vPos = { float(pt.x), float(pt.y), 0.f };
			Invalidate(FALSE);
		}
		break;
	case 5:
		if (m_pSampleMon != nullptr)
		{
			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(&pt);
			pt.x = int(float(pt.x) / g_vZoom.x);
			pt.y = int(float(pt.y) / g_vZoom.y);
			m_pSampleMon->vPos = { float(pt.x), float(pt.y), 0.f };
			Invalidate(FALSE);
		}
	}
	UpdateData(FALSE);

	CScrollView::OnMouseMove(nFlags, point);
}


void CTool82View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch ((*m_pStateNum))
	{
	case 1:
		if (m_pStartPT == nullptr)
		{
			m_pStartPT = new POINT;
			m_pStartPT->x = GetCur().x;
			m_pStartPT->y = GetCur().y;
			m_rt.left = (m_pStartPT->x - GetScrollPos(0)) * g_vZoom.x;
			m_rt.right = (m_pStartPT->x - GetScrollPos(0)) * g_vZoom.x;
			m_rt.top = (m_pStartPT->y - GetScrollPos(1)) * g_vZoom.y;
			m_rt.bottom = (m_pStartPT->y - GetScrollPos(1)) * g_vZoom.y;
		}
		else if (m_pStartPT != nullptr)
		{
			POINT		 pt		= GetCur();
			tRECT*		pRect	= new tRECT;

			pRect->vPos = { float(m_pStartPT->x + pt.x) / 2.f, float(m_pStartPT->y + pt.y) / 2.f, 0.f };
			pRect->vSize = { fabsf(float(m_pStartPT->x - pt.x)), fabsf(float(m_pStartPT->y - pt.y)), 0.f };

			switch (*m_pIndexNum)
			{
			case 0: pRect->eType = RT_TRACK; break;
			case 1: pRect->eType = RT_HOLE; break;
			case 2: pRect->eType = RT_IHOLE; break;
			case 3: pRect->eType = RT_OHOLE; break;
			case 4: pRect->eType = RT_JUMP; break;
			}
			m_Rectlist[(*m_pIndexNum)].push_back(pRect);

			Safe_Delete(m_pStartPT);
			Invalidate();
		}
		break;
	case 2:
		if (m_pStartPT == nullptr)
		{
			m_pStartPT = new POINT;
			m_pStartPT->x = GetCur().x;
			m_pStartPT->y = GetCur().y;
			m_rt.left = (m_pStartPT->x - GetScrollPos(0)) * g_vZoom.x;
			m_rt.right = (m_pStartPT->x - GetScrollPos(0)) * g_vZoom.x;
			m_rt.top = (m_pStartPT->y - GetScrollPos(1)) * g_vZoom.y;
			m_rt.bottom = (m_pStartPT->y - GetScrollPos(1)) * g_vZoom.y;
		}
		else if (m_pStartPT != nullptr)
		{
			POINT		 pt = GetCur();
			tRECT*		pRect = new tRECT;

			pRect->vPos = { float(m_pStartPT->x + pt.x) / 2.f, float(m_pStartPT->y + pt.y) / 2.f, 0.f };
			pRect->vSize = { fabsf(float(m_pStartPT->x - pt.x)) + TRACKCXY/2.f, fabsf(float(m_pStartPT->y - pt.y)) + TRACKCXY / 2.f, 0.f };
			m_Map2list.push_back(pRect);
			Safe_Delete(m_pStartPT);
			Invalidate();
		}
		break;
	case 3:
		if (m_pSampleImg == nullptr)
		{
			m_pSampleImg = new bOBJ;
			m_pSampleImg->iDrawID = *m_pIndexNum;
			m_pSampleImg->eType = BG_FIX;
			m_pSampleImg->vScale = { 1.f, 1.f, 0.f };
		}
		else
		{
			m_pSampleImg->vPos.x += GetScrollPos(0);
			m_pSampleImg->vPos.y += GetScrollPos(1);
			m_BObjlist[BG_FIX].push_back(m_pSampleImg);
			m_pSampleImg = nullptr;
			Invalidate();
		}
		break;
	case 4:
		if (m_pSampleSup == nullptr)
		{
			m_pSampleSup = new SUP;
			m_pSampleSup->eType = (SUPPORTTYPE)(*m_pIndexNum);
			m_pSampleSup->vScale = { 1.f, 1.f, 0.f };
		}
		else
		{
			m_pSampleSup->vPos.x += GetScrollPos(0);
			m_pSampleSup->vPos.y += GetScrollPos(1);
			m_Suplist[(SUPPORTTYPE)(*m_pIndexNum)].push_back(m_pSampleSup);
			m_pSampleSup = nullptr;
			Invalidate();
		}
		break;
	case 5:
		if (m_pSampleMon == nullptr)
		{
			m_pSampleMon = new MON;
			ZeroMemory(m_pSampleMon, sizeof(MON));
			m_pSampleMon->eType = (MONSTERTYPE)(*m_pIndexNum);
			m_pSampleMon->vScale = { 1.f, 1.f, 0.f };
		}
		else if (m_pSampleMon->ptStart.x == 0 && m_pSampleMon->ptStart.y == 0)
		{
			m_pSampleMon->ptStart.x = m_pSampleMon->vPos.x + GetScrollPos(0);
			m_pSampleMon->ptStart.y = m_pSampleMon->vPos.y + GetScrollPos(1);
			Invalidate();
		}
		else
		{
			m_pSampleMon->vPos.x += GetScrollPos(0);
			m_pSampleMon->vPos.y += GetScrollPos(1);
			m_pSampleMon->ptEnd.x = m_pSampleMon->vPos.x;
			m_pSampleMon->ptEnd.y = m_pSampleMon->vPos.y;
			m_Monlist.push_back(m_pSampleMon);
			m_pSampleMon = nullptr;
			Invalidate();
		}
		break;
	default:
		break;
	}

	CScrollView::OnLButtonDown(nFlags, point);
}

void CTool82View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch ((*m_pStateNum))
	{
	case 1:
		if (m_Rectlist[(*m_pIndexNum)].size() != 0)
		{
			Safe_Delete(m_Rectlist[(*m_pIndexNum)].back());
			m_Rectlist[(*m_pIndexNum)].pop_back();
			Invalidate(FALSE);
		}
		break;
	case 2:
		if (m_Map2list.size() != 0)
		{
			Safe_Delete(m_Map2list.back());
			m_Map2list.pop_back();
			Invalidate(FALSE);
		}
		break;
	case 3:
		if (m_BObjlist[BG_FIX].size() != 0)
		{
			Safe_Delete(m_BObjlist[BG_FIX].back());
			m_BObjlist[BG_FIX].pop_back();
			Invalidate(FALSE);
		}
		break;
	case 4:
		if (m_Suplist[(*m_pIndexNum)].size() != 0)
		{
			Safe_Delete(m_Suplist[(*m_pIndexNum)].back());
			m_Suplist[(*m_pIndexNum)].pop_back();
			Invalidate(FALSE);
		}
		break;
	case 5:
		if (m_Monlist.size() != 0)
		{
			Safe_Delete(m_Monlist.back());
			m_Monlist.pop_back();
			Invalidate(FALSE);
		}
		break;
	default:
		break;
	}

	CScrollView::OnRButtonDown(nFlags, point);
}


void CTool82View::Release(void)
{
	for (auto& list : m_Rectlist)
	{
		for (auto& rt : list)
		{
			Safe_Delete(rt);
		}
	}
	for (auto& map : m_Map2list)
	{
		Safe_Delete(map);
	}
	for (auto& list : m_BObjlist)
	{
		for (auto& bobj : list)
		{
			Safe_Delete(bobj);
		}
	}
	for (auto& list : m_Suplist)
	{
		for (auto& sup : list)
		{
			Safe_Delete(sup);
		}
	}
	for (auto& mon : m_Monlist)
	{
		Safe_Delete(mon);
	}
	Safe_Delete(m_pBackGround);
	CTextureMgr::GetInstance()->DestroyInstance();
	CDevice::GetInstance()->DestroyInstance();
}

void CTool82View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_pSampleImg != nullptr)
	{
		switch (nChar)
		{
		case VK_SPACE:
			m_pSampleImg->vScale.y *= -1.f;
			break;
		case 'W':
			if (m_pSampleImg->vScale.y <= 0)
				m_pSampleImg->vScale.y -= 0.25f;
			else
				m_pSampleImg->vScale.y += 0.25f;
			break;
		case 'S':
			if (m_pSampleImg->vScale.y >= 0)
				m_pSampleImg->vScale.y -= 0.25f;
			else
				m_pSampleImg->vScale.y += 0.25f;
			break;
		case 'A':
			m_pSampleImg->vScale.x -= 0.25f;
			break;
		case 'D':
			m_pSampleImg->vScale.x += 0.25f;
			break;
		}
	}
	if (m_pSampleSup != nullptr)
	{
		switch (nChar)
		{
		case VK_SPACE:
			m_pSampleSup->vScale.y *= -1.f;
			break;
		case 'W':
			if (m_pSampleSup->vScale.y <= 0)
				m_pSampleSup->vScale.y -= 0.25f;
			else
				m_pSampleSup->vScale.y += 0.25f;
			break;
		case 'S':
			if (m_pSampleSup->vScale.y >= 0)
				m_pSampleSup->vScale.y -= 0.25f;
			else
				m_pSampleSup->vScale.y += 0.25f;
			break;
		case 'A':
			m_pSampleSup->vScale.x -= 0.25f;
			break;
		case 'D':
			m_pSampleSup->vScale.x += 0.25f;
			break;
		}
	}
	wstring		wstrZoom = L"배율 : ";
	switch (nChar)
	{
	case 'Q':
		if (g_vZoom.x > 0.3f) g_vZoom.x -= 0.05f;
		if (g_vZoom.y > 0.3f) g_vZoom.y -= 0.05f;
		wstrZoom = wstrZoom + to_wstring(g_vZoom.x);
		m_pMyForm->GetDlgItem(IDC_EDIT1)->SetWindowText(wstrZoom.c_str());
		break;
	case 'E':
		if (g_vZoom.x < 2.f) g_vZoom.x += 0.05f;
		if (g_vZoom.y < 2.f) g_vZoom.y += 0.05f;
		wstrZoom = wstrZoom + to_wstring(g_vZoom.x);
		m_pMyForm->GetDlgItem(IDC_EDIT1)->SetWindowText(wstrZoom.c_str());
		break;
	}
	Invalidate(FALSE);
	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}
