#pragma once
#include "afxwin.h"
#include <afxstr.h>
#include <iostream>
#include <CString>



inline char* CString2Char(CString chaine)
{
	char *sz= new char [chaine.GetLength()+1] ;
	WideCharToMultiByte( CP_ACP, 0, chaine, -1, sz, chaine.GetLength()+1, NULL, NULL );
	return sz;
}

inline CString Char2CString(char * chaine)
{
	return (LPCTSTR) (LPTSTR) chaine;
}

//Ouverture fichier
inline FILE* ouvertureFichier(FILE* fichier, char* path)
{
	fichier = fopen(path, "a");
	return fichier;
}

//Fermeture fichier
inline void fermetureFichier(FILE* fichier)
{
	fclose(fichier);
}

//Changement de repère OpenCV -> Enora
inline float changementRepere(int coord, bool isX, int width, float echelle, int Ymin)
{
	//Cas X
	if (isX)
	{
		return ((width-coord)*echelle)/100.0;
	}
	else
	{
		return ((Ymin-coord)*echelle)/100.0;
	}
}


class Point
{
	public:
		int x;
		int y;
};