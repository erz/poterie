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
		
	private:
		int base;
		int hauteur; 
		int ouverture;
		int maxDiam;
		int maxDiamHauteur;
};