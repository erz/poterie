// PoterieDoc.h : interface de la classe CPoterieDoc
//


#pragma once


class CPoterieDoc : public CDocument
{
protected: // création à partir de la sérialisation uniquement
	CPoterieDoc();
	DECLARE_DYNCREATE(CPoterieDoc)

// Attributs
public:

// Opérations
public:

// Substitutions
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implémentation
public:
	virtual ~CPoterieDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Fonctions générées de la table des messages
protected:
	DECLARE_MESSAGE_MAP()
};


