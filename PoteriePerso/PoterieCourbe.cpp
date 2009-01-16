#include "stdafx.h"
#include "PoterieCourbe.h"
#include "InterpolationSpline.h"
#include <vector>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <math.h>

#include <algorithm>

using namespace std;

struct TriAscendant
	{		
		inline bool operator() (Point * a, Point * b) const
		{
				return a->y < b->y;
		}
	};

void CPoterieCourbe::InterpolationBSpline(vector <Point *> *pts)
{
	////////////////////////////
	//Methode MD
	///////////////////////////////

	//Valeur maximales
	int N = 210;
	int M = 210;
	int K = 4;

	//Degré
	int k = 3;

	//Nombre de points
	int n = (int)(pts->size())-1;

	//Nombre de points de controle
	static int m = 0;

	if (m == 0 )
	{ 
		if ( n >= 19)
			m = 19;
		else
			m = n;
	}

	//Coordonnées des points d'entrée
	coor_pts	x = MemVecteurFloat(N);
	coor_pts	y = MemVecteurFloat(N);

	sort((*pts).begin(),(*pts).end(),TriAscendant());

	//Remplissage des points d'entree
	for (int i = 0; i <= n; ++i)
	{
		x[i] = (float)(*pts)[i]->x;
		y[i] = (float)(*pts)[i]->y;

		//cout << x[i] << "\t" << y[i] << endl;
	}

	//Coordonnées des points de controle
	coor_pts_controle_c	xcontr = MemVecteurFloat(M);
	coor_pts_controle_c	ycontr = MemVecteurFloat(M);

	//vecteur des parametres
	vecteur_parametres	vzeta  = MemVecteurFloat(N);
	vecteur_noeuds		vknot  = MemVecteurFloat(M+K);
	
	//indice du dernier noeud de vknot
	int	imax;		
	
	//choix de parametrisation
	int choix_para = 1;
	
	//choix du vecteur de noeud
	int choix_noeuds = 1;

	//indice de bon deroulement 
	int ir;		

	//conditionnement du systeme
	float condi;

	//erreurs moyenne et superieure
	float emoy, esup;
	
	//une distance inferieure ou egale a eps entraine que les deux entites sont egales 
	float eps = (float)1e-04;

	//matrice du systeme lineaire
	matrice bnik = MemVecteurFloat((N+5)*(N+2));

	table_travail_int	jf = MemVecteurInt(M);
	table_fonctions		b  = MemVecteurFloat(K);

	//parameterisation
	parameterization(x, y, n, m, k, vzeta, xcontr, ycontr, vknot, &imax, &ir, &condi, &emoy, &esup, choix_para, choix_noeuds);

	//Noeuds
	knots(n,m,k,vzeta,&imax,vknot,choix_noeuds);

	//Approximation de la BSpline
	li2coc(x,y,n,m,k,vzeta,bnik,N+1,b,jf,xcontr,ycontr,vknot,&imax,&ir, &condi,&emoy,&esup);

	//Point d'entree
	cout << "Points d'entrée" << endl;
	for (int i = 0; i <= n; ++i)
		cout << i << ":" << x[i] << "\t" << y[i] << endl;

	//Points de controle
	pointsControle = new std::vector<Point *>;
	cout << "Points de controle" << endl;
	for (int i = 0; i <= m; ++i)
	{
		Point *pt = new Point;
		pt->x = (int)xcontr[i];
		pt->y = (int)ycontr[i];
		pointsControle->push_back(pt);
		cout << i << ":" << pt->x << "\t" << pt->y << endl;
	}

	//Vecteur de noeuds
	vecteurNoeuds = vknot;
	cout << "Vecteur de noeuds" << endl;
	for (int i = 0; i <= imax; ++i)
	{
		cout << vecteurNoeuds[i] << " - ";
	}
	cout << endl;

	//Points sur la BSpline
	bspline = new std::vector<Point *>;

	float t, pas, l, xcal, ycal;
    pas = (vknot[imax]-vknot[0])/(N-1);
	t=vknot[0];
	cout << "BSpline : " << endl;
	for(l=0;l<N-1;l=l+1)
	{
		calc2x(xcontr,ycontr,t,&xcal,&ycal,vknot,imax,k,b,&ir);
		t=t+pas;
		Point* pt = new Point;
		pt->x = (int)xcal;
		pt->y = (int)ycal;
		bspline->push_back(pt);
		cout << l << ": " << pt->x << "\t" << pt->y << endl;
	}

    t=vknot[imax];
	calc2x(xcontr,ycontr,t,&xcal,&ycal,vknot,imax,k,b,&ir);

	Point* pt = new Point;
	pt->x = (int)xcal;
	pt->y = (int)ycal;
	bspline->push_back(pt);

	//Affichage de la BSpline
	IplImage* cnt_img = cvCreateImage( cvSize(300, 300), 8, 3 );
    cvZero( cnt_img );

	cvNamedWindow("BSpline", 0);

	for (unsigned int i = 0; i+1 < bspline->size(); i+=2)
	{
		CvPoint pt[2], *rect = pt;
		int count=2;
		pt[0].x=(*bspline)[i]->x;
		pt[0].y=(*bspline)[i]->y;
		pt[1].x=(*bspline)[i+1]->x;
		pt[1].y=(*bspline)[i+1]->y;
		cvPolyLine( cnt_img, &rect, &count, 1, 0, CV_RGB(255,255,255), 1, 0, 0 );
	}

	cvShowImage("BSpline", cnt_img);
	cvWaitKey();
	
	//Liberation mémoire
	FreeVecteurFloat(&x);
	FreeVecteurFloat(&y);
	FreeVecteurFloat(&xcontr);
	FreeVecteurFloat(&ycontr);
	FreeVecteurFloat(&vknot);
	FreeVecteurFloat(&vzeta);
	FreeVecteurFloat(&bnik);
	FreeVecteurFloat(&b);
	FreeVecteurInt(&jf);
}

std::vector<Point *>* CPoterieCourbe::getPointsControle()
{
	return pointsControle;
}

float* CPoterieCourbe::getVecteurNoeuds()
{
	return vecteurNoeuds;
}

std::vector<Point *>* CPoterieCourbe::getBspline()
{
	return bspline;
}

CPoterieCourbe::CPoterieCourbe (vector <Point *> *pts)
{
	InterpolationBSpline(pts);
}