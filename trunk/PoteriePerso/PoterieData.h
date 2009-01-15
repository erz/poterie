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
		float volume;
		float surface;
		int surfaceVolumique;
		float eHaute;
		float eMoyenne;
		float eBasse;
		float eBase;
		float circularite;
		std::vector<Point *> pts;
		std::vector<Point *> ptsProfilInterne;
};

struct TriAscendant
	{		
		inline bool operator() (Point * a, Point * b) const
		{
				return a->y < b->y;
		}
	};