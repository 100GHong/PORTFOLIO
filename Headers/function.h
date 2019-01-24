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

static void ReportError(const WCHAR* inDescription)
{
	LPVOID lpMsgBuf;
	DWORD errorNum = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		errorNum,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	// Log
	static WCHAR temp[4096];

	va_list args;
	va_start(args, inDescription);

	_vsnwprintf_s(temp, 4096, 4096, inDescription, args);
	OutputDebugString(temp);
	OutputDebugString(_T("\n"));
}