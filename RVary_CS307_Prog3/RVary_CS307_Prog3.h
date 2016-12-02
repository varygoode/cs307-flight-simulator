
// RVary_CS307_Prog3.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CRVary_CS307_Prog3App:
// See RVary_CS307_Prog3.cpp for the implementation of this class
//

class CRVary_CS307_Prog3App : public CWinApp
{
public:
	CRVary_CS307_Prog3App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CRVary_CS307_Prog3App theApp;