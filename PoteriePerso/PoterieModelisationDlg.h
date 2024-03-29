#pragma once

#include "OpenGLControl.h"

// Bo�te de dialogue CPoterieModelisationDlg

class CPoterieModelisationDlg : public CDialog
{
	DECLARE_DYNAMIC(CPoterieModelisationDlg)

public:
	CPoterieModelisationDlg(CWnd* pParent = NULL);   // constructeur standard
	virtual ~CPoterieModelisationDlg();

// Donn�es de bo�te de dialogue
	enum { IDD = IDD_MODELISATION_DIALOG };

	//Initialisation
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBoutonmodelisation();
protected:
	COpenGLControl* openGLControl;
};
