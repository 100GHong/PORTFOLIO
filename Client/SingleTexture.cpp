#include "stdafx.h"
#include "SingleTexture.h"


CSingleTexture::CSingleTexture()
{
}


CSingleTexture::~CSingleTexture()
{
	Release();
}

HRESULT CSingleTexture::InsertTexture(	const wstring & wstrFilePath, 
										const wstring & wstrStateKey , 
										const int & iCnt)
{
	m_pTexInfo = new TEXINFO;
	ZeroMemory(m_pTexInfo, sizeof(TEXINFO));

	if (FAILED(D3DXGetImageInfoFromFile(wstrFilePath.c_str(), 
										&m_pTexInfo->tImgInfo)))
	{
		ERR_MSG(wstrFilePath.c_str());
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFileEx(
		CDevice::GetInstance()->GetDevice(), 
		wstrFilePath.c_str(),				// 이미지 파일을 읽어 들이는 경로
		m_pTexInfo->tImgInfo.Width,			// 이미지 가로 사이즈
		m_pTexInfo->tImgInfo.Height,		// 이미지 세로 사이즈
		m_pTexInfo->tImgInfo.MipLevels,		// 이미지 확대 축소 시 적용 값(3d 사용)
		0,									// 이미지를 읽어 들이는 방식, 기본적으로 0
		m_pTexInfo->tImgInfo.Format,		// 이미지 포맷 형태
		D3DPOOL_MANAGED,					// 메모리 저장 방식
		D3DX_DEFAULT,						// 텍스쳐 테두리 표현을 어떻게 할 것인가
		D3DX_DEFAULT,						// 확대, 축소 시 이미지를 어떻게 할 것인가
		NULL,								// 제거할 이미지 색상
		&m_pTexInfo->tImgInfo,				// 이미지 정보를 저장할 구조체
		NULL,								// 8비트 미만의 이미지 처리 방식
		&m_pTexInfo->pTexture)))			// 생성된 이미지 컴객체 정보를 저장할 포인터
	{
		ERR_MSG(L"SingleTexture Image Load False");
		return E_FAIL;
	}



	return S_OK;
}

void CSingleTexture::Release(void)
{
	m_pTexInfo->pTexture->Release();
	Safe_Delete(m_pTexInfo);
}

const TEXINFO * CSingleTexture::GetTexture(	const wstring & wstrStateKey, 
											const int & iCnt)
{
	return m_pTexInfo;
}


//char		szName[128] = "asdg";
//string		strName = "신사임당";
//
//szName = strName;
//strName = szName;
//
//strcpy_s(szName, strName.c_str());
//
//
//TCHAR		szName[128] = L"asdg";
//wstring		strName = L"신사임당";
//
//szName = strName;
//strName = szName;
//
//strcpy_s(szName, strName.c_str());