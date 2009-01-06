/*
	Fichier source des traitements de l'application
*/

/*
	Fonction de rafraichissement des données à l'écran
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
			// Permet de redimensionner l'image à la taille du receptacle

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

		

			//Création Structure image OPENCV
			
			//Si le CImage n'existe pas, on le crée
			if (seq->getImage(seq->getIdCour()) == NULL)
			{
				CString TMPREP = seq->getRepertoireCourant()+CString("\\")+seq->getNom(seq->getIdCour()); 
				CPoterieImage *newImage = new CPoterieImage(TMPREP);
				seq->setImage(seq->getIdCour(), newImage);
			}


			if (seq->getImage(seq->getIdCour())->getContour() == NULL)
				seq->getImage(seq->getIdCour())->trouver_contour();
			
			seq->getImage(seq->getIdCour())->afficher_image();

			//Si le CPoterieCourbe n'existe pas, on le crée
			if (seq->getCourbe(seq->getIdCour()) == NULL)
			{
				CPoterieCourbe *newCourbe = new CPoterieCourbe(seq->getImage(seq->getIdCour())->getContour());
				seq->setCourbe(seq->getIdCour(), newCourbe);
			}

			//Si le CPoterieData n'existe pas, on le crée
			if (seq->getData(seq->getIdCour()) == NULL)
			{
				CPoterieData *newData = new CPoterieData(seq->getImage(seq->getIdCour()));
				seq->setData(seq->getIdCour(), newData);
			}
			seq->getData(seq->getIdCour())->RefreshListe();
		}
	}
}

CPoterieImage::CPoterieImage(CString str)
{
	contours = 0;
	storage = cvCreateMemStorage(0);
	storageContours= cvCreateMemStorage(0);
	img=cvLoadImage(CString2Char(str));
	sz = cvSize(img->width, img->height);
	imgCtrs = NULL;
	cnt_img = NULL;
	ContourPoterie = NULL;
}

std::vector<Point *> * CPoterieImage::getContour()
{
	return ContourPoterie;
}

double CPoterieImage::angle( CvPoint* pt1, CvPoint* pt2, CvPoint* pt0 )
{
    double dx1 = pt1->x - pt0->x;
    double dy1 = pt1->y - pt0->y;
    double dx2 = pt2->x - pt0->x;
    double dy2 = pt2->y - pt0->y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

void CPoterieImage::afficher_image()
{
	cvNamedWindow("Opencv",CV_WINDOW_AUTOSIZE);
	cvShowImage("Opencv",img);
	cvNamedWindow( "contours", 1 );
	if (cnt_img == NULL)
		trouver_contour();
	cvShowImage( "contours", cnt_img );

	cvWaitKey(0);	
}

void CPoterieImage::filtreMoyenNVG(IplImage *src, IplImage *dst, int voisinage){
  
    //On vérifie que le voisinage est impair, 
    //on le corrige si ce n'est pas le cas
    if(voisinage%2!=1)
        voisinage++;
    
    
    //On initialise un carré de côté "voisinage"
    CvRect roi=cvRect(0,0,voisinage,voisinage);
    
    //On initialise un entier, pour la moyenne
    int moyenne=0;
    
    //Un petit scalaire pour la route ^^
    CvScalar scalaire;
    
    
    /////////// FIN DE L'INITIALISATION //////////////
    
    
    //On parcourt toute l'image
    for(int x=0; x<src->width; x++)
    {
        for(int y=0; y<src->height; y++)
        {
            //Pour chaque pixel
        
            //S'il est trop "au bord" :
            if(x<(voisinage-1)/2 || x>(src->width - 1 - (voisinage-1)/2) || y<(voisinage-1)/2 || y>(src->height - 1 - (voisinage-1)/2))
            {
                //Dans ce cas on recopie simplement le pixel 
                cvSet2D(dst, y, x, cvGet2D(src, y, x));
            }else
            {
                //On remet la moyenne à zéro 
                moyenne=0;
                
                //On centre le voisinage sur le pixel en cours
                roi.x= x - (voisinage-1)/2;
                roi.y= y - (voisinage-1)/2;
                
                //On initialise la région d'intéret
                cvSetImageROI(src, roi);
                
                //On parcourt le voisinage
                for(int i=0; i<voisinage; i++)
                {
                    for(int j=0; j<voisinage; j++)
                    {
                    
                        //On récupère les valeurs du voisinage que l'on additionne
                        scalaire = cvGet2D(src, j, i);
                        moyenne+= scalaire.val[0];                    
                    }
                }
                
                //On relache la région d'intéret
                cvResetImageROI(src);

                //On calcule la moyenne 
                scalaire.val[0] = moyenne/(voisinage*voisinage);
                
                //On la remplace dans l'image de destination
                cvSet2D(dst, y, x, scalaire);
            }
        }
    }
}


void CPoterieImage::filtreMedianNVG(IplImage *src, IplImage *dst, int voisinage){

    //On vérifie que les 2 images que l'on nous a fournies sont bien en NVG 
    if(src->nChannels!=1||dst->nChannels!=1)
        return;
        
    //On vérifie que les 2 images ont les mêmes dimensions
    if((src->width!=dst->width)||(src->height!=dst->height))
        return;
    
    
    //On véridie que le voisinage est impair, on le corrige si ce n'est pas le cas
    if(voisinage%2!=1)
        voisinage++;
    
    
    //On initialise un carré de côté "voisinage"
    CvRect roi=cvRect(0,0,voisinage,voisinage);
    
    //On initialise un tableau d'entiers, pour le calcul de la médiane
    int *voisins=new int[voisinage*voisinage];
    
    //Un petit scalaire pour la route ^^
    CvScalar scalaire;
    
    
    /////////// FIN DE L'INITIALISATION //////////////
    
    
    //On parcourt toute l'image
    for(int x=0; x<src->width; x++)
    {
        for(int y=0; y<src->height; y++)
        {
            //Pour chaque pixel
        
            //S'il est trop "au bord" :
            if(x<(voisinage-1)/2 || x>(src->width - 1 - (voisinage-1)/2) || y<(voisinage-1)/2 || y>(src->height - 1 - (voisinage-1)/2))
            {
                //Dans ce cas on recopie simplement le pixel 
                cvSet2D(dst, y, x, cvGet2D(src, y, x));
            }else
            {
                //On centre le voisinage sur le pixel en cours
                roi.x= x - (voisinage-1)/2;
                roi.y= y - (voisinage-1)/2;
                
                //On initialise la région d'intéret
                cvSetImageROI(src, roi);
                
                //On parcourt le voisinage
                for(int i=0; i<voisinage; i++)
                {
                    for(int j=0; j<voisinage; j++)
                    {
                    
                        //On récupère les valeurs du voisinage
                        scalaire = cvGet2D(src, j, i);
                        voisins[i*voisinage + j] = scalaire.val[0];                    
                    }
                }
                
                //On relache la région d'intéret
                cvResetImageROI(src);

                
                //On classe les valeurs
                sort( voisins, voisins + (voisinage*voisinage));
                
                //On choisit la valeur médiane 
                scalaire.val[0] = voisins[ (voisinage-1)/2 + 1];
                
                //On la remplace dans l'image de destination
                cvSet2D(dst, y, x, scalaire);
            }
        }
    }
    
    delete[] voisins;
}


void CPoterieImage::trouver_contour()
{

	IplImage* cropped = cvCreateImage( cvSize(img->width/2,img->height/2), 8, 3);
	CvMat *matCrop = cvCreateMatHeader( img->width/2, img->height/2, CV_8UC3 );
	CvMat* src_region = cvGetSubRect(img, matCrop, cvRect(0, img->height/2, img->width/2, img->height/2) );
	cvCopy(src_region, cropped);
	
	sz = cvSize(cropped->width, cropped->height);
	IplImage* NvGris = cvCreateImage( sz, 8, 1 );
	IplImage* gray = cvCreateImage(sz , 8, 1 );
	IplImage* copieImg = cvCloneImage( cropped ); 
	IplImage* pyr = cvCreateImage( cvSize(cropped->width, cropped->height), 8, 3 );
	

	cnt_img = cvCreateImage( sz, 8, 3 );
    cvZero( cnt_img );

	CvSeq* result;
	CvSeq* contourPoterie = cvCreateSeq( 0, sizeof(CvSeq), sizeof(CvPoint), storageContours );
	
	
		//On choitsit un canal de l'image pour travailler dessus
		cvSetImageCOI( copieImg, 1 );
		cvCopy(copieImg, NvGris, NULL );
		
		//On applique un filtre moyen à l'image en Niveau de gris
		filtreMoyenNVG(NvGris,NvGris,7);
		//On applique un filtre median à l'image en Niveau de gris
		filtreMedianNVG(NvGris,NvGris,3);

		//Recherche de contours
		for(int l = 0; l < 11; l++ )
        {
            if( l == 0 )
            {
				//gradient : c'est le dernier parametre de cvcanny (degré de la dérivé)
                cvCanny( NvGris, gray, 0.5, 0.5, 3 );
				cvErode( gray, gray, 0, 2 );
                cvDilate( gray, gray, 0, 2 );
				
				//cvNamedWindow("Gris",CV_WINDOW_AUTOSIZE);
				//cvShowImage("Gris",gray);
            }
            else
            {
                cvThreshold( NvGris, gray, (l+1)*255/11, 255, CV_THRESH_BINARY );
            }
		
			cvFindContours(gray, storage, &contours, sizeof(CvContour),CV_RETR_EXTERNAL, CV_LINK_RUNS, cvPoint(0,0) );
			
			//On dessine les contours trouvés
			double s=0;
			double t=0;
			int i=0;
			bool sortirboucle=false;
			 while( contours && !sortirboucle)
             {
				result = cvApproxPoly( contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP,  0, 1 );
				
					//On effectue des tests sur les points appartenant au contours
					if( i >= 2 && cvGetSeqElem( result, i )!=NULL)
					{
								CvPoint* test2 = (CvPoint*) cvGetSeqElem( result, i );
								CvPoint* test1 = (CvPoint*) cvGetSeqElem( result, i-1 );
								
								//cout<<"Point\t" << i << "\tX\t:"<< test2->x <<"\tY\t:"<< test2->y << endl;

								double ecartX=(test2->x)-(test1->x);
								double ecartY=(test2->y)-(test1->y);
								//cout<<"Ecart X\t:"<<ecartX<<"\tEcart Y\t:"<<ecartY<<endl;
								
								/***************************************************************************************/
								//ici on rempli la structure contenant les points appartenant à la bordure de la poterie!
								if((fabs(ecartX)<30 && fabs(ecartY)<30) && test2->y>30 && test2->y<(gray->height-15))
								{
									if(i>=5)
									{
										double variationX=0;
										double variationY=0;
										CvPoint* tmp;
										for(int j=0;j<5;j++)
										{
											tmp=(CvPoint*) cvGetSeqElem( result, i-j );
											variationX+=tmp->x;
											//variationY+=tmp->y;
										}
										variationX=variationX/5;
										//variationY=variationY/5;

										//cout<<"Moyenne X\t:"<<variationX<<endl;
										//cout<<"Moyenne Y\t:"<<variationY<<endl;
										//cout<<"**************"<<endl;
										
										if(variationX <300)
										{
										cvSeqPush( contourPoterie,(CvPoint*) cvGetSeqElem( result, i ));
										//cvSeqPush( contourPoterie,(CvPoint*) cvGetSeqElem( result, i-1 ));
										cvSeqPush( contourPoterie,(CvPoint*) cvGetSeqElem( result, i-2 ));
										//cvSeqPush( contourPoterie,(CvPoint*) cvGetSeqElem( result, i-3 ));
										//cvSeqPush( contourPoterie,(CvPoint*) cvGetSeqElem( result, i-4 ));
										}
									}
									
								}
								/***************************************************************************************/
						}
						
				
				//cvDrawContours( cnt_img, result, CV_RGB(255,255,255), CV_RGB(0,255,0), -1, 0, CV_AA, cvPoint(0,0) );
				
				//POur sortir de la boucle! (oui ce n'est pas propre mais opencv c'est mal codé!)
				if(cvGetSeqElem( result, i )==NULL) sortirboucle=true;
				result=result->h_next;
				i++;
			 }
			
	
		}

	/*************Lecture et affichage du contour de la poterie****************/
	ContourPoterie = new std::vector<Point *>;
	CvSeqReader reader;
	int compteurSelection = 0;
	cvStartReadSeq( contourPoterie, &reader, 0 );
	for(int i = 0; i < contourPoterie->total; i += 2 )
    {
		CvPoint pt[2], *rect = pt;
        int count = 2;
        
        // read 2 vertices
        CV_READ_SEQ_ELEM( pt[0], reader );
        CV_READ_SEQ_ELEM( pt[1], reader );
		Point * Pttmp= new Point();
		Point * Pttmp2= new Point();
		float longeur = abs(pt[0].x-pt[1].x);
		if(pt[0].x>30 && pt[0].y>20 && pt[1].x>10 && pt[1].y>15 && pt[0].x<300 && longeur<20)
		{
			//cout<<"Pt X:"<<pt[0].x<<"\tPt Y:"<<pt[0].y<<endl;
			//cout<<"Pt X:"<<pt[1].x<<"\tPt Y:"<<pt[1].y<<endl;
			//cout<<"*******************************"<<endl;
			cvPolyLine( cnt_img, &rect, &count, 1, 0, CV_RGB(255,255,255), 1, 0, 0 );
			Pttmp->x=pt[0].x;Pttmp->y=pt[0].y;
			Pttmp2->x=pt[1].x;Pttmp2->y=pt[1].y;
			ContourPoterie->push_back(Pttmp);
			ContourPoterie->push_back(Pttmp2);
			//compteurSelection=compteurSelection+2;
		}
	}
	//cout<<"Nbres de points:\t"<<compteurSelection<<endl;
	/*****************************************************************************/

	//cvShowImage( "contours", cnt_img );
    //cvReleaseImage( &cnt_img );
	
	//return ContourPoterie;
}


//Fonction d'enregistrement des données
void enregistrerDonnees(CString path)
{
	CFile fileTest;
	BOOL bLecture = FALSE;

	if( !fileTest.Open( path, CFile::modeWrite ) )
	{
		if( fileTest.Open( path, CFile::modeCreate | CFile::modeWrite ) )
		{
			bLecture = TRUE;
		}
	}
	else
	{
		bLecture = TRUE;
	}

	if( bLecture )
	{
		fileTest.SeekToEnd();
		fileTest.Write(path, path.GetLength());
		fileTest.Close();
	}
}