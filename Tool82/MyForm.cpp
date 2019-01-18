// MyForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool82.h"
#include "MyForm.h"
#include "MainFrm.h"

// CMyForm

IMPLEMENT_DYNCREATE(CMyForm, CFormView)

CMyForm::CMyForm()
	: CFormView(IDD_MYFORM)
	, m_Radio(0)
	, m_bTrackRadio(false)
	, m_bObjRadio(false)
{

}

CMyForm::~CMyForm()
{
}

void CMyForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_Radio);
	DDX_Control(pDX, IDC_COMBO1, m_TrackCombo);
	DDX_Control(pDX, IDC_COMBO2, m_MapCombo);
	DDX_Control(pDX, IDC_COMBO3, m_ObjCombo);
	DDX_Control(pDX, IDC_COMBO4, m_SupportCombo);
	DDX_Control(pDX, IDC_COMBO5, m_MonCombo);
	DDX_Control(pDX, IDC_RADIO1, m_RadioCtrl);
}

BEGIN_MESSAGE_MAP(CMyForm, CFormView)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO1, IDC_RADIO7, &CMyForm::SetRadioStatus)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMyForm::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CMyForm::OnCbnSelchangeCombo3)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyForm::OnSaveButton)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyForm::OnLoadButton)
	ON_CBN_SELCHANGE(IDC_COMBO4, &CMyForm::OnCbnSelchangeCombo4)
	ON_CBN_SELCHANGE(IDC_COMBO5, &CMyForm::OnCbnSelchangeCombo5)
END_MESSAGE_MAP()


// CMyForm 진단입니다.

#ifdef _DEBUG
void CMyForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyForm 메시지 처리기입니다.

void CMyForm::SetRadioStatus(UINT value)
{
	m_Radio = value - 1000;

	switch (m_Radio)
	{
	case 1:
		m_iCombo = m_TrackCombo.GetCurSel();
		break;
	case 2:
		break;
	case 3:
		m_iCombo = m_ObjCombo.GetCurSel();
		break;
	case 4:
		m_iCombo = m_SupportCombo.GetCurSel();
	break;
	}
}


void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	CMainFrame*		pMainFrm = ((CMainFrame*)AfxGetMainWnd());

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
		int(250 + fRowFrm),
		int(WINCY + fColFrm + 17),
		SWP_NOZORDER);


	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	
	m_TrackCombo.InsertString(0, L"Track");
	m_TrackCombo.InsertString(1, L"Hole");
	m_TrackCombo.InsertString(2, L"IbbHole");
	m_TrackCombo.InsertString(3, L"ObbHole");
	m_TrackCombo.InsertString(4, L"Jump");
	m_TrackCombo.SetCurSel(0);

	
	m_MapCombo.InsertString(0, L"MAP");
	m_MapCombo.SetCurSel(0);

	m_ObjCombo.InsertString(0, L"산1");
	m_ObjCombo.InsertString(1, L"산2");
	m_ObjCombo.InsertString(2, L"풀1");
	m_ObjCombo.InsertString(3, L"풀2");
	m_ObjCombo.InsertString(4, L"풀3");
	m_ObjCombo.InsertString(5, L"나무1");
	m_ObjCombo.InsertString(6, L"나무2");
	m_ObjCombo.InsertString(7, L"야자1");
	m_ObjCombo.InsertString(8, L"야자2");
	m_ObjCombo.InsertString(9, L"덩쿨1");
	m_ObjCombo.InsertString(10, L"덩쿨2");
	m_ObjCombo.InsertString(11, L"덩쿨3");
	m_ObjCombo.InsertString(12, L"링1");
	m_ObjCombo.InsertString(13, L"링2");
	m_ObjCombo.InsertString(14, L"구름");

	m_ObjCombo.SetCurSel(0);

	m_SupportCombo.InsertString(0, L"사각");
	m_SupportCombo.InsertString(1, L"마름모");
	m_SupportCombo.InsertString(2, L"롱롱");

	m_SupportCombo.SetCurSel(0);

	m_MonCombo.InsertString(0, L"동글이");
	m_MonCombo.InsertString(1, L"반쪽이");

	m_MonCombo.SetCurSel(0);

	GetDlgItem(IDC_EDIT1)->SetWindowText(L"배율 : 1.0");
}


