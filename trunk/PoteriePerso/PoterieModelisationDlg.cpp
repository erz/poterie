// PoterieModelisationDlg.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "PoteriePerso.h"
#include "PoterieModelisationDlg.h"


// Boîte de dialogue CPoterieModelisationDlg

IMPLEMENT_DYNAMIC(CPoterieModelisationDlg, CDialog)

CPoterieModelisationDlg::CPoterieModelisationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPoterieModelisationDlg::IDD, pParent)
{
/*
	CRect rect;
	GetDlgItem(IDMODELISATIONWINDOW)->GetWindowRect(rect);
	ScreenToClient(rect);
	openGLControl.Create(rect,this);
*/
}

CPoterieModelisationDlg::~CPoterieModelisationDlg()
{
}

void CPoterieModelisationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL CPoterieModelisationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	openGLControl = new COpenGLControl;

	CRect rect;

	GetDlgItem(IDMODELISATIONWINDOW)->GetWindowRect(rect);

	ScreenToClient(rect);
	//GetWindowRect(thisRect);


	openGLControl->Create(rect,this);
	return true;
}

BEGIN_MESSAGE_MAP(CPoterieModelisationDlg, CDialog)
	ON_BN_CLICKED(IDBOUTONMODELISATION, &CPoterieModelisationDlg::OnBnClickedBoutonmodelisation)
END_MESSAGE_MAP()


// Gestionnaires de messages de CPoterieModelisationDlg

void CPoterieModelisationDlg::OnBnClickedBoutonmodelisation()
{
	// TODO : ajoutez ici le code de votre gestionnaire de notification de contrôle
	OnCancel();
}
