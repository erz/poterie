/*
	Fichier source des traitements de l'application
*/

/*
	Fonction de rafraichissement des donn�es � l'�cran
*/
#include "stdafx.h"

#include "PoteriePerso.h"
#include "PoteriePersoDlg.h"
#include "PoterieSequence.h"
#include "PoterieTraitement.h"
#include "VariablesGlobales.h"

#include <iostream>
#include <CString>
#include <afxstr.h>
#include <atlimage.h>

//Variables globales
//Sequence d'image
CPoterieSequence *seq = new CPoterieSequence();

void CPoteriePersoDlg::refresh ()
{
	if (seq != NULL)
	{
		//Affichage de l'image
		if (seq->getNbImages() > 0)
		{
			m_image = ATL::CImage();
			m_image.Load(seq->getNom(seq->getIdCour()));

			///////////////////////////
			// Permet de redimensionner l'image � la taille du receptacle

			CDC m_dcMem; // Compatible Memory DC
			CBitmap bmpItem; // Bitmap for Check
			BITMAP bmInfo; // Bitmap information structure
			CBitmap* pBmpOld; // Pointer to old bitmap
			CSize m_size; // Size of bitmap
			RECT rect; // rect of static member


			bmpItem.Attach(m_image);

			// Get bitmap information
			bmpItem.GetObject( sizeof(BITMAP), &bmInfo );

			m_picture.GetClientRect( &rect );
			m_size.cx = rect.right;
			m_size.cy = rect.bottom;

			// Convert to screen coordinates using static as base,
			// then to DIALOG (instead of static) client coords
			// using dialog as base
			m_picture.ClientToScreen( &rect );
			ScreenToClient( &rect );

			// Get temporary DC for dialog - Will be released in dc destructor
			CClientDC dc(this);

			// Create compatible memory DC using the dialogs DC
			m_dcMem.CreateCompatibleDC( &dc );

			// Select bitmap into DC - get pointer to original bitmap
			pBmpOld = m_dcMem.SelectObject( &bmpItem );

			//Permet de garder les couleurs
			dc.SetStretchBltMode(COLORONCOLOR);

			// Stretch bitmap into static member's client area.
			dc.StretchBlt( rect.left, rect.top, m_size.cx, m_size.cy,
			&m_dcMem, 0, 0, bmInfo.bmWidth-1,
			bmInfo.bmHeight-1,
			SRCCOPY );

			// Select back old bitmap and release bitmap resource
			m_dcMem.SelectObject( pBmpOld );
			bmpItem.DeleteObject();
		//////////////////

		//	m_picture.SetBitmap((HBITMAP)m_image);
		//	m_picture.Invalidate(); 

		

			//Cr�ation Structure image OPENCV
			CPoterieImage newimage;
			CString TMPREP = seq->getRepertoireCourant()+CString("\\")+seq->getNom(seq->getIdCour()); 
			newimage.afficher_image(TMPREP);
		}
	}
}

CPoterieImage::CPoterieImage()
{
	CvSeq* contours = 0;
	CvMemStorage* storage = cvCreateMemStorage(0);
	sz = cvSize( 500 , 500  );
    img = cvCreateImage( sz, 8, 3 );
}

void CPoterieImage::afficher_image(CString source)
{
		
	img=cvLoadImage(CString2Char(source));
	cvNamedWindow("Opencv",CV_WINDOW_AUTOSIZE);
	cvShowImage("Opencv",img);

	trouver_contour();
	cvWaitKey(0);	
	
}

void CPoterieImage::trouver_contour()
{
	
	IplImage* NvGris = cvCreateImage( sz, 8, 1 );
	IplImage* copieImg = cvCloneImage( img ); 
	cvSetImageCOI( copieImg, 1 );
	//cvCopy( img, NvGris, 0 );

	//cvFindContours( tmp, storage, &contours, sizeof(CvContour),CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0) );
	//contours = cvApproxPoly( contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, 3, 1 );
	/*
	cvNamedWindow( "contours", 1 );

	IplImage* cnt_img = cvCreateImage( cvGetSize(img), 8, 1 );
    CvSeq* _contours = contours;
    int _levels = 0;
    //if( _levels <= 0 ) // get to the nearest face to make it look more funny
    //    _contours = _contours->h_next->h_next->h_next;
    cvZero( cnt_img );
    //cvDrawContours( cnt_img, _contours, CV_RGB(255,0,0), CV_RGB(0,255,0), _levels, 3, CV_AA, cvPoint(0,0) );
    cvShowImage( "contours", cnt_img );
    cvReleaseImage( &cnt_img );
	*/
}