// Poterie.h�: fichier d'en-t�te principal pour l'application Poterie
//
#pragma once

#ifndef __AFXWIN_H__
	#error "incluez 'stdafx.h' avant d'inclure ce fichier pour PCH"
#endif

#include "resource.h"       // symboles principaux


// CPoterieApp:
// Consultez Poterie.cpp pour l'impl�mentation de cette classe
//

class CPoterieApp : public CWinApp
{
public:
	CPoterieApp();


// Substitutions
public:
	virtual BOOL InitInstance();

// Impl�mentation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPoterieApp theApp;