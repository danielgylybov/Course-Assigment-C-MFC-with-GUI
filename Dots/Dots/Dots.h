
// Dots.h : main header file for the Dots application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CDotsApp:
// See Dots.cpp for the implementation of this class
//

class CDotsApp : public CWinApp
{
public:
	CDotsApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDotsApp theApp;
