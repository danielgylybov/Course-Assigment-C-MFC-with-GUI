
// DotsView.h : interface of the CDotsView class
//

#pragma once


class CDotsView : public CView
{
protected: // create from serialization only
	CDotsView();
	DECLARE_DYNCREATE(CDotsView)

// Attributes
public:
	CDotsDoc* GetDocument() const;
// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CDotsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	int Dist(CPoint Point1, CPoint Point2);
};

#ifndef _DEBUG  // debug version in DotsView.cpp
inline CDotsDoc* CDotsView::GetDocument() const
   { return reinterpret_cast<CDotsDoc*>(m_pDocument); }
#endif

