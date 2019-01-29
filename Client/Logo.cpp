#include "stdafx.h"
#include "Logo.h"
#include "SceneMgr.h"
#include "Stage.h"


void CLogo::LoadData(void)
{


	//HANDLE	hFile = CreateFile(L"../Data/test.dat",
	//	GENERIC_READ,
	//	0,
	//	nullptr,
	//	OPEN_EXISTING,
	//	FILE_ATTRIBUTE_NORMAL,
	//	NULL);

	//DWORD		dwByte = 0;
	//tRECT		tempRT;
	//bOBJ		tempBO;
	//SUP			tempSP;
	//MON			tempMON;

	//{
	//	int iCount = 0;
	//	ReadFile(hFile, &iCount, sizeof(int), &dwByte, nullptr);
	//	for (int i = 0; i < iCount; ++i)
	//	{
	//		ReadFile(hFile, pTemp, sizeof(tRECT), &dwByte, nullptr);
	//		m_Map2list->push_back(pTemp);
	//	}
	//	printf("맵 : %d \n", m_Map2list->size());
	//}
	//for (size_t i = 0; i < RT_END; ++i)
	//{
	//	int iCount = 0;// = pMainView->m_Rectlist[i].size();
	//	ReadFile(hFile, &iCount, sizeof(int), &dwByte, nullptr);
	//	for (int j = 0; j < iCount; ++j)
	//	{
	//		tRECT* pTemp = new tRECT;
	//		ReadFile(hFile, pTemp, sizeof(tRECT), &dwByte, nullptr);
	//		m_Rectlist[i].push_back(pTemp);
	//	}
	//	printf("렉트[%d] : %d \n", i, m_Rectlist[i].size());
	//}
	//for (size_t i = 0; i < BG_END; ++i)
	//{
	//	int iCount = 0;
	//	ReadFile(hFile, &iCount, sizeof(int), &dwByte, nullptr);
	//	for (int j = 0; j < iCount; ++j)
	//	{
	//		bOBJ* pTemp = new bOBJ;
	//		ReadFile(hFile, pTemp, sizeof(bOBJ), &dwByte, nullptr);
	//		m_BObjlist[i].push_back(pTemp);
	//	}
	//	printf("오브[%d] : %d \n", i, m_BObjlist[i].size());
	//}
	//for (size_t i = 0; i < SP_END; ++i)
	//{
	//	int iCount = 0;
	//	ReadFile(hFile, &iCount, sizeof(int), &dwByte, nullptr);
	//	for (int j = 0; j < iCount; ++j)
	//	{
	//		SUP* pTemp = new SUP;
	//		ReadFile(hFile, pTemp, sizeof(SUP), &dwByte, nullptr);
	//		m_Suplist[i].push_back(pTemp);
	//	}
	//	printf("발판[%d] : %d \n", i, m_Suplist[i].size());
	//}
	//{
	//	int iCount = 0;
	//	ReadFile(hFile, &iCount, sizeof(int), &dwByte, nullptr);
	//	for (int i = 0; i < iCount; ++i)
	//	{
	//		MON* pTemp = new MON;
	//		ReadFile(hFile, pTemp, sizeof(MON), &dwByte, nullptr);
	//		m_Monlist->push_back(pTemp);
	//	}
	//	printf("몬스터 : %d \n", m_Monlist->size());
	//}

	//CloseHandle(hFile);
}

CLogo::CLogo()
{
}

CLogo::~CLogo()
{
}

unsigned __stdcall ImgLoadFunction(void* pArg)
{
	CLogo*			pLogo = (CLogo*)pArg;

	EnterCriticalSection(&pLogo->GetCrt());

	if (FAILED(CTextureMgr::GetInstance()->ReadImgPath(L"../Data/ImgPath.txt")))
	{
		ERR_MSG(L"TEXTURE LOAD FAILED");
		return E_FAIL;
	}

	CScene*	pGame = CSceneMgr::GetInstance()->GetGame();
	pGame->Initialize();

	CTextureMgr::GetInstance()->SetMessage(L"로딩 완료");

	LeaveCriticalSection(&pLogo->GetCrt());

	_endthreadex(0);

	return 0;
}

HRESULT CLogo::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Scene/LOGO/Loading/Logo_00.png", L"LOGO", TEX_SINGLE)))
	{
		ERR_MSG(L"LOGO Texture INIT FAILED");
		return E_FAIL;
	}

	InitializeCriticalSection(&m_Crt);

	m_hThread = (HANDLE)_beginthreadex(0, 0, ImgLoadFunction, this, 0, nullptr);

	return S_OK;
}

int CLogo::Progress(void)
{
	if (GetAsyncKeyState(VK_RETURN))
	{
		WaitForSingleObject(m_hThread, INFINITE);
		CloseHandle(m_hThread);

		DeleteCriticalSection(&m_Crt);

		CSceneMgr::GetInstance()->SetScene(SC_GAME);

		return 0;
	}

	return 0;
}

void CLogo::Render(void)
{
	const TEXINFO*	pTexture = CTextureMgr::GetInstance()->GetTexture(L"LOGO");

	if (nullptr == pTexture)
		return;

	float fX = pTexture->tImgInfo.Width / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	D3DXMATRIX	matTrans;
	D3DXMatrixTranslation(&matTrans, WINCX / 2.f, WINCY / 2.f, 0.f);

	// 로고 텍스쳐
	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture,
		nullptr, &D3DXVECTOR3(fX, fY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	// 파일 경로
	D3DXMatrixTranslation(&matTrans, 50.f, 500.f, 0.f);
	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetFont()->DrawTextW(CDevice::GetInstance()->GetSprite(),
		CTextureMgr::GetInstance()->GetFilePath().c_str(),
		CTextureMgr::GetInstance()->GetFilePath().length(),
		nullptr,
		0,
		D3DCOLOR_ARGB(255, 255, 0, 0));
}

void CLogo::Release(void)
{
}
