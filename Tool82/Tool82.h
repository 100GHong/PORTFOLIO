
// Tool82.h : Tool82 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CTool82App:
// �� Ŭ������ ������ ���ؼ��� Tool82.cpp�� �����Ͻʽÿ�.
//

class CTool82App : public CWinAppEx
{
public:
	CTool82App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTool82App theApp;
