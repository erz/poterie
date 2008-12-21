/*
	Entête du fichier de traitement de l'application
*/


#pragma once

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <algorithm>


/*
	Fonction de rafraichissement des données à l'écran
*/
void refresh ();

/*
	Fonction d'enregistrement des données
*/
void enregistrerDonnees (CString);

class CPoterieImage
{
public:
	CPoterieImage(CString str);
	void afficher_image();
	void trouver_contour();
	void filtreMoyenNVG(IplImage *src, IplImage *dst, int voisinage);
	void filtreMedianNVG(IplImage *src, IplImage *dst, int voisinage);

private:
	IplImage *img;
	IplImage *imgCtrs;
	IplImage *cnt_img;
	CvMemStorage* storage;
	CvSeq* contours;
	CvSize sz ;
};