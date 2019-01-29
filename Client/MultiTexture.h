#pragma once
#include "Texture.h"
class CMultiTexture :
	public CTexture
{
public:
	CMultiTexture();
	virtual ~CMultiTexture();
public:
	virtual HRESULT InsertTexture(const wstring& wstrFilePath, 
									const wstring& wstrStateKey = L"", 
									const int& iCnt = 0) override;
	virtual void Release(void) override;
	virtual const TEXINFO* GetTexture(const wstring& wstrStateKey = L"", 
										const int& iCnt = 0) override;

public:
	size_t	GetImageCount(const wstring& wstrStateKey);

private:
	map<wstring, vector<TEXINFO*>>			m_MapMultiTexture;
};

