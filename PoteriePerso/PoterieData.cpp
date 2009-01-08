#include "stdafx.h"
#include "PoterieData.h"

CPoterieData::CPoterieData(CPoterieImage *im)
{
	if(im->getContour() != NULL)
	{
		int ctrWidth = im->getWidthCtr();
		int ctrHeight = im->getHeightCtr();

		base = 0; 
		int baseHauteur = 0;
		hauteur = ctrHeight; 
		ouverture = 0; 
		maxDiam = ctrWidth;
		maxDiamHauteur = 0;


		std::vector<Point *> pts = *(im->getContour());
		for (unsigned int i=0; i < pts.size(); ++i)
		{
			//std::cout << "X\t" << pts[i]->x << "\tY\t" << pts[i]->y << std::endl;
			//Il faut faire attention : l'axe des Y est invers� !
			//Avant d'avoir les bons r�sultats, on se sert des variables pour y stocker les r�sultats interm�diaires.
			//ouverture : on y met la coordonn�e x du point le plus haut.
			//hauteur : on met la coordonn�e y de ce point.
			if (hauteur > pts[i]->y)
			{
				ouverture = pts[i]->x;
				hauteur = pts[i]->y;
			}
			//maxDiam : on y met la coordonn�e x du point le plus excentr� horizontalement.
			//maxDiamHauteur : la coordonn�e y de ce point.
			if (maxDiam > pts[i]->x)
			{
				maxDiam = pts[i]->x;
				maxDiamHauteur = pts[i]->y;
			}

			//base : on y met la coordonn�e X du point le plus bas.
			if (baseHauteur < pts[i]->y)
			{
				base = pts[i]->x;
				baseHauteur = pts[i]->y;
			}
		}

		//On a toutes les variables : on les traite pour avoir les bons r�sultats.
		ouverture = (ctrWidth-ouverture)*2;
		hauteur = (baseHauteur-hauteur);
		maxDiam = (ctrWidth-maxDiam)*2;
		maxDiamHauteur = (baseHauteur-maxDiamHauteur);
		base = (ctrWidth-base)*2;
	}
}


void CPoterieData::RefreshListe(CListBox *liste)
{
	//Vidage de la liste 
	while (liste->GetItemDataPtr(0) == 0)
		liste->DeleteString(0);

	CString ouv;
	ouv.Format(CString("Ouverture : %d"), ouverture);
	CString haut;
	haut.Format(CString("Hauteur : %d"), hauteur);
	CString diam;
	diam.Format(CString("Diam�tre maximal : %d"), maxDiam);
	CString diamHaut;
	diamHaut.Format(CString("Hauteur du diam�tre max : %d"), maxDiamHauteur);
	CString bas;
	bas.Format(CString("Base : %d"), base);


	liste->AddString(ouv);
	liste->AddString(haut);
	liste->AddString(diam);
	liste->AddString(diamHaut);
	liste->AddString(bas);
}