void CMyForm::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_Radio = 1;
	m_iCombo = m_TrackCombo.GetCurSel();
}

void CMyForm::OnCbnSelchangeCombo3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_Radio = 3;
	m_iCombo = m_ObjCombo.GetCurSel();
}

void CMyForm::OnCbnSelchangeCombo4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_Radio = 4;
	m_iCombo = m_SupportCombo.GetCurSel();
}

void CMyForm::OnCbnSelchangeCombo5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_Radio = 5;
	m_iCombo = m_MonCombo.GetCurSel();
}

void CMyForm::OnSaveButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog		Dlg(FALSE,	    // false 인 경우 저장, true인 경우 불러오기
		L"dat",    // 파일의 확장자명 
		L"*.dat",  // 최초에 창에 띄워줄 문자열
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // 중복된 파일이 있을 경우에 경고
		L"*.dat", // 지원하는 파일 형식
		this);

	if (IDCANCEL == Dlg.DoModal())
		return;

	TCHAR		szDirPath[MAX_PATH] = L"";

	GetCurrentDirectory(sizeof(szDirPath), szDirPath);
	SetCurrentDirectory(szDirPath);
	PathRemoveFileSpec(szDirPath);
	lstrcat(szDirPath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szDirPath;

	HANDLE	hFile = CreateFile(Dlg.GetPathName(),
		GENERIC_WRITE,
		0,
		nullptr,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	DWORD		dwByte = 0;

	CTool82View*	pMainView = ((CMainFrame*)AfxGetMainWnd())->m_pMainView;

	{
		int iCount = pMainView->m_Map2list.size();
		WriteFile(hFile, &iCount, sizeof(int), &dwByte, nullptr);
		for (auto& map : pMainView->m_Map2list)
		{
			WriteFile(hFile, map, sizeof(tRECT), &dwByte, nullptr);
		}
		printf("맵 : %d \n", pMainView->m_Map2list.size());
	}
	for (size_t i = 0; i < RT_END; ++i)
	{
		int iCount = pMainView->m_Rectlist[i].size();
		WriteFile(hFile, &iCount, sizeof(int), &dwByte, nullptr);
		for (auto& list : pMainView->m_Rectlist[i])
		{
			WriteFile(hFile, list, sizeof(tRECT), &dwByte, nullptr);
		}
		printf("렉트[%d] : %d \n", i, pMainView->m_Rectlist[i].size());
	}
	for (size_t i = 0; i < BG_END; ++i)
	{
		int iCount = pMainView->m_BObjlist[i].size();
		WriteFile(hFile, &iCount, sizeof(int), &dwByte, nullptr);
		for (auto& bobj : pMainView->m_BObjlist[i])
		{
			WriteFile(hFile, bobj, sizeof(bOBJ), &dwByte, nullptr);
		}
		printf("배경[%d] : %d \n", i, pMainView->m_BObjlist[i].size());
	}
	for (size_t i = 0; i < SP_END; ++i)
	{
		int iCount = pMainView->m_Suplist[i].size();
		WriteFile(hFile, &iCount, sizeof(int), &dwByte, nullptr);
		for (auto& sup : pMainView->m_Suplist[i])
		{
			WriteFile(hFile, sup, sizeof(SUP), &dwByte, nullptr);
			printf("타입 : %d \n", (int)sup->eType);
		}
		printf("발판[%d] : %d \n", i, pMainView->m_Suplist[i].size());
	}
	{
		int iCount = pMainView->m_Monlist.size();
		WriteFile(hFile, &iCount, sizeof(int), &dwByte, nullptr);
		for (auto& mon : pMainView->m_Monlist)
		{
			WriteFile(hFile, mon, sizeof(MON), &dwByte, nullptr);
		}
		printf("몬스터 : %d \n", pMainView->m_Monlist.size());
	}
	CloseHandle(hFile);
}

void CMyForm::OnLoadButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CTool82View*	pMainView = ((CMainFrame*)AfxGetMainWnd())->m_pMainView;
	list<tRECT*>*	m_Rectlist = pMainView->m_Rectlist;
	list<tRECT*>*	m_Map2list = &pMainView->m_Map2list;
	list<bOBJ*>*	m_BObjlist = pMainView->m_BObjlist;
	list<SUP*>*		m_Suplist = pMainView->m_Suplist;
	list<MON*>*		m_Monlist = &pMainView->m_Monlist;

	for (size_t i = 0; i < RT_END; ++i)
	{
		for (auto& rt : m_Rectlist[i])
		{
			Safe_Delete(rt);
		}
		m_Rectlist[i].clear();
	}
	for (auto& map : *m_Map2list)
	{
		Safe_Delete(map);
		m_Map2list->clear();
	}
	for (size_t i = 0; i < BG_END; ++i)
	{
		for (auto& bobj : m_BObjlist[i])
		{
			Safe_Delete(bobj);
		}
		m_BObjlist[i].clear();
	}
	for (size_t i = 0; i < SP_END; ++i)
	{
		for (auto& sup : m_Suplist[i])
		{
			Safe_Delete(sup);
		}
		m_Suplist[i].clear();
	}
	for (auto& mon : *m_Monlist)
	{
		Safe_Delete(mon);
		m_Monlist->clear();
	}

	CFileDialog		Dlg(TRUE,	    // false 인 경우 저장, true인 경우 불러오기
		L"dat",    // 파일의 확장자명 
		L"*.dat",  // 최초에 창에 띄워줄 문자열
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // 중복된 파일이 있을 경우에 경고
		L"*.dat", // 지원하는 파일 형식
		this);

	if (IDCANCEL == Dlg.DoModal())
		return;

	TCHAR		szDirPath[MAX_PATH] = L"";

	GetCurrentDirectory(sizeof(szDirPath), szDirPath);
	SetCurrentDirectory(szDirPath);
	PathRemoveFileSpec(szDirPath);
	lstrcat(szDirPath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szDirPath;

	HANDLE	hFile = CreateFile(Dlg.GetPathName(),
		GENERIC_READ,
		0,
		nullptr,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	DWORD		dwByte = 0;

	{
		int iCount = 0;
		ReadFile(hFile, &iCount, sizeof(int), &dwByte, nullptr);
		for (int i = 0; i < iCount; ++i)
		{
			tRECT* pTemp = new tRECT;
			ReadFile(hFile, pTemp, sizeof(tRECT), &dwByte, nullptr);
			m_Map2list->push_back(pTemp);
		}
		printf("맵 : %d \n", m_Map2list->size());
	}
	for (size_t i = 0; i < RT_END; ++i)
	{
		int iCount = 0;// = pMainView->m_Rectlist[i].size();
		ReadFile(hFile, &iCount, sizeof(int), &dwByte, nullptr);
		for(int j = 0; j < iCount; ++j)
		{
			tRECT* pTemp = new tRECT;
			ReadFile(hFile, pTemp, sizeof(tRECT), &dwByte, nullptr);
			m_Rectlist[i].push_back(pTemp);
		}
		printf("렉트[%d] : %d \n", i, m_Rectlist[i].size());
	}
	for (size_t i = 0; i < BG_END; ++i)
	{
		int iCount = 0;
		ReadFile(hFile, &iCount, sizeof(int), &dwByte, nullptr);
		for (int j = 0; j < iCount; ++j)
		{
			bOBJ* pTemp = new bOBJ;
			ReadFile(hFile, pTemp, sizeof(bOBJ), &dwByte, nullptr);
			m_BObjlist[i].push_back(pTemp);
		}
		printf("오브[%d] : %d \n", i, m_BObjlist[i].size());
	}
	for (size_t i = 0; i < SP_END; ++i)
	{
		int iCount = 0;
		ReadFile(hFile, &iCount, sizeof(int), &dwByte, nullptr);
		for (int j = 0; j < iCount; ++j)
		{
			SUP* pTemp = new SUP;
			ReadFile(hFile, pTemp, sizeof(SUP), &dwByte, nullptr);
			m_Suplist[i].push_back(pTemp);
		}
		printf("발판[%d] : %d \n", i, m_Suplist[i].size());
	}
	{
		int iCount = 0;
		ReadFile(hFile, &iCount, sizeof(int), &dwByte, nullptr);
		for (int i = 0; i < iCount; ++i)
		{
			MON* pTemp = new MON;
			ReadFile(hFile, pTemp, sizeof(MON), &dwByte, nullptr);
			m_Monlist->push_back(pTemp);
		}
		printf("몬스터 : %d \n", m_Monlist->size());
	}

	CloseHandle(hFile);

	pMainView->Invalidate(FALSE);
}