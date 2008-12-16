/*
	Entête du fichier de traitement de l'application
*/


#pragma once

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

/*
	Fonction de rafraichissement des données à l'écran
*/
void refresh ();

class CPoterieImage
{
public:
	void afficher_image(CString source);
private:
	IplImage *img;
};