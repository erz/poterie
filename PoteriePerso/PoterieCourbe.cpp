#include "stdafx.h"
#include "PoterieCourbe.h"
#include "InterpolationSpline.h"
#include <vector>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <math.h>

using namespace std;
/*
int CPoterieCourbe::B0(int i,int x)
{
	if(x<t[i]&& x>t[i+1]) return 0;
	else return 1;

}

float CPoterieCourbe::B1(int i,int x)
{
	return (x-t[i])/(float)(t[i+1]-t[i])*B0(i,x)+(t[i+2]-x)/(float)(t[i+2]-t[i+1])*B0(i+1,x);
}

float CPoterieCourbe::B2(int i,int x)
{
	return (x-t[i])/(t[i+2]-t[i])*B1(i,x)+(t[i+3]-x)/(t[i+3]-t[i+1])*B1(i+1,x);
}


void CPoterieCourbe::calculcoeff(int n,vector<Point *> points)
{
	float gamma[200];
	float delta[200];
	float q,u,v;
	gamma[0]=0;
	delta[0]=1;
	

	for(int i=0;i<n;i++)
	{	
		q=(float)(t[i]-t[i+1])/(float)(t[i]-t[i-1]);
		gamma[i]=gamma[i-1]*q+points[i]->y*(1-q);
		delta[i]=delta[i-1]*q;
		u=u+delta[i]*gamma[i];
		v=v+sqrt(delta[i]);
	}

	A[0]=-u/v;
	for(int i=0;i<n;i++)
	{
		A[i]=gamma[i]+delta[i]*A[0];
	}

}

*/

void CPoterieCourbe::InterpolationBSpline(vector <Point *> *pts)
{
	////////////////////////////
	//Methode MD
	///////////////////////////////

	
	//Degré
	int k = 3;

	//Nombre de points
	int n = (int)(pts->size());

	//Nombre de points de controle
	int m = 20;

	if (m>n)
		m = n;

	//Coordonnées des points d'entrée
	coor_pts	x = MemVecteurFloat(n);
	coor_pts	y = MemVecteurFloat(n);

	for (int i = 0; i < n; ++i)
	{
		x[i] = (float)(*pts)[i]->x;
		y[i] = (float)(*pts)[i]->y;

		//cout << x[i] << "\t" << y[i] << endl;
	}

	//Coordonnées des points de controle
	coor_pts_controle_c	xcontr = MemVecteurFloat(m);
	coor_pts_controle_c	ycontr = MemVecteurFloat(m);

	//vecteur des parametres
	vecteur_parametres	vzeta  = MemVecteurFloat(n);
	vecteur_noeuds		vknot  = MemVecteurFloat(m+k);
	
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
	matrice bnik = (matrice) malloc (sizeof(float)*((n+5)*(n+2)));

	table_travail_int	jf = MemVecteurInt(m);
	table_fonctions		b  = MemVecteurFloat(k);

	//parameterisation
	parameterization(x, y, n, m, k, vzeta, xcontr, ycontr, vknot, &imax, &ir, &condi, &emoy, &esup, choix_para, choix_noeuds);

	//Noeuds
	knots(n,m,k,vzeta,&imax,vknot,choix_noeuds);

	//Approximation de la BSpline
	li2coc(x,y,n,m,k,vzeta,bnik,n+1,b,jf,xcontr,ycontr,vknot,&imax,&ir, &condi,&emoy,&esup);

	//Points de controle
	pointsControle = new std::vector<Point *>;
	cout << "Points de controle" << endl;
	for (int i = 0; i < m; ++i)
	{
		Point *pt = new Point;
		pt->x = (int)xcontr[i];
		pt->y = (int)ycontr[i];
		pointsControle->push_back(pt);
		cout << pt->x << "\t" << pt->y << endl;
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
    pas = (vknot[imax]-vknot[0])/(n-1);
	t=vknot[0];
	cout << "BSpline : " << endl;
	for(l=0;l<n-1;l=l+1)
	{
		calc2x(xcontr,ycontr,t,&xcal,&ycal,vknot,imax,k,b,&ir);
		t=t+pas;
		Point* pt = new Point;
		pt->x = (int)xcal;
		pt->y = (int)ycal;
		bspline->push_back(pt);
		cout << pt->x << "\t" << pt->y << endl;
	}

    t=vknot[imax];
	calc2x(xcontr,ycontr,t,&xcal,&ycal,vknot,imax,k,b,&ir);

	Point* pt = new Point;
	pt->x = (int)xcal;
	pt->y = (int)ycal;
	bspline->push_back(pt);

	//Affichage de la BSpline
	/*IplImage* cnt_img = cvCreateImage( cvSize(300, 300), 8, 3 );
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
*/
	
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
/*
double distance2D(Point A, Point B) {
	int ux = A.x-B.x;
	int uy = A.y-B.y;
	double un = ux*ux+uy*uy;
	return sqrt(un);
}
*/

std::vector<Point *>* CPoterieCourbe::getPointsControle()
{
	return pointsControle;
}

float* getVecteurNoeuds()
{
	return vecteurNoeuds;
}

std::vector<Point *>* getBspline()
{
	return bspline;
}

CPoterieCourbe::CPoterieCourbe (vector <Point *> *pts)
{
	InterpolationBSpline(pts);
}