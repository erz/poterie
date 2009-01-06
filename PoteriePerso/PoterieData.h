// Classe permettant de g�rer les s�quences d'image charg�es.
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
		void RefreshListe();
		
	private:
		float base;
		float hauteur; 
		float ouverture;
		float maxDiam;
		float maxDiamHauteur;
};