// PoteriePersoDlg.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "PoteriePerso.h"
#include "PoteriePersoDlg.h"
#include "PoterieSequence.h"
#include "PoterieTraitement.h"
#include "VariablesGlobales.h"
#include "PoterieModelisationDlg.h"
#include <string>
#include <iostream>
#include <CString>
#include <afxstr.h>
#include <atlimage.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

// boîte de dialogue CAboutDlg utilisée pour la boîte de dialogue 'À propos de' pour votre application

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Données de boîte de dialogue
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

// Implémentation
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


// boîte de dialogue CPoteriePersoDlg




CPoteriePersoDlg::CPoteriePersoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPoteriePersoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPoteriePersoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDPIC, m_picture);
	DDX_Control(pDX, IDLIST, listeVars);
	DDX_Control(pDX, IDSAUVER, boutonSauver);
	DDX_Control(pDX, IDETALONNER, boutonEtalonner);
	DDX_Control(pDX, IDTEXTEBIENVENUE, texteBienvenue);
	DDX_Control(pDX, IDPREC, boutonPrecedent);
	DDX_Control(pDX, IDSUIV, boutonSuivant);
	DDX_Control(pDX, IDTEXT, texteListe);
	DDX_Control(pDX, IDC_GROUPTYPE, groupeBoutonsType);
	DDX_Control(pDX, IDC_RADIO1, radio1);
	DDX_Control(pDX, IDC_RADIO2, radio2);
	DDX_Control(pDX, IDC_RADIO3, radio3);
	DDX_Control(pDX, IDMODELISATION, boutonModelisation);
}

BEGIN_MESSAGE_MAP(CPoteriePersoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDCANCEL, &CPoteriePersoDlg::OnBnClickedCancel)
	ON_BN_CLICKED(ID_HELP, &CPoteriePersoDlg::OnBnClickedHelp)
	ON_BN_CLICKED(IDOUVRIR, &CPoteriePersoDlg::OnBnClickedOuvrir)
	ON_BN_CLICKED(IDPREC, &CPoteriePersoDlg::OnBnClickedPrec)
	ON_BN_CLICKED(IDSUIV, &CPoteriePersoDlg::OnBnClickedSuiv)
	ON_BN_CLICKED(IDSAUVER, &CPoteriePersoDlg::OnBnClickedSauver)
	ON_BN_CLICKED(IDETALONNER, &CPoteriePersoDlg::OnBnClickedEtalonner)
	ON_BN_CLICKED(IDC_RADIO2, &CPoteriePersoDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO1, &CPoteriePersoDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO3, &CPoteriePersoDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDMODELISATION, &CPoteriePersoDlg::OnBnClickedModelisation)
END_MESSAGE_MAP()


// gestionnaires de messages pour CPoteriePersoDlg

BOOL CPoteriePersoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Ajouter l'élément de menu "À propos de..." au menu Système.

	// IDM_ABOUTBOX doit se trouver dans la plage des commandes système.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Définir l'icône de cette boîte de dialogue. L'infrastructure effectue cela automatiquement
	//  lorsque la fenêtre principale de l'application n'est pas une boîte de dialogue
	SetIcon(m_hIcon, TRUE);			// Définir une grande icône
	SetIcon(m_hIcon, FALSE);		// Définir une petite icône

	// TODO : ajoutez ici une initialisation supplémentaire

	return TRUE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
}

void CPoteriePersoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}


// Si vous ajoutez un bouton Réduire à votre boîte de dialogue, vous devez utiliser le code ci-dessous
//  pour dessiner l'icône. Pour les applications MFC utilisant le modèle Document/Vue,
//  cela est fait automatiquement par l'infrastructure.

void CPoteriePersoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // contexte de périphérique pour la peinture

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrer l'icône dans le rectangle client
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dessiner l'icône
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// Le système appelle cette fonction pour obtenir le curseur à afficher lorsque l'utilisateur fait glisser
//  la fenêtre réduite.
HCURSOR CPoteriePersoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPoteriePersoDlg::OnBnClickedCancel()
{
	// TODO : ajoutez ici le code de votre gestionnaire de notification de contrôle
	OnCancel();

	//Destruction des fenetre OpenCv
	cvDestroyWindow("Opencv");
	cvDestroyWindow("contours");
	cvDestroyWindow("CLIQUER SUR LES DEUX EXTREMITES DE L'ETALON");
	cvDestroyWindow("Interpolation");
}

