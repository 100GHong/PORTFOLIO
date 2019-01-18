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
		if (eTexType == TEX_MULTI)
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
