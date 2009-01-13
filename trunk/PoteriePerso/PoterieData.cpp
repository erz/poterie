#include "stdafx.h"
#include "PoterieData.h"

#include "VariablesGlobales.h"

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
			//Il faut faire attention : l'axe des Y est inversé !
			//Avant d'avoir les bons résultats, on se sert des variables pour y stocker les résultats intermédiaires.
			//ouverture : on y met la coordonnée x du point le plus haut.
			//hauteur : on met la coordonnée y de ce point.
			if (hauteur > pts[i]->y)
			{
				ouverture = pts[i]->x;
				hauteur = pts[i]->y;
			}
			//maxDiam : on y met la coordonnée x du point le plus excentré horizontalement.
			//maxDiamHauteur : la coordonnée y de ce point.
			if (maxDiam > pts[i]->x)
			{
				maxDiam = pts[i]->x;
				maxDiamHauteur = pts[i]->y;
			}

			//base : on y met la coordonnée X du point le plus bas.
			if (baseHauteur < pts[i]->y)
			{
				base = pts[i]->x;
				baseHauteur = pts[i]->y;
			}
		}

		//On a toutes les variables : on les traite pour avoir les bons résultats.
		ouverture = (ctrWidth-ouverture)*2;
		hauteur = (baseHauteur-hauteur);
		maxDiam = (ctrWidth-maxDiam)*2;
		maxDiamHauteur = (baseHauteur-maxDiamHauteur);
		base = (ctrWidth-base)*2;
	}
}

void CPoterieData::CentreDeMasse(CPoterieImage * im)
{
	int indiceMilieu = pts.size()/2-1;
	int deltaPartieSup = abs(eHaute-eMoyenne)/indiceMilieu;
	int deltaPartieInf = abs(eMoyenne-eBasse)/indiceMilieu;
	
	int hauteurInterieure= pts[0]->y+eBase;
	unsigned int i=pts.size()-1;
	int j,k=1;
	while(i>=0 && pts[i]->y>hauteurInterieure)
	{
		if(i>indiceMilieu)
		{
			ptsProfilInterne[i]->x=pts[i]->x+deltaPartieSup*j;
			ptsProfilInterne[i]->y=pts[i]->y;
			++j;
		}
		else
		{
			ptsProfilInterne[i]->x=pts[i]->x+deltaPartieInf*j;
			ptsProfilInterne[i]->y=pts[i]->y;
			++k;
		}
		--i;
	}


}
void CPoterieData::RefreshListe(CListBox *liste)
{
	//Vidage de la liste 
	while (liste->GetItemDataPtr(0) == 0)
		liste->DeleteString(0);

	//On crée les strings d'affichage (on n'oublie pas l'echelle!)
	CString ouv;
	ouv.Format(CString("Ouverture : %.4lf cm"), ouverture*echelle);
	CString haut;
	haut.Format(CString("Hauteur : %.4lf cm"), hauteur*echelle);
	CString diam;
	diam.Format(CString("Diamètre maximal : %.4lf cm"), maxDiam*echelle);
	CString diamHaut;
	diamHaut.Format(CString("Hauteur du diamètre max : %.4lf cm"), maxDiamHauteur*echelle);
	CString bas;
	bas.Format(CString("Base : %.4lf cm"), base*echelle);


	liste->AddString(ouv);
	liste->AddString(haut);
	liste->AddString(diam);
	liste->AddString(diamHaut);
	liste->AddString(bas);
}