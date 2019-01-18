#pragma once
#include "SingleTexture.h"
#include "MultiTexture.h"

class CTextureMgr
{
	DECLARE_SINGLETON(CTextureMgr)

private:
	CTextureMgr();
	~CTextureMgr();
public:
	HRESULT		InsertTexture(const wstring& wstrFilePath, 
								const wstring& wstrObjKey,
								TEXTYPE eTexType, 
								const wstring& wstrStateKey = L"", 
								const int& iCnt = 0);

	void		Release(void);

	const TEXINFO* GetTexture(const wstring& wstrObjKey,
							  const wstring& wstrStateKey = L"",
							  const int& iCnt = 0);

private:
	map<wstring, CTexture*>					m_MapTexture;
};

