// PoterieDoc.cpp : implémentation de la classe CPoterieDoc
//

#include "stdafx.h"
#include "Poterie.h"

#include "PoterieDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPoterieDoc

IMPLEMENT_DYNCREATE(CPoterieDoc, CDocument)

BEGIN_MESSAGE_MAP(CPoterieDoc, CDocument)
END_MESSAGE_MAP()


// construction ou destruction de CPoterieDoc

CPoterieDoc::CPoterieDoc()
{
	// TODO : ajoutez ici le code d'une construction unique

}

CPoterieDoc::~CPoterieDoc()
{
}

BOOL CPoterieDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO : ajoutez ici le code de réinitialisation
	// (les documents SDI réutiliseront ce document)

	return TRUE;
}




// sérialisation de CPoterieDoc

void CPoterieDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO : ajoutez ici le code de stockage
	}
	else
	{
		// TODO : ajoutez ici le code de chargement
	}
}


// diagnostics pour CPoterieDoc

#ifdef _DEBUG
void CPoterieDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPoterieDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// commandes pour CPoterieDoc
