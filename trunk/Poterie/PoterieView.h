// PoterieView.h : interface de la classe CPoterieView
//


#pragma once


class CPoterieView : public CView
{
protected: // cr�ation � partir de la s�rialisation uniquement
	CPoterieView();
	DECLARE_DYNCREATE(CPoterieView)

// Attributs
public:
	CPoterieDoc* GetDocument() const;

// Op�rations
public:

// Substitutions
public:
	virtual void OnDraw(CDC* pDC);  // substitu� pour dessiner cette vue
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Impl�mentation
public:
	virtual ~CPoterieView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Fonctions g�n�r�es de la table des messages
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // version de d�bogage dans PoterieView.cpp
inline CPoterieDoc* CPoterieView::GetDocument() const
   { return reinterpret_cast<CPoterieDoc*>(m_pDocument); }
#endif

