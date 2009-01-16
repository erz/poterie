#pragma once


// Boîte de dialogue CPoterieModelisationDlg

class CPoterieModelisationDlg : public CDialog
{
	DECLARE_DYNAMIC(CPoterieModelisationDlg)

public:
	CPoterieModelisationDlg(CWnd* pParent = NULL);   // constructeur standard
	virtual ~CPoterieModelisationDlg();

// Données de boîte de dialogue
	enum { IDD = IDD_MODELISATION_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBoutonmodelisation();
};
