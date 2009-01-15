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
	return (x-t[i])/(t[i+1]-t[i])*B0(i,x)+(t[i+2]-x)/(t[i+2]-t[i+1])*B0(i+1,x);
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
		q=(t[i]-t[i+1])/(t[i]-t[i-1]);
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
	/*
	IplImage *img=cvCreateImage( cvSize(300,300), 8, 3);
	vector<Point *> points=*(pts);
	vector<Point *>Spline ;
	Point * tmp=new Point();


	//Vecteur de noeud
	t[0]=t[1]=t[2]=0;
	int c=0;
	for(int j=3;j<96;j++)
	{
		t[j]=c-3;
		c++;
	}
	t[96]=t[97]=t[98]=c+1;


	//Bspline
	for(unsigned int i=0;i<pts->size()-1;i++)
	{
		tmp->x= (points[i]->x+points[i+1]->x)/2;
		if((points[i+1]->x-points[i]->x)>0.0001)
			tmp->y= points[i]->y + ( (points[i+1]->y - points[i]->y) / (points[i+1]->x-points[i]->x))*(tmp->x-points[i]->x);
		else tmp->y= points[i]->y;
		
		//cout<<"Point "<<i<<" x: "<<tmp->x<<"\ty: "<<tmp->y<<endl;
		cvCircle(img,cvPoint(tmp->x,tmp->y),1,CV_RGB(0,255,0),1);
		//Spline.push_back(tmp);
	}
	
	
	cvNamedWindow("Interpolation",CV_WINDOW_AUTOSIZE);
	
	cvShowImage("Interpolation",img);
	cvWaitKey(0);
	*/

	////////////////////////////
	//Methode MD
	///////////////////////////////

	
	//Degré
	int k = 3;

	//Nombre de points
	int n = (pts->size());

	//Nombre de points de controle
	int m = 20;

	//Coordonnées des points d'entrée
	coor_pts	x = (coor_pts) malloc (sizeof(float)*n);
	coor_pts	y = (coor_pts) malloc (sizeof(float)*n);

	for (unsigned int i = 0; i < n; ++i)
	{
		x[i] = (*pts)[i]->x;
		y[i] = (*pts)[i]->y;

		cout << x[i] << "\t" << y[i] << endl;
	}

	//Coordonnées des points de controle
	coor_pts_controle_c	xcontr = (coor_pts_controle_c) malloc (sizeof(float)*m);
	coor_pts_controle_c	ycontr = (coor_pts_controle_c) malloc (sizeof(float)*m);

	//vecteur des parametres
	vecteur_parametres	vzeta  = (vecteur_parametres) malloc (sizeof(float)*n);

//vecteur_parametres	vzeta;		/* vecteur des parametres             */
//vecteur_noeuds 		vknot;		/* vecteurs de noeuds                 */
//int 			imax;		/* indice du dernier noeud de vknot   */
//vecteur_char		chaine;		/* chaines de caracteres              */
//int			choix_para,	/* choix de l'utilisateur en matiere  */
					/* de parametrisation                 */
//			choix_noeuds,	/* choix de l'utilisateur en matiere  */
					/* de vecteur de noeuds               */
//			ir;		/* indice de bon deroulement          */
//float                   condi,		/* conditionnement du systeme         */
  //                      emoy, esup;	/* erreurs moyenne et superieure      */
//float 			eps;		/* une distance inferieure ou egale a */
					/* eps entraine que les deux entites  */
					/* sont egales                        */
//matrice                 bnik;           /* matrice du systeme lineaire        */
//table_travail_int       jf;
//table_fonctions		b;
//char                    *chaine1,  
 //                       *chaine2;       /* chaines de caracteres              */
//   vknot=MemVecteurFloat(M+K);
  // vzeta=MemVecteurFloat(N);
  // bnik=MemVecteurFloat((N+5)*(N+2));
  // b=MemVecteurFloat(K);
  // jf=MemVecteurInt(M);
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
	cout << "HAHAH" << endl;
	InterpolationBSpline(pts);
	//rebuild(pts);
}