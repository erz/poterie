/*
	Ent�te du fichier de traitement de l'application
*/


#pragma once

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

/*
	Fonction de rafraichissement des donn�es � l'�cran
*/
void refresh ();

class CPoterieImage
{
public:
	CPoterieImage(CString str);
	void afficher_image();
	void trouver_contour();
private:
	IplImage *img;
	IplImage *imgCtrs;
	CvMemStorage* storage;
	CvSeq* contours;
	CvSize sz ;
};