#include "stdafx.h"
#include "MultiTexture.h"


CMultiTexture::CMultiTexture()
{
}


CMultiTexture::~CMultiTexture()
{
	Release();
}

HRESULT CMultiTexture::InsertTexture(const wstring& wstrFilePath, 
									const wstring& wstrStateKey /*= L""*/, 
									const int& iCnt /*= 0*/)
{
	TCHAR		szPath[MAX_PATH] = L"";
	vector<TEXINFO*>		vecTexture;

	for (int i = 0; i < iCnt; ++i)
	{
		wsprintf(szPath, wstrFilePath.c_str(), i);

		TEXINFO*		pTexInfo = new TEXINFO;
		ZeroMemory(pTexInfo, sizeof(TEXINFO));

		if (FAILED(D3DXGetImageInfoFromFile(szPath,
			&pTexInfo->tImgInfo)))
		{
			ERR_MSG(szPath);
			return E_FAIL;
		}

		if (FAILED(D3DXCreateTextureFromFileEx(
			CDevice::GetInstance()->GetDevice(),
			szPath,								// 이미지 파일을 읽어 들이는 경로
			pTexInfo->tImgInfo.Width,			// 이미지 가로 사이즈
			pTexInfo->tImgInfo.Height,			// 이미지 세로 사이즈
			pTexInfo->tImgInfo.MipLevels,		// 이미지 확대 축소 시 적용 값(3d 사용)
			0,									// 이미지를 읽어 들이는 방식, 기본적으로 0
			pTexInfo->tImgInfo.Format,			// 이미지 포맷 형태
			D3DPOOL_MANAGED,					// 메모리 저장 방식
			D3DX_DEFAULT,						// 텍스쳐 테두리 표현을 어떻게 할 것인가
			D3DX_DEFAULT,						// 확대, 축소 시 이미지를 어떻게 할 것인가
			NULL,								// 제거할 이미지 색상
			&pTexInfo->tImgInfo,				// 이미지 정보를 저장할 구조체
			NULL,								// 8비트 미만의 이미지 처리 방식
			&pTexInfo->pTexture)))				// 생성된 이미지 컴객체 정보를 저장할 포인터
		{
			ERR_MSG(L"MultiTexture Image Load False");
			return E_FAIL;
		}

		vecTexture.push_back(pTexInfo);
	}

	m_MapMultiTexture.insert(
		map<wstring, vector<TEXINFO*>>::value_type(wstrStateKey, vecTexture));
	
	return S_OK;
}

void CMultiTexture::Release(void)
{
	for (auto mapiter : m_MapMultiTexture)
	{
		for (size_t i = 0; i < mapiter.second.size(); ++i)
		{
			mapiter.second[i]->pTexture->Release();
			Safe_Delete(mapiter.second[i]);
		}
		mapiter.second.clear();
	}
	m_MapMultiTexture.clear();
}

const TEXINFO* CMultiTexture::GetTexture(const wstring& wstrStateKey /*= L""*/, 
										const int& iCnt /*= 0*/)
{
	auto iter = m_MapMultiTexture.find(wstrStateKey);

	if (m_MapMultiTexture.end() == iter)
		return nullptr;

	return iter->second[iCnt];
}
