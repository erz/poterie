// PoterieView.h : interface de la classe CPoterieView
//


#pragma once


class CPoterieView : public CView
{
protected: // création à partir de la sérialisation uniquement
	CPoterieView();
	DECLARE_DYNCREATE(CPoterieView)

// Attributs
public:
	CPoterieDoc* GetDocument() const;

// Opérations
public:

// Substitutions
public:
	virtual void OnDraw(CDC* pDC);  // substitué pour dessiner cette vue
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implémentation
public:
	virtual ~CPoterieView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Fonctions générées de la table des messages
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // version de débogage dans PoterieView.cpp
inline CPoterieDoc* CPoterieView::GetDocument() const
   { return reinterpret_cast<CPoterieDoc*>(m_pDocument); }
#endif

