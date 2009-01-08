// PoteriePersoDlg.h : fichier d'en-t�te
//


#pragma once
#include "afxwin.h"
#include <afxstr.h>
#include <atlimage.h>
#include "Outils.h"

// bo�te de dialogue CPoteriePersoDlg
class CPoteriePersoDlg : public CDialog
{
// Construction
public:
	CPoteriePersoDlg(CWnd* pParent = NULL);	// constructeur standard

// Donn�es de bo�te de dialogue
	enum { IDD = IDD_POTERIEPERSO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Prise en charge de DDX/DDV


// Impl�mentation
protected:
	HICON m_hIcon;

	// Fonctions g�n�r�es de la table des messages
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
public:
	afx_msg void OnBnClickedHelp();
public:
	afx_msg void OnBnClickedOuvrir();
private:
	ATL::CImage m_image;
	CStatic m_picture;
public:
	afx_msg void OnBnClickedPrec();
public:
	afx_msg void OnBnClickedSuiv();
public:
	afx_msg void refresh();
	afx_msg void OnBnClickedSauver();
	CListBox listeVars;
	CButton boutonSauver;
	CButton boutonEtalonner;
	CStatic texteBienvenue;
	CButton boutonPrecedent;
	CButton boutonSuivant;
	CStatic texteListe;
	afx_msg void OnBnClickedEtalonner();
};
