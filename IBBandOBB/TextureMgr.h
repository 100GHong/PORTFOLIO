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

	HRESULT	ReadImgPath(const wstring& wstrImgPath);

	size_t	GetImageCount(const wstring& wstrObjKey, const wstring& wstrStateKey);

	void	SetMessage(const wstring& wstrMessage) { m_wstrFullPath = wstrMessage; }
	wstring&	GetFilePath(void) { return m_wstrFullPath; }

private:
	map<wstring, CTexture*>					m_MapTexture;
	wstring									m_wstrFullPath;
};

