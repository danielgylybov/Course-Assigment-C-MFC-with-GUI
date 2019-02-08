
// DotsDoc.h : interface of the CDotsDoc class
//


#pragma once


class CDotsDoc : public CDocument
{
protected: // create from serialization only
	CDotsDoc();
	DECLARE_DYNCREATE(CDotsDoc)

// Attributes
public:
	CArray<CPoint, CPoint> m_pArr;
	// Масив съхраняващ въведените точки (Стъпка 1)
	int m_nCount;
	// Брой въведени точки
	bool m_bStart, m_bRemove, m_bMaxMin;
	// Променливи връщащи истина, в зависимост от режима да въвеждане
	int m_nMin, m_nMax;
	// Променливи съхраняващи разтоянанията м/у максималното и минималното разстояние на две точки
	int mini, minj, maxi, maxj;
	// Индекси на на максималната и минималната точка в масива


// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CDotsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
