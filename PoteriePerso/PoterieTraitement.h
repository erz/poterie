/*
	Entête du fichier de traitement de l'application
*/


#pragma once

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <algorithm>
#include <vector>
#include "Outils.h"
#include <fstream>
#include <iostream>


/*
	Fonction de rafraichissement des données à l'écran
*/
void refresh ();

/*
	Fonction d'enregistrement des données
*/
void enregistrerDonnees (CString);

//Enregistre un point
void enregistrerPoints(FILE *,Point *);

//Remplis les variables globales dépendantes de la forme en fonction de celle-ci
void remplirValeursSelonForme(void);

/*
	Fonction d'étalonnage
*/
void etalonnerAvecImage(CString);
//Fonction de Callback souris
void mouseHandler(int event, int x, int y, int flags, void* param);

class CPoterieImage
{
public:
	CPoterieImage();
	CPoterieImage(CString str);
	void afficher_image();
	void trouver_contour();
	void filtreMoyenNVG(IplImage *src, IplImage *dst, int voisinage);
	void filtreMedianNVG(IplImage *src, IplImage *dst, int voisinage);
	double angle( CvPoint* pt1, CvPoint* pt2, CvPoint* pt0 );
	std::vector<Point *> *getContour(void);
	int getHeightCtr(void);
	int getWidthCtr(void);
private:
	IplImage *img;
	IplImage *imgCtrs;
	IplImage *cnt_img;
	CvMemStorage* storage;
	CvMemStorage* storageContours;
	CvSeq* contours;
	CvSize sz ;	
	std::vector<Point *> *ContourPoterie;
};