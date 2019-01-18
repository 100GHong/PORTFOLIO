// MyForm.cpp : ���� �����Դϴ�.
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


// CMyForm �����Դϴ�.

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


// CMyForm �޽��� ó�����Դϴ�.

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

	pMainFrm->GetWindowRect(&rcWindow);	// ���� â�� ��ü ������ ����� ������ �Լ�

	SetRect(&rcWindow,
		0,
		0,
		rcWindow.right - rcWindow.left,
		rcWindow.bottom - rcWindow.top);

	RECT	rcMainView{};
	GetClientRect(&rcMainView); // ���� �� â�� ũ�⸦ ������ �Լ�

	float	fRowFrm = float(rcWindow.right - rcMainView.right);
	float	fColFrm = float(rcWindow.bottom - rcMainView.bottom);

	pMainFrm->SetWindowPos(nullptr,
		100,
		100,
		int(250 + fRowFrm),
		int(WINCY + fColFrm + 17),
		SWP_NOZORDER);


	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	
	m_TrackCombo.InsertString(0, L"Track");
	m_TrackCombo.InsertString(1, L"Hole");
	m_TrackCombo.InsertString(2, L"IbbHole");
	m_TrackCombo.InsertString(3, L"ObbHole");
	m_TrackCombo.InsertString(4, L"Jump");
	m_TrackCombo.SetCurSel(0);

	
	m_MapCombo.InsertString(0, L"MAP");
	m_MapCombo.SetCurSel(0);

	m_ObjCombo.InsertString(0, L"��1");
	m_ObjCombo.InsertString(1, L"��2");
	m_ObjCombo.InsertString(2, L"Ǯ1");
	m_ObjCombo.InsertString(3, L"Ǯ2");
	m_ObjCombo.InsertString(4, L"Ǯ3");
	m_ObjCombo.InsertString(5, L"����1");
	m_ObjCombo.InsertString(6, L"����2");
	m_ObjCombo.InsertString(7, L"����1");
	m_ObjCombo.InsertString(8, L"����2");
	m_ObjCombo.InsertString(9, L"����1");
	m_ObjCombo.InsertString(10, L"����2");
	m_ObjCombo.InsertString(11, L"����3");
	m_ObjCombo.InsertString(12, L"��1");
	m_ObjCombo.InsertString(13, L"��2");
	m_ObjCombo.InsertString(14, L"����");

	m_ObjCombo.SetCurSel(0);

	m_SupportCombo.InsertString(0, L"�簢");
	m_SupportCombo.InsertString(1, L"������");
	m_SupportCombo.InsertString(2, L"�շ�");

	m_SupportCombo.SetCurSel(0);

	m_MonCombo.InsertString(0, L"������");
	m_MonCombo.InsertString(1, L"������");

	m_MonCombo.SetCurSel(0);

	GetDlgItem(IDC_EDIT1)->SetWindowText(L"���� : 1.0");
}


void CMyForm::OnCbnSelchangeCombo1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_Radio = 1;
	m_iCombo = m_TrackCombo.GetCurSel();
}

void CMyForm::OnCbnSelchangeCombo3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_Radio = 3;
	m_iCombo = m_ObjCombo.GetCurSel();
}

void CMyForm::OnCbnSelchangeCombo4()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_Radio = 4;
	m_iCombo = m_SupportCombo.GetCurSel();
}

void CMyForm::OnCbnSelchangeCombo5()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_Radio = 5;
	m_iCombo = m_MonCombo.GetCurSel();
}

void CMyForm::OnSaveButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog		Dlg(FALSE,	    // false �� ��� ����, true�� ��� �ҷ�����
		L"dat",    // ������ Ȯ���ڸ� 
		L"*.dat",  // ���ʿ� â�� ����� ���ڿ�
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // �ߺ��� ������ ���� ��쿡 ���
		L"*.dat", // �����ϴ� ���� ����
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
		printf("�� : %d \n", pMainView->m_Map2list.size());
	}
	for (size_t i = 0; i < RT_END; ++i)
	{
		int iCount = pMainView->m_Rectlist[i].size();
		WriteFile(hFile, &iCount, sizeof(int), &dwByte, nullptr);
		for (auto& list : pMainView->m_Rectlist[i])
		{
			WriteFile(hFile, list, sizeof(tRECT), &dwByte, nullptr);
		}
		printf("��Ʈ[%d] : %d \n", i, pMainView->m_Rectlist[i].size());
	}
	for (size_t i = 0; i < BG_END; ++i)
	{
		int iCount = pMainView->m_BObjlist[i].size();
		WriteFile(hFile, &iCount, sizeof(int), &dwByte, nullptr);
		for (auto& bobj : pMainView->m_BObjlist[i])
		{
			WriteFile(hFile, bobj, sizeof(bOBJ), &dwByte, nullptr);
		}
		printf("���[%d] : %d \n", i, pMainView->m_BObjlist[i].size());
	}
	for (size_t i = 0; i < SP_END; ++i)
	{
		int iCount = pMainView->m_Suplist[i].size();
		WriteFile(hFile, &iCount, sizeof(int), &dwByte, nullptr);
		for (auto& sup : pMainView->m_Suplist[i])
		{
			WriteFile(hFile, sup, sizeof(SUP), &dwByte, nullptr);
			printf("Ÿ�� : %d \n", (int)sup->eType);
		}
		printf("����[%d] : %d \n", i, pMainView->m_Suplist[i].size());
	}
	{
		int iCount = pMainView->m_Monlist.size();
		WriteFile(hFile, &iCount, sizeof(int), &dwByte, nullptr);
		for (auto& mon : pMainView->m_Monlist)
		{
			WriteFile(hFile, mon, sizeof(MON), &dwByte, nullptr);
		}
		printf("���� : %d \n", pMainView->m_Monlist.size());
	}
	CloseHandle(hFile);
}

void CMyForm::OnLoadButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

	CFileDialog		Dlg(TRUE,	    // false �� ��� ����, true�� ��� �ҷ�����
		L"dat",    // ������ Ȯ���ڸ� 
		L"*.dat",  // ���ʿ� â�� ����� ���ڿ�
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // �ߺ��� ������ ���� ��쿡 ���
		L"*.dat", // �����ϴ� ���� ����
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
		printf("�� : %d \n", m_Map2list->size());
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
		printf("��Ʈ[%d] : %d \n", i, m_Rectlist[i].size());
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
		printf("����[%d] : %d \n", i, m_BObjlist[i].size());
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
		printf("����[%d] : %d \n", i, m_Suplist[i].size());
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
		printf("���� : %d \n", m_Monlist->size());
	}

	CloseHandle(hFile);

	pMainView->Invalidate(FALSE);
}