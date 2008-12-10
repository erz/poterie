// PoterieView.cpp : impl�mentation de la classe CPoterieView
//

#include "stdafx.h"
#include "Poterie.h"

#include "PoterieDoc.h"
#include "PoterieView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPoterieView

IMPLEMENT_DYNCREATE(CPoterieView, CView)

BEGIN_MESSAGE_MAP(CPoterieView, CView)
	// Commandes d'impression standard
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// construction ou destruction�de CPoterieView

CPoterieView::CPoterieView()
{
	// TODO : ajoutez ici du code de construction

}

CPoterieView::~CPoterieView()
{
}

BOOL CPoterieView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO : changez ici la classe ou les styles Window en modifiant
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// dessin de CPoterieView

void CPoterieView::OnDraw(CDC* /*pDC*/)
{
	CPoterieDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO : ajoutez ici le code de dessin pour les donn�es natives
}


// impression de CPoterieView

BOOL CPoterieView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// pr�paration par d�faut
	return DoPreparePrinting(pInfo);
}

void CPoterieView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO : ajoutez une initialisation suppl�mentaire avant l'impression
}

void CPoterieView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO : ajoutez un nettoyage apr�s l'impression
}


// diagnostics pour CPoterieView

#ifdef _DEBUG
void CPoterieView::AssertValid() const
{
	CView::AssertValid();
}

void CPoterieView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPoterieDoc* CPoterieView::GetDocument() const // la version non d�bogu�e est en ligne
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPoterieDoc)));
	return (CPoterieDoc*)m_pDocument;
}
#endif //_DEBUG


// gestionnaires de messages pour CPoterieView




