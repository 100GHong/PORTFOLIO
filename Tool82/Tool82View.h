
// Tool82View.h : CTool82View Ŭ������ �������̽�
//

#pragma once

#include "Include.h"
class CTool82Doc;
class CDevice;
class CBackGround;
class CMyForm;

class CTool82View : public CScrollView
{
protected: // serialization������ ��������ϴ�.
	CTool82View();
	DECLARE_DYNCREATE(CTool82View)

private:
	void			ImageLoad(void);

// Ư���Դϴ�.
public:
	CTool82Doc* GetDocument() const;

// �۾��Դϴ�.
public:
	CBackGround*				m_pBackGround = nullptr;
	CDevice*					m_pDevice = nullptr;
	CMyForm*					m_pMyForm = nullptr;
	int*						m_pStateNum = nullptr;
	int*						m_pIndexNum = nullptr;
	POINT*						m_pStartPT = nullptr;
	RECT						m_rt = {};
	bOBJ*						m_pSampleImg = nullptr;
	SUP*						m_pSampleSup = nullptr;
	MON*						m_pSampleMon = nullptr;
	list<tRECT*>				m_Rectlist[RT_END];
	list<tRECT*>				m_Map2list;
	list<bOBJ*>					m_BObjlist[BG_END];
	list<SUP*>					m_Suplist[SP_END];
	list<MON*>					m_Monlist;

	POINT		GetCur(void);

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CTool82View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();

public:
	void	Release(void);
//	virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // Tool82View.cpp�� ����� ����
inline CTool82Doc* CTool82View::GetDocument() const
   { return reinterpret_cast<CTool82Doc*>(m_pDocument); }
#endif

