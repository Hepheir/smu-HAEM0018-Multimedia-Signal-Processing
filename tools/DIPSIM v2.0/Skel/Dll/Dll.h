// Dll.h : main header file for the DLL DLL
//

#if !defined(AFX_DLL_H__D665D8A0_7D18_4A0F_8627_75648D9EC159__INCLUDED_)
#define AFX_DLL_H__D665D8A0_7D18_4A0F_8627_75648D9EC159__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDllApp
// See Dll.cpp for the implementation of this class
//

class CDllApp : public CWinApp
{
public:
	CDllApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDllApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CDllApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLL_H__D665D8A0_7D18_4A0F_8627_75648D9EC159__INCLUDED_)
