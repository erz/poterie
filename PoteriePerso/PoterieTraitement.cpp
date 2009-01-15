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
//Echelle par défaut
double echelle = 0.076692;
//Fichier d'enregistrement
FILE *fichierSortie = new FILE;
//Données dépendantes de la forme de la poterie
int formePoterie = 1;
float epaisseurBase = 0;
float epaisseurBasse = 0;
float epaisseurMilieu = 0;
float epaisseurHaute = 0;

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
			seq->getData(seq->getIdCour())->RefreshListe(&listeVars);
			
			//Enregistrement des points 
			//Ouverture du fichier
			char path[100];
			sprintf_s(path,"C:\\data_source_%d",seq->getIdCour());

			fichierSortie = ouvertureFichier(fichierSortie,path);
			//fichierSortie = fopen("C:\\hop.txt", "a");
			//Parcours de tous les points
			vector <Point*> pts = *(seq->getImage(seq->getIdCour())->getContour());
			for (unsigned int i=0; i<pts.size();++i)
			{
				enregistrerPoints(fichierSortie, pts[i]);
				//fprintf(fichierSortie, "%d %d\n", pts[i]->x, pts[i]->y);
			}
			//Fermeture du fichier
			fermetureFichier(fichierSortie);
			//fclose(fichierSortie);
			
			//L'affichage d'image est bloquant ! alors, ne le faire qu'à la fin !
			seq->getImage(seq->getIdCour())->afficher_image();

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


int CPoterieImage::getHeightCtr(void)
{
	if (cnt_img != NULL)
		return cnt_img->height;
	return 0;
}

int CPoterieImage::getWidthCtr(void)
{
	if (cnt_img != NULL)
		return cnt_img->width;
	return 0;
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
    double moyenne=0;
    
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
    double *voisins=new double[voisinage*voisinage];
    
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
	
					/*
					int m = 0;
					while (cvGetSeqElem( result, m ) != NULL)
					{
						CvPoint* point = (CvPoint*) cvGetSeqElem( result, m );
						cout << "Point " << m << " :\t" << point->x << "\t" << point->y << endl;
						m++;
					}
					*/
						
			
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
	std::vector<Point *> *TempContourPoterie = new std::vector<Point *>;
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
		int longeur = abs(pt[0].x-pt[1].x);
		if(pt[0].x>30 && pt[0].y>20 && pt[1].x>10 && pt[1].y>15 && pt[0].x<300 && longeur<20)
		{
			//cout<<"Pt X:"<<pt[0].x<<"\tPt Y:"<<pt[0].y<<endl;
			//cout<<"Pt X:"<<pt[1].x<<"\tPt Y:"<<pt[1].y<<endl;
			//cout<<"*******************************"<<endl;
			//cvPolyLine( cnt_img, &rect, &count, 1, 0, CV_RGB(0,0,255), 1, 0, 0 );
			Pttmp->x=pt[0].x;Pttmp->y=pt[0].y;
			Pttmp2->x=pt[1].x;Pttmp2->y=pt[1].y;
			//cout << "Pttmp1 :\t" << Pttmp->x << "\t" << Pttmp->y << endl; 
			//cout << "Pttmp2 :\t" << Pttmp2->x << "\t" << Pttmp2->y << endl;
			TempContourPoterie->push_back(Pttmp);
			TempContourPoterie->push_back(Pttmp2);
			//compteurSelection=compteurSelection+2;
		}
	}

	//Nettoyage du contour par suppression des points en double
	ContourPoterie = new std::vector<Point *>;
	

	for (unsigned int i = 0; i < TempContourPoterie->size(); ++i)
	{
		//Est-ce que le point qu'on veut mettre existe déjà, ici ou sur cette ligne (y)
		bool existePoint = false;
		for (unsigned int j=0; j < ContourPoterie->size(); ++j)
		{
			//if ((*ContourPoterie)[j]->x == (*TempContourPoterie)[i]->x && (*ContourPoterie)[j]->y == (*TempContourPoterie)[i]->y)
			if (abs((*ContourPoterie)[j]->y -(*TempContourPoterie)[i]->y)<=1)
			{
				existePoint = true;
				break;
			}
		}

		//S'il n'est pas déja, on le met
		if (existePoint == false)
			ContourPoterie->push_back((*TempContourPoterie)[i]);
	}
	
	//cout << "Apres Nettoyage : " << endl;
	for (unsigned int i = 0; i+1 < ContourPoterie->size(); i+=2)
	{
		CvPoint pt[2], *rect = pt;
		int count=2;
		pt[0].x=(*ContourPoterie)[i]->x;
		pt[0].y=(*ContourPoterie)[i]->y;
		pt[1].x=(*ContourPoterie)[i+1]->x;
		pt[1].y=(*ContourPoterie)[i+1]->y;
		cvPolyLine( cnt_img, &rect, &count, 1, 0, CV_RGB(255,255,255), 1, 0, 0 );
		//cout << "Point " << i << " :\t" << (*ContourPoterie)[i]->x << "\t" << (*ContourPoterie)[i]->y << endl;
		//cout << "Point " << i+1 << " :\t" << (*ContourPoterie)[i+1]->x << "\t" << (*ContourPoterie)[i+1]->y << endl;

	}
