#include "stdafx.h"
#include "PoterieCourbe.h"
#include "InterpolationSpline.h"
#include <vector>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <math.h>

using namespace std;

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

	
	cout << "Points d'entree" << endl;
	for (int i = 0; i < n; ++i)
		cout << x[i] << " " << y[i] << endl;

	cout << "Points de controle" << endl;
	for (int i = 0; i < m; ++i)
		cout << xcontr[i] << " " << ycontr[i] << endl;

	cout << "Vecteur de noeud" << endl;
	for (int i = 0; i < imax; ++i)
		cout << vknot[i] << endl;


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

double distance2D(Point A, Point B) {
	int ux = A.x-B.x;
	int uy = A.y-B.y;
	double un = ux*ux+uy*uy;
	return sqrt(un);
}

// TEST SNAKE
// rebuild the snake using cubic spline interpolation
void CPoterieCourbe::rebuild(vector <Point *> *pts) 
{
	vector <Point*> snake = *(pts);
	int space = 16;
	// precompute length(i) = length of the snake from start to point #i
	double *clength = new double[snake.size()+1];
	clength[0]=0;
	for(unsigned int i=0;i<snake.size();i++) 
	{
		Point cur   = *(snake[i]);
		Point next  = *(snake[(i+1)%snake.size()]);
		clength[i+1]=clength[i]+distance2D(cur, next);
	}
 
	// compute number of points in the new snake
	double total = clength[snake.size()];
	int nmb = (int)(0.5+total/space);
 
	// build a new snake
	vector<Point*> newsnake;
	for(int i=0,j=0;j<nmb;j++) 
	{
		// current length in the new snake
		double dist = (j*total)/nmb;
 
		// find corresponding interval of points in the original snake
		while(! (clength[i]<=dist && dist<clength[i+1])) i++;
 
		// get points (P-1,P,P+1,P+2) in the original snake
		Point prev  = *(snake[(i+snake.size()-1)%snake.size()]);
		Point cur   = *(snake[i]);
		Point next  = *(snake[(i+1)%snake.size()]);
		Point next2  = *(snake[(i+2)%snake.size()]);
 
		// do cubic spline interpolation
		double t =  (dist-clength[i])/(clength[i+1]-clength[i]);
		double t2 = t*t, t3=t2*t;
		double c0 =  1*t3;
		double c1 = -3*t3 +3*t2 +3*t + 1;
		double c2 =  3*t3 -6*t2 + 4;
		double c3 = -1*t3 +3*t2 -3*t + 1;
		double x = prev.x*c3 + cur.x*c2 + next.x* c1 + next2.x*c0;
		double y = prev.y*c3 + cur.y*c2 + next.y* c1 + next2.y*c0;
		Point* newpoint = new Point();
		newpoint->x = (int)(0.5+x/6);
		newpoint->y = (int)(0.5+y/6);
 
		// add computed point to the new snake
		newsnake.push_back(newpoint);
	}
	
	/*cout << "Snake : " << endl;
	for (int i = 0; i < snake.size(); ++i)
		cout << "Point\t" << i << "\tX :\t" << snake[i]->x << "\tY :\t" << snake[i]->y << endl;

	cout << "\nNewSnake : " << endl;
	IplImage *img=cvCreateImage( cvSize(300,300), 8, 3);
	for (int i = 0; i < newsnake.size(); ++i)
	{
		cout << "Point\t" << i << "\tX :\t" << newsnake[i]->x << "\tY :\t" << newsnake[i]->y << endl;
		cvCircle(img,cvPoint(newsnake[i]->x,newsnake[i]->y),1,CV_RGB(0,255,0),1);
	}
	
	cvNamedWindow("Interpolation",CV_WINDOW_AUTOSIZE);
	cvShowImage("Interpolation",img);
	cvWaitKey(0);
	*/
}


CPoterieCourbe::CPoterieCourbe (vector <Point *> *pts)
{
	InterpolationBSpline(pts);
	//rebuild(pts);
}