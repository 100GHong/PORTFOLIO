#pragma once
#include "Texture.h"
class CSingleTexture :
	public CTexture
{

public:
	CSingleTexture();
	virtual ~CSingleTexture();
public:
	// CTexture��(��) ���� ��ӵ�
	virtual HRESULT InsertTexture(const wstring & wstrFilePath, const wstring & wstrStateKey = L"", const int & iCnt = 0) override;
	virtual void Release(void) override;
	virtual const TEXINFO * GetTexture(const wstring & wstrStateKey = L"", const int & iCnt = 0) override;
private:
	TEXINFO*			m_pTexInfo = nullptr;
};