/*
	bool effacement=false;

	double moyenne=((*ContourPoterie)[0]->y+(*ContourPoterie)[1]->y+(*ContourPoterie)[2]->y)/3.0;
	unsigned int j=3;
	while(j<ContourPoterie->size() && fabs((float)(*ContourPoterie)[j]->y-moyenne)<=1)
	{
		j++;
		effacement = true;
	}

	if(effacement) 
		ContourPoterie->erase(ContourPoterie->begin(),ContourPoterie->begin()+j-1);
	
	cout << "Apres Nettoyage 2: " << endl;
	for (unsigned int i = 0; i+1 < ContourPoterie->size(); i+=2)
	{
		CvPoint pt[2], *rect = pt;
		int count=2;
		pt[0].x=(*ContourPoterie)[i]->x;
		pt[0].y=(*ContourPoterie)[i]->y;
		pt[1].x=(*ContourPoterie)[i+1]->x;
		pt[1].y=(*ContourPoterie)[i+1]->y;
		cvPolyLine( cnt_img, &rect, &count, 1, 0, CV_RGB(255,255,255), 1, 0, 0 );
		cout << "Point " << i << " :\t" << (*ContourPoterie)[i]->x << "\t" << (*ContourPoterie)[i]->y << endl;
		cout << "Point " << i+1 << " :\t" << (*ContourPoterie)[i+1]->x << "\t" << (*ContourPoterie)[i+1]->y << endl;
	}*/

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

//Fonction d'enregistrement des points
void enregistrerPoints(FILE* fichier, Point * p)
{
	if (fichier!=NULL)
	{
		fprintf(fichier, "%d %d\n", p->x, p->y);
	}
	else
	{
		cout<<"Erreur d'écriture"<<endl;	
	}
}
//Fonction d'etalonnage
void etalonnerAvecImage(CString etalon)
{
	IplImage *img=cvLoadImage(CString2Char(etalon));
	cvNamedWindow("CLIQUER SUR LES DEUX EXTREMITES DE L'ETALON",CV_WINDOW_AUTOSIZE);
	cvSetMouseCallback("CLIQUER SUR LES DEUX EXTREMITES DE L'ETALON",mouseHandler);
	cvShowImage("CLIQUER SUR LES DEUX EXTREMITES DE L'ETALON",img);
	cvWaitKey(0);
}

void mouseHandler(int event, int x, int y, int flags, void* param)
{
	static int clic1 = 0;
	static int clic2 = 0;

    switch(event)
	{
      case CV_EVENT_LBUTTONDOWN:
	    if (clic1 != 0 && clic2 == 0)
			clic2 = y;
        else if ((clic1 != 0) && (clic2 != 0))
		{
			clic1 = y;
			clic2 = 0;
		}
		else if (clic1 == 0)
			clic1 = y;

		if (clic1 != 0 && clic2 != 0)
		{
			if (abs(clic1-clic2) != 0)
				echelle = 36.0 / abs(clic1-clic2);
			
			CString mess;
			mess.Format(CString("Etalonnage terminé avec succès.\nEchelle : 1px = %.4lf cm.\nCela vous convient-t-il ? Choisissez non pour choisir deux nouveaux points."), echelle);
			if (MessageBox(NULL, mess, CString("Succès"), MB_YESNO) == IDYES)
				cvDestroyWindow("CLIQUER SUR LES DEUX EXTREMITES DE L'ETALON");
		}

        break;
    }
	
}

//Remplis les variables globales dépendantes de la forme en fonction de celle-ci
void remplirValeursSelonForme()
{
	//Convention:
	//1 = bol
	//2 = cylindre
	//3 = vase
	
	switch (formePoterie)
	{
		case 1 :
			epaisseurBase = 0.98;
			epaisseurBasse = 0.18;
			epaisseurMilieu = 0.68;
			epaisseurHaute = 0.5;
			break;
		case 2 :
			epaisseurBase = 0.753;
			epaisseurBasse = 0.11;
			epaisseurMilieu = 0.7;
			epaisseurHaute = 0.46;
			break;
		case 3 :
			epaisseurBase = 0.8;
			epaisseurBasse = 1.55;
			epaisseurMilieu = 0.8;
			epaisseurHaute = 0.5;
			break;
		default :
			cout << "Mauvais choix de forme" << endl;
	}

}