void CPoteriePersoDlg::OnBnClickedHelp()
{
	// TODO : ajoutez ici le code de votre gestionnaire de notification de contrôle
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CPoteriePersoDlg::OnBnClickedOuvrir()
{
	// TODO : ajoutez ici le code de votre gestionnaire de notification de contrôle
	LPMALLOC pMalloc; 
	/* Gets the Shell's default allocator */ 
	if (::SHGetMalloc(&pMalloc) == NOERROR) 
	{ 
		BROWSEINFO bi; 
		char pszBuffer[MAX_PATH]; 
		LPITEMIDLIST pidl; 
		// Get help on BROWSEINFO struct - it's got all the bit settings. 
		bi.hwndOwner = GetSafeHwnd(); 
		bi.pidlRoot = NULL; 
		bi.pszDisplayName = (LPWSTR)pszBuffer; 
		bi.lpszTitle = _T("Répertoire de la séquence d'image"); 
		bi.ulFlags = BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS |BIF_NEWDIALOGSTYLE; 
		bi.lpfn = NULL; 
		bi.lParam = 0; 
		
		// This next call issues the dialog box. 
		if ((pidl = ::SHBrowseForFolder(&bi)) != NULL) 
		{ 
			if (::SHGetPathFromIDList(pidl, LPWSTR(pszBuffer))) 
		   { 
			   				
				//Affichage de l'ihm
			   	boutonEtalonner.ShowWindow(SW_HIDE);
				groupeBoutonsType.ShowWindow(SW_HIDE);
				radio1.ShowWindow(SW_HIDE);
				radio2.ShowWindow(SW_HIDE);
				radio3.ShowWindow(SW_HIDE);
				listeVars.ShowWindow(SW_SHOW);
				boutonModelisation.ShowWindow(SW_SHOW);
				boutonSauver.ShowWindow(SW_SHOW);
				boutonPrecedent.ShowWindow(SW_SHOW);
				boutonSuivant.ShowWindow(SW_SHOW);
				texteListe.ShowWindow(SW_SHOW);
				texteBienvenue.SetWindowTextW(CString("...TRAITEMENT EN COURS...\nveuillez patienter"));

				// At this point pszBuffer contains the selected path */. 
				::SetCurrentDirectory(LPWSTR(pszBuffer));
				
				//Sequence d'image
				if (seq != NULL)
					seq = new CPoterieSequence();
				
				CString rep;
				rep = Char2CString(pszBuffer);
				//MessageBox(rep);
				seq->setRepertoireCourant(rep);
				//Parcours des fichiers du dossier
		
				CFileFind finder;
		
				BOOL bWorking = finder.FindFile(CString("*.bmp*"));

				
				while (bWorking)
				{
					bWorking = finder.FindNextFile();
					//MessageBox( finder.GetFileName());

					//Ajout de l'image
					seq->addImage(finder.GetFileName());
				}

				//Remplissage des valeurs en fonction de la forme
				remplirValeursSelonForme();

				//Traitement des données
				traitementTotal();

				//Petites modifs d'IHM
				texteBienvenue.ShowWindow(SW_HIDE);
				m_picture.RedrawWindow();

				//Rafraichissement
				refresh();
			} 
			// Free the PIDL allocated by SHBrowseForFolder. 
			pMalloc->Free(pidl); 
		} 
		// Release the shell's allocator. 
		pMalloc->Release(); 
	}
}
void CPoteriePersoDlg::OnBnClickedPrec()
{
	// TODO : ajoutez ici le code de votre gestionnaire de notification de contrôle
	if (seq != NULL)
	{
		seq->prevImage();
		refresh();
	}
}

void CPoteriePersoDlg::OnBnClickedSuiv()
{
	// TODO : ajoutez ici le code de votre gestionnaire de notification de contrôle
	if (seq != NULL)
	{
		seq->nextImage();
		refresh();
	}
}
void CPoteriePersoDlg::OnBnClickedSauver()
{
	// TODO : ajoutez ici le code de votre gestionnaire de notification de contrôle
	CFileDialog fOpenDlg(FALSE, CString("csv"), NULL, OFN_HIDEREADONLY, CString("Donnees Poterie (*.csv)|*.csv||"), this);
  
	if(fOpenDlg.DoModal()==IDOK)
	{
		//On enregistre les données dans le fichier choisi
		enregistrerDonnees(fOpenDlg.GetPathName());
		MessageBox(CString("Vos données ont été enregistrées avec succès."));
	}

}

void CPoteriePersoDlg::OnBnClickedEtalonner()
{
	//On demande le fichier d'étalon
	CFileDialog fOpenDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, CString("Image Etalon (*.bmp)|*.bmp||"), this);
	if (fOpenDlg.DoModal() == IDOK)
	{
		etalonnerAvecImage(fOpenDlg.GetPathName());
	}
}

void CPoteriePersoDlg::OnBnClickedRadio1()
{
	formePoterie = 1;
}

void CPoteriePersoDlg::OnBnClickedRadio2()
{
	formePoterie = 2;	
}

void CPoteriePersoDlg::OnBnClickedRadio3()
{
	formePoterie = 3;
}

void CPoteriePersoDlg::OnBnClickedModelisation()
{
	//Creation de la fenete modelisation
	CPoterieModelisationDlg dlg;
	dlg.DoModal();
}
