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
		CPoterieData(CPoterieImage*);
		void RefreshListe(CListBox*);
		void CentreDeMasse(CPoterieImage * im);
		
	private:
		int base;
		int hauteur; 
		int ouverture;
		int maxDiam;
		int maxDiamHauteur;
		int volume;
		int surfaceVolumique;
		int eHaute;
		int eMoyenne;
		int eBasse;
		int eBase;
		std::vector<Point *> pts;
		std::vector<Point *> ptsProfilInterne;
};