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
			szPath,								// �̹��� ������ �о� ���̴� ���
			pTexInfo->tImgInfo.Width,			// �̹��� ���� ������
			pTexInfo->tImgInfo.Height,			// �̹��� ���� ������
			pTexInfo->tImgInfo.MipLevels,		// �̹��� Ȯ�� ��� �� ���� ��(3d ���)
			0,									// �̹����� �о� ���̴� ���, �⺻������ 0
			pTexInfo->tImgInfo.Format,			// �̹��� ���� ����
			D3DPOOL_MANAGED,					// �޸� ���� ���
			D3DX_DEFAULT,						// �ؽ��� �׵θ� ǥ���� ��� �� ���ΰ�
			D3DX_DEFAULT,						// Ȯ��, ��� �� �̹����� ��� �� ���ΰ�
			NULL,								// ������ �̹��� ����
			&pTexInfo->tImgInfo,				// �̹��� ������ ������ ����ü
			NULL,								// 8��Ʈ �̸��� �̹��� ó�� ���
			&pTexInfo->pTexture)))				// ������ �̹��� �İ�ü ������ ������ ������
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
