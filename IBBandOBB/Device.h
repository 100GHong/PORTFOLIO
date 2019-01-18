#pragma once

#include "Include.h"

class CDevice
{
	DECLARE_SINGLETON(CDevice)

private:
	CDevice();
	~CDevice();

private:
	LPDIRECT3D9			m_p3D = nullptr;
	LPDIRECT3DDEVICE9	m_pDevice = nullptr;
	LPD3DXSPRITE		m_pSprite = nullptr;
	LPD3DXFONT			m_pFont = nullptr;
	LPD3DXLINE			m_pLine = nullptr;

public:
	LPDIRECT3DDEVICE9	GetDevice(void) { return m_pDevice;  }
	LPD3DXSPRITE		GetSprite(void) { return m_pSprite;  }
	LPD3DXFONT			GetFont(void) { return m_pFont;  }
	LPD3DXLINE			GetLine(void) { return m_pLine; }

public:
	HRESULT			InitDevice(void);
	void			Release(void);
	void			Render_Begin(void);
	void			Render_End(HWND hWnd = NULL);
	
private:
	void	SetParameters(D3DPRESENT_PARAMETERS& d3dpp);


};

