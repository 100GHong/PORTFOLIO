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
		wstrFilePath.c_str(),				// �̹��� ������ �о� ���̴� ���
		m_pTexInfo->tImgInfo.Width,			// �̹��� ���� ������
		m_pTexInfo->tImgInfo.Height,		// �̹��� ���� ������
		m_pTexInfo->tImgInfo.MipLevels,		// �̹��� Ȯ�� ��� �� ���� ��(3d ���)
		0,									// �̹����� �о� ���̴� ���, �⺻������ 0
		m_pTexInfo->tImgInfo.Format,		// �̹��� ���� ����
		D3DPOOL_MANAGED,					// �޸� ���� ���
		D3DX_DEFAULT,						// �ؽ��� �׵θ� ǥ���� ��� �� ���ΰ�
		D3DX_DEFAULT,						// Ȯ��, ��� �� �̹����� ��� �� ���ΰ�
		NULL,								// ������ �̹��� ����
		&m_pTexInfo->tImgInfo,				// �̹��� ������ ������ ����ü
		NULL,								// 8��Ʈ �̸��� �̹��� ó�� ���
		&m_pTexInfo->pTexture)))			// ������ �̹��� �İ�ü ������ ������ ������
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
//string		strName = "�Ż��Ӵ�";
//
//szName = strName;
//strName = szName;
//
//strcpy_s(szName, strName.c_str());
//
//
//TCHAR		szName[128] = L"asdg";
//wstring		strName = L"�Ż��Ӵ�";
//
//szName = strName;
//strName = szName;
//
//strcpy_s(szName, strName.c_str());