#pragma once

template<typename T>
static void Safe_Delete(T& Temp)
{
	if (nullptr != Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

static D3DXVECTOR3	GetMouse(void)
{
	POINT		Pt;

	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	return D3DXVECTOR3(float(Pt.x), float(Pt.y), 0.f);
}