
// DotsView.cpp : implementation of the CDotsView class
//

#include "stdafx.h"
#include "math.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Dots.h"
#endif

#include "DotsDoc.h"
#include "DotsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDotsView

IMPLEMENT_DYNCREATE(CDotsView, CView)

BEGIN_MESSAGE_MAP(CDotsView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_CHAR()
END_MESSAGE_MAP()

// CDotsView construction/destruction

CDotsView::CDotsView()
{
	// TODO: add construction code here
}

CDotsView::~CDotsView()
{
}

BOOL CDotsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CDotsView drawing

void CDotsView::OnDraw(CDC* pDC)
{
	CDotsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	for (int i = 0; i < pDoc->m_nCount; i++)
	{
		CString str;
		CString cross = _T("X");
		str.Format(_T("%d"), i + 1);
		pDC->SetTextColor(RGB(0, 0, 255));
		pDC->TextOutW(pDoc->m_pArr[i].x - 5, pDoc->m_pArr[i].y - 10, cross);
		pDC->SetTextColor(RGB(255, 170, 0));
		pDC->TextOutW(pDoc->m_pArr[i].x - 5, pDoc->m_pArr[i].y + 15, str);
	}
	if (pDoc->m_bMaxMin)
	{
		CPen pen,pen1;
		pen.CreatePen(PS_ENDCAP_FLAT, 3, RGB(255, 0, 0));
		pDC->SelectObject(&pen);
		
		pDC->MoveTo(pDoc->m_pArr[pDoc->maxi]);
		pDC->LineTo(pDoc->m_pArr[pDoc->maxj]);
		
		pen1.CreatePen(PS_ENDCAP_FLAT, 3, RGB(0, 255, 0));
		pDC->SelectObject(&pen1);

		pDC->MoveTo(pDoc->m_pArr[pDoc->mini]);
		pDC->LineTo(pDoc->m_pArr[pDoc->minj]);
	}
}


// CDotsView printing

BOOL CDotsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDotsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDotsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CDotsView diagnostics

#ifdef _DEBUG
void CDotsView::AssertValid() const
{
	CView::AssertValid();
}

void CDotsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDotsDoc* CDotsView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDotsDoc)));
	return (CDotsDoc*)m_pDocument;
}
#endif //_DEBUG


// CDotsView message handlers


void CDotsView::OnLButtonDown(UINT nFlags, CPoint point)// Стъпка 2: Създаваме функция прихващаща ляв бутон на мишката
{
	// TODO: Add your message handler code here and/or call default
	CDotsDoc* pDoc = GetDocument();
	CView::OnLButtonDown(nFlags, point);

	if (pDoc->m_bStart)
	{
		pDoc->m_pArr.Add(point);
		pDoc->m_nCount++;
		RedrawWindow();
	}
	if (pDoc->m_bRemove)
	{
		for (int i = 0; i < pDoc->m_nCount; i++)
			if (point.x < pDoc->m_pArr[i].x+10 &&
				point.x > pDoc->m_pArr[i].x-10 && 
				point.y < pDoc->m_pArr[i].y + 10 &&
				point.y > pDoc->m_pArr[i].y - 10)
			{
				pDoc->m_pArr.RemoveAt(i);
				pDoc->m_nCount--;
				RedrawWindow();
				pDoc->m_bStart = true;
				UpdateData(TRUE);
			}
		}
	if (pDoc->m_bMaxMin)
	{
		for (int i = 0; i < pDoc->m_nCount - 1; i++)
		{
			for (int j = i + 1; j < pDoc->m_nCount; j++)
			{
				if (Dist(pDoc->m_pArr[i], pDoc->m_pArr[j]) > pDoc->m_nMax)
				{
					pDoc->m_nMax = Dist(pDoc->m_pArr[i], pDoc->m_pArr[j]);
					pDoc->maxi = i;
					pDoc->maxj = j;
					RedrawWindow();
				}
				if(Dist(pDoc->m_pArr[i], pDoc->m_pArr[j]) < pDoc->m_nMin)
				{
					pDoc->m_nMin = Dist(pDoc->m_pArr[i], pDoc->m_pArr[j]);
					pDoc->mini = i;
					pDoc->minj = j;
					RedrawWindow();
				}
			}
		}
	}
}


void CDotsView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	CDotsDoc* pDoc = GetDocument();

	if (nChar == _T('S') || nChar == _T('s'))
	{
		if (!pDoc->m_bStart)
		{
			pDoc->m_pArr.RemoveAll();
			pDoc->m_nCount = 0;
			pDoc->m_bStart = true;
			pDoc->m_bMaxMin = false;
		}
	}
	if (nChar == _T('D') || nChar == _T('d'))
	{
		if (pDoc->m_bStart)
		{
			pDoc->m_bRemove = true;
			pDoc->m_bStart = false;
			pDoc->m_bMaxMin = false;
		}
	}

	if (nChar == _T('E') || nChar == _T('e'))
	{
		if (pDoc->m_bStart)
		{
			pDoc->m_bRemove = false;
			pDoc->m_bStart = false;
			pDoc->m_bMaxMin = true;
		}
		else
			pDoc->m_bStart = true;
	}

	CView::OnChar(nChar, nRepCnt, nFlags);
}


int CDotsView::Dist(CPoint Point1, CPoint Point2)
{
	return sqrt(pow(Point1.x - Point2.x, 2) + pow(Point1.y - Point2.y, 2));
}
