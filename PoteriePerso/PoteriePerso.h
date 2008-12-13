// PoteriePerso.h : fichier d'en-tête principal pour l'application PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "incluez 'stdafx.h' avant d'inclure ce fichier pour PCH"
#endif


#include "resource.h"		// symboles principaux

// CPoteriePersoApp:
// Consultez PoteriePerso.cpp pour l'implémentation de cette classe
//

class CPoteriePersoApp : public CWinApp
{
public:
	CPoteriePersoApp();

// Substitutions
	public:
	virtual BOOL InitInstance();

// Implémentation

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};

extern CPoteriePersoApp theApp;