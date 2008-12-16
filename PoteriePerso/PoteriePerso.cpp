// PoteriePerso.cpp : Définit les comportements de classe pour l'application.
//

#include "stdafx.h"
#include "PoteriePerso.h"
#include "PoterieTraitement.h"
#include "Console.h"
#include "PoteriePersoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPoteriePersoApp

BEGIN_MESSAGE_MAP(CPoteriePersoApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// construction CPoteriePersoApp

CPoteriePersoApp::CPoteriePersoApp()
{
	EnableHtmlHelp();

	// TODO : ajoutez ici du code de construction,
	// Placez toutes les initialisations significatives dans InitInstance
}


// Seul et unique objet CPoteriePersoApp

CPoteriePersoApp theApp;


// initialisation de CPoteriePersoApp

BOOL CPoteriePersoApp::InitInstance()
{
	// InitCommonControlsEx() est requis sur Windows XP si le manifeste de l'application
	// spécifie l'utilisation de ComCtl32.dll version 6 ou ultérieure pour activer les
	// styles visuels.  Dans le cas contraire, la création de fenêtres échouera.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// À définir pour inclure toutes les classes de contrôles communs à utiliser
	// dans votre application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Initialisation standard
	// Si vous n'utilisez pas ces fonctionnalités et que vous souhaitez réduire la taille
	// de votre exécutable final, vous devez supprimer ci-dessous
	// les routines d'initialisation spécifiques dont vous n'avez pas besoin.
	// Changez la clé de Registre sous laquelle nos paramètres sont enregistrés
	// TODO : modifiez cette chaîne avec des informations appropriées,
	// telles que le nom de votre société ou organisation
	SetRegistryKey(_T("Applications locales générées par AppWizard"));

	// créer une console
    ::AllocConsole();
    // synchroniser la CRT
    InitializeConsoleStdIO();
	

	CPoteriePersoDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	if (nResponse == IDCANCEL)
	{
		// TODO : placez ici le code définissant le comportement lorsque la boîte de dialogue est
		//  fermée avec Annuler
	}

	

	// Lorsque la boîte de dialogue est fermée, retourner FALSE afin de quitter
	//  l'application, plutôt que de démarrer la pompe de messages de l'application.
	return FALSE;
}
