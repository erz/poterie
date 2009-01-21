// Classe permettant de gérer les séquences d'image chargées.
//

#pragma once

#include "stdafx.h"

#include <CString>
#include <iostream>

#include "PoterieTraitement.h"


class CPoterieData
{
	public:
		CPoterieData(CPoterieImage*,int indice);
		void RefreshListe(CListBox*);
		void CentreDeMasse(CPoterieImage * im);
		
		int ouverture;
		int base;
		int hauteur; 
		int maxDiam;
		int maxDiamHauteur;
		float volume;
		float surface;
		float circularite;
		float hauteurCDM;
	private:
		int baseHauteur;
		int surfaceVolumique;
		float eHaute;
		float eMoyenne;
		float eBasse;
		float eBase;

		std::vector<Point *> pts;
		std::vector<Point *> ptsProfilInterne;
};
