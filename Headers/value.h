#pragma once

extern	HWND			g_hWnd;
extern	D3DXVECTOR3		g_vZoom;
extern	D3DXVECTOR3		g_vScroll;
extern	int				g_iFPS;

const int	WINCX = 800;
const int	WINCY = 600;

const int	MAPX = 2400;
const int	MAPY = 1200;

const WORD	MIN_STR = 64;
const WORD	MAX_STR = 256;

const WORD	TRACKCXY = 20;

const WORD TILECX = 130;
const WORD TILECY = 68;

const WORD TILEX = 20;
const WORD TILEY = 30;

// 키 상태 값
const DWORD		KEY_LEFT	= 0x00000001;
const DWORD		KEY_RIGHT	= 0x00000002;
const DWORD		KEY_UP		= 0x00000004;
const DWORD		KEY_DOWN	= 0x00000008;

const DWORD		KEY_SPACE = 0x00000010;
const DWORD		KEY_ENTER = 0x00000020;
const DWORD		KEY_LBUTTON = 0x00000040;
const DWORD		KEY_RBUTTON = 0x00000080;

const DWORD		KEY_1 = 0x00000100;
const DWORD		KEY_2 = 0x00000200;
const DWORD		KEY_3 = 0x00000400;
const DWORD		KEY_4 = 0x00000800;

