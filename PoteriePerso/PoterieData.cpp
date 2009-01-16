#include "stdafx.h"
#include "PoterieData.h"
#include <math.h>

#include <algorithm>

#include "VariablesGlobales.h"

#define PI 3.14159265

CPoterieData::CPoterieData(CPoterieImage *im)
{
	if(im->getContour() != NULL)
	{
		int ctrWidth = im->getWidthCtr();
		int ctrHeight = im->getHeightCtr();
		
		base = 0; 
		baseHauteur = 0;
		hauteur = ctrHeight; 
		ouverture = 0; 
		maxDiam = ctrWidth;
		maxDiamHauteur = 0;

		//epaisseurs;
		eHaute=epaisseurHaute/echelle;
		eMoyenne=epaisseurMilieu/echelle;
		eBasse=epaisseurBasse/echelle;
		eBase=epaisseurBase/echelle;
		pts = *(im->getContour());
	
		for (unsigned int i=0; i < pts.size(); ++i)
		{
			
			//cout << "X\t" << pts[i]->x << "\tY\t" << pts[i]->y << endl;
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
		
		volume=0;
		surface=0;
		for (unsigned int i=0; i < pts.size()-1; i++)
		{
			float base1=(ctrWidth-pts[i]->x)*echelle;
			float base2=(ctrWidth-pts[i+1]->x)*echelle;
			float generatrice=sqrt(pow((float)(pts[i]->x-pts[i+1]->x)*echelle,2)+pow((float)(pts[i]->y-pts[i+1]->y)*echelle,2) );
			float hauteurSection=abs((pts[i]->y-pts[i+1]->y))*echelle;

			//volume+=(PI*(hauteurSection)*(base1*base1+base1*base2+base2*base2))/3.0;
			volume+=((PI*pow(base2,2)*hauteurSection)/3.0)*(1+(base1/base2)+(pow(base1,2)/pow(base2,2)));
			surface+=PI*(base1+base2)*generatrice;

		}

		CentreDeMasse(im);
		//On a toutes les variables : on les traite pour avoir les bons résultats.
		ouverture = (ctrWidth-ouverture)*2;
		hauteur = (baseHauteur-hauteur);
		maxDiam = (ctrWidth-maxDiam)*2;
		maxDiamHauteur = (baseHauteur-maxDiamHauteur);
		base = (ctrWidth-base)*2;
		circularite= pow(surface,3)/pow(volume,2);
	}
}

void CPoterieData::CentreDeMasse(CPoterieImage * im)
{
	//cout<<"calcul centre de masse"<<endl;
	int indiceMilieu = pts.size()/2-1;
	float deltaPartieSup = abs(eHaute-eMoyenne)/indiceMilieu;
	float deltaPartieInf = abs(eMoyenne-eBasse)/indiceMilieu;
	int hauteurInterieure= pts[pts.size()-1]->y + eBase;
	unsigned int i=0;
	int j=1;
	int k=1;
	
	while(i<pts.size() && pts[i]->y <= hauteurInterieure)
	{
		Point *tmp=new Point();
		if(i<indiceMilieu)
		{
			
			tmp->x=pts[i]->x+eHaute+deltaPartieSup*j;
			tmp->y=pts[i]->y;
			ptsProfilInterne.push_back(tmp);
			++j;
		}
		else
		{
			tmp->x=pts[i]->x+eMoyenne+deltaPartieInf*k;
			tmp->y=pts[i]->y;
			ptsProfilInterne.push_back(tmp);
			++k;
		}
		i++;
	}
	
	//cout<<"Apres translation"<<endl;
	float volumeInterieur=0;
	for (unsigned int i=0; i < ptsProfilInterne.size()-1; i++)
		{
		

			float base1=(im->getWidthCtr()-ptsProfilInterne[i]->x)*echelle;
			float base2=(im->getWidthCtr()-ptsProfilInterne[i+1]->x)*echelle;
			float hauteurSection=abs((ptsProfilInterne[i]->y-ptsProfilInterne[i+1]->y))*echelle;
			
			//volume+=(PI*(hauteurSection)*(base1*base1+base1*base2+base2*base2))/3.0;
			volumeInterieur+=((PI*pow(base2,2)*hauteurSection)/3.0)*(1+(base1/base2)+(pow(base1,2)/pow(base2,2)));

		}

	
	float volumeMilieu= (volume-volumeInterieur)/2;
	
	i=0;
	float volumeTmp=0;
	while(i<ptsProfilInterne.size()-1 && volumeTmp<volumeMilieu)
	{	
		float base1=(im->getWidthCtr()-pts[i]->x)*echelle;
		float base2=(im->getWidthCtr()-pts[i+1]->x)*echelle;
		float hauteurSectionExterieure=abs((pts[i]->y-pts[i+1]->y))*echelle;

		float base3=(im->getWidthCtr()-ptsProfilInterne[i]->x)*echelle;
		float base4=(im->getWidthCtr()-ptsProfilInterne[i+1]->x)*echelle;
		float hauteurSection=abs((ptsProfilInterne[i]->y-ptsProfilInterne[i+1]->y))*echelle;
		volumeTmp+=((PI*pow(base2,2)*hauteurSectionExterieure)/3.0)*(1+(base1/base2)+(pow(base1,2)/pow(base2,2))) - ((PI*pow(base4,2)*hauteurSection)/3.0)*(1+(base3/base4)+(pow(base3,2)/pow(base4,2)));
		i++;	
	}
	
	hauteurCDM=(baseHauteur-pts[i]->y)*echelle;
	
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
	CString Surface;
	Surface.Format(CString("Surface : %.4lf cm²"), surface);
	CString Volume;
	Volume.Format(CString("Volume : %.4lf cm3"), volume);
	CString Circularite;
	Circularite.Format(CString("Circularite : %.2lf "), circularite);
	CString HauteurCDM;
	HauteurCDM.Format(CString("Hauteur du CDM : %.2lf cm"), hauteurCDM);

	liste->AddString(ouv);
	liste->AddString(haut);
	liste->AddString(diam);
	liste->AddString(diamHaut);
	liste->AddString(bas);
	liste->AddString(Surface);
	liste->AddString(Volume);
	liste->AddString(Circularite);
	liste->AddString(HauteurCDM);
}
