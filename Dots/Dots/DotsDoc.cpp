
// DotsDoc.cpp : implementation of the CDotsDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Dots.h"
#endif

#include "DotsDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDotsDoc

IMPLEMENT_DYNCREATE(CDotsDoc, CDocument)

BEGIN_MESSAGE_MAP(CDotsDoc, CDocument)
END_MESSAGE_MAP()


// CDotsDoc construction/destruction

CDotsDoc::CDotsDoc()
{
	// TODO: add one-time construction code here
	m_pArr.RemoveAll();
	m_nCount = 0;
	m_bStart = false;
	m_bRemove = false;
	m_bMaxMin = false;
	m_nMax = 0;
	m_nMin = 1000;
	mini = 0;
	minj = 0;
	maxi = 0;
	maxj = 0;
}

CDotsDoc::~CDotsDoc()
{
}

BOOL CDotsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	m_pArr.RemoveAll();
	m_nCount = 0;
	m_bStart = false;
	m_bRemove = false;
	m_bMaxMin = false;
	m_nMax = 0;
	m_nMin = 1000;
	mini = 0;
	minj = 0;
	maxi = 0;
	maxj = 0;

	return TRUE;
}




// CDotsDoc serialization

void CDotsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		m_bStart = false;
		ar << m_nCount;
		for (int i = 0; i < m_nCount; i++)
		{
			ar << m_pArr[i];
		}
	}
	else
	{
		// TODO: add loading code here
		CPoint pt;
		m_pArr.RemoveAll();
		m_bStart =  false;
		ar >> m_nCount;
		for (int i = 0; i < m_nCount; i++)
		{
			ar >> pt;
			m_pArr.Add(pt);
		}
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CDotsDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CDotsDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CDotsDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CDotsDoc diagnostics

#ifdef _DEBUG
void CDotsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDotsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CDotsDoc commands
