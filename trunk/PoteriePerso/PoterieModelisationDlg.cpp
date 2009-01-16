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

}

CPoterieModelisationDlg::~CPoterieModelisationDlg()
{
}

void CPoterieModelisationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
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
