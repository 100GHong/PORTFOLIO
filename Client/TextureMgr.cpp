#include "stdafx.h"
#include "TextureMgr.h"

IMPLEMENT_SINGLETON(CTextureMgr)

CTextureMgr::CTextureMgr()
{
}


CTextureMgr::~CTextureMgr()
{
	Release();
}

HRESULT CTextureMgr::InsertTexture(const wstring& wstrFilePath, 
									const wstring& wstrObjKey, 
									TEXTYPE eTexType, 
									const wstring& wstrStateKey /*= L""*/, 
									const int& iCnt /*= 0*/)
{
	auto		iter = m_MapTexture.find(wstrObjKey);

	m_wstrFullPath = wstrFilePath;

	//wcout << wstrFilePath << endl;

	if (iter == m_MapTexture.end())
	{
		CTexture*			pTexture = nullptr;

		switch (eTexType)
		{
		case TEX_SINGLE:
			pTexture = new CSingleTexture;
			break;

		case TEX_MULTI:
			pTexture = new CMultiTexture;
			break;
		}

		if (FAILED(pTexture->InsertTexture(wstrFilePath, wstrStateKey, iCnt)))
		{
			ERR_MSG(wstrObjKey.c_str());
			return E_FAIL;
		}

		m_MapTexture.insert(map<wstring, CTexture*>::value_type(wstrObjKey, pTexture));
	}
	else
	{
		if (TEX_MULTI == eTexType)
		{
			if (iter->second->GetTexture(wstrStateKey) == nullptr)
			{
				iter->second->InsertTexture(wstrFilePath, wstrStateKey, iCnt);
			}
		}
	}
	
	return S_OK;
}

void CTextureMgr::Release(void)
{
	for (auto iter : m_MapTexture)
	{
		Safe_Delete(iter.second);
	}
	m_MapTexture.clear();
}

const TEXINFO* CTextureMgr::GetTexture(const wstring& wstrObjKey, 
										const wstring& wstrStateKey /*= L""*/, 
										const int& iCnt /*= 0*/)
{
	auto iter = m_MapTexture.find(wstrObjKey);

	if (m_MapTexture.end() == iter)
		return nullptr;

	return iter->second->GetTexture(wstrStateKey, iCnt);
}

HRESULT CTextureMgr::ReadImgPath(const wstring& wstrImgPath)
{
	wifstream			LoadFile;

	LoadFile.open(wstrImgPath.c_str(), ios::in);

	TCHAR	szObjKey[MIN_STR] = L"";
	TCHAR	szStateKey[MIN_STR] = L"";
	TCHAR	szCount[MIN_STR] = L"";
	TCHAR	szImgPath[MAX_PATH] = L"";

	while (!LoadFile.eof())
	{

		LoadFile.getline(szObjKey, MIN_STR, '|');
		LoadFile.getline(szStateKey, MIN_STR, '|');
		LoadFile.getline(szCount, MIN_STR, '|');
		LoadFile.getline(szImgPath, MAX_PATH);

		int iCount = _ttoi(szCount);
	
		if (FAILED(InsertTexture(szImgPath, szObjKey, TEX_MULTI, szStateKey, iCount)))
		{
			return E_FAIL;
		}
	}

	LoadFile.close();

	return S_OK;
}

size_t CTextureMgr::GetImageCount(const wstring& wstrObjKey, const wstring& wstrStateKey)
{
	auto	iter = m_MapTexture.find(wstrObjKey);

	if (iter == m_MapTexture.end())
		return -1;

	return dynamic_cast<CMultiTexture*>(iter->second)->GetImageCount(wstrStateKey);
}
