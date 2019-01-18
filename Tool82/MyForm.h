#pragma once
#include "afxwin.h"



// CMyForm �� ���Դϴ�.

class CMyForm : public CFormView
{
	DECLARE_DYNCREATE(CMyForm)

protected:
	CMyForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CMyForm();

public:
	int				m_Radio;
	int				m_iCombo = 0;
	CComboBox		m_TrackCombo;
	CComboBox		m_MapCombo;
	CComboBox		m_ObjCombo;
	CComboBox		m_SupportCombo;
	CComboBox		m_MonCombo;
	CButton			m_RadioCtrl;
	bool			m_bTrackRadio;
	bool			m_bObjRadio;


#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYFORM };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void SetRadioStatus(UINT value);
	virtual void OnInitialUpdate();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnSaveButton();
	afx_msg void OnLoadButton();
	afx_msg void OnCbnSelchangeCombo4();
	afx_msg void OnCbnSelchangeCombo5();
};


