// Poterie.cpp : D�finit les comportements de classe pour l'application.
//

#include "stdafx.h"
#include "Poterie.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "PoterieDoc.h"
#include "PoterieView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPoterieApp

BEGIN_MESSAGE_MAP(CPoterieApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CPoterieApp::OnAppAbout)
	// Commandes de fichier standard
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// construction CPoterieApp

CPoterieApp::CPoterieApp()
{
	EnableHtmlHelp();

	// TODO�: ajoutez ici du code de construction,
	// Placez toutes les initialisations significatives dans InitInstance
}


// Seul et unique objet CPoterieApp

CPoterieApp theApp;


// initialisation de CPoterieApp

BOOL CPoterieApp::InitInstance()
{
	// InitCommonControlsEx() est requis sur Windows�XP si le manifeste de l'application
	// sp�cifie l'utilisation de ComCtl32.dll version�6 ou ult�rieure pour activer les
	// styles visuels.  Dans le cas contraire, la cr�ation de fen�tres �chouera.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// � d�finir pour inclure toutes les classes de contr�les communs � utiliser
	// dans votre application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// Initialiser les biblioth�ques OLE
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// Initialisation standard
	// Si vous n'utilisez pas ces fonctionnalit�s et que vous souhaitez r�duire la taille
	// de votre ex�cutable final, vous devez supprimer ci-dessous
	// les routines d'initialisation sp�cifiques dont vous n'avez pas besoin.
	// Changez la cl� de Registre sous laquelle nos param�tres sont enregistr�s
	// TODO : modifiez cette cha�ne avec des informations appropri�es,
	// telles que le nom de votre soci�t� ou organisation
	SetRegistryKey(_T("Applications locales g�n�r�es par AppWizard"));
	LoadStdProfileSettings(4);  // Charge les options de fichier INI standard (y compris les derniers fichiers utilis�s)
	// Inscrire les mod�les de document de l'application. Ces mod�les
	//  lient les documents, fen�tres frame et vues entre eux
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_PoterieTYPE,
		RUNTIME_CLASS(CPoterieDoc),
		RUNTIME_CLASS(CChildFrame), // frame enfant MDI personnalis�
		RUNTIME_CLASS(CPoterieView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// cr�e la fen�tre frame MDI principale
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// appelle DragAcceptFiles uniquement s'il y a un suffixe
	//  Dans une application MDI, cet appel doit avoir lieu juste apr�s la d�finition de m_pMainWnd


	// Analyser la ligne de commande pour les commandes shell standard, DDE, ouverture de fichiers
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// Commandes de dispatch sp�cifi�es sur la ligne de commande. Retournent FALSE si
	// l'application a �t� lanc�e avec /RegServer, /Register, /Unregserver ou /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// La fen�tre principale a �t� initialis�e et peut donc �tre affich�e et mise � jour
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}



// bo�te de dialogue CAboutDlg utilis�e pour la bo�te de dialogue '� propos de' pour votre application

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Donn�es de bo�te de dialogue
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

// Impl�mentation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// Commande App pour ex�cuter la bo�te de dialogue
void CPoterieApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// gestionnaires de messages pour CPoterieApp

