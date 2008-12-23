// Classe permettant de gérer les séquences d'image chargées.
//

#pragma once

#include "PoterieTraitement.h"
#include "stdafx.h"

#include <CString>
#include <afxstr.h>
#include <atlimage.h>
#include <iostream>

using namespace std;
class CPoterieSequence
{
	int nbImages;

	CString *tabNoms;
	CString directory;
	CPoterieImage **tabImages;

	int idPicCourante;

	public :

	CPoterieSequence()
	{
		nbImages = 0;
		idPicCourante = 0;
	}

	/*
		Renvoie le nombre d'images dans la séquence
	*/
	int getNbImages()
	{
		return nbImages;
	}

	/*
		Renvoie l'indice de l'image courante
	*/
	int getIdCour()
	{
		return idPicCourante;
	}
	
	/*
		Ajoute une image en plus, renvoie son indice
	*/
	int addImage(CString str)
	{
		nbImages++;
		CPoterieImage **temp = new CPoterieImage* [nbImages];
		CString *temp2 = new CString [nbImages];
		for (int i = 0; i < (nbImages-1); ++i)
		{
			temp[i] = tabImages[i];
			temp2[i] = tabNoms[i];
		}

		temp[nbImages-1] = NULL;
		temp2[nbImages-1] = str;

		tabImages = temp;
		tabNoms = temp2;

		return nbImages;
	}

	/*
		Retourne l'image à l'indice i
	*/
	CPoterieImage* getImage(int i)
	{
		return tabImages[i];
	}

	/*
		Enregistre l'image à l'indice i
	*/
	void setImage(int i, CPoterieImage* im)
	{
		tabImages[i] = im;
	}
	
	/*
		Retourne le nom de l'image à l'indice i
	*/
	CString getNom(int i)
	{
		return tabNoms[i];
	}

	/*
		Passe l'id courant à l'image précedente
	*/
	void prevImage()
	{
		if (idPicCourante-1 < 0)
			idPicCourante = nbImages-1;
		else if (nbImages>0)
			idPicCourante = (idPicCourante-1)%nbImages;
	}

	/*
		Passe l'id courant à l'image suivante
	*/
	void nextImage()
	{ 
		if (nbImages>0)
			idPicCourante = (idPicCourante+1)%nbImages;
	}

	void setRepertoireCourant(CString nom)
	{
		directory=nom;
	}
	
	CString getRepertoireCourant()
	{
		return directory;
	}

};
