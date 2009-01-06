#include "stdafx.h"
#include "PoterieCourbe.h"
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
	for(int i=0;i<pts->size()-1;i++)
	{
		tmp->x= (points[i]->x+points[i+1]->x)/2;
		if((points[i+1]->x-points[i]->x)>0.0001)
			tmp->y= points[i]->y + ( (points[i+1]->y - points[i]->y) / (points[i+1]->x-points[i]->x))*(tmp->x-points[i]->x);
		else tmp->y= points[i]->y;
		
		cout<<"Point "<<i<<" x: "<<tmp->x<<"\ty: "<<tmp->y<<endl;
		cvCircle(img,cvPoint(tmp->x,tmp->y),1,CV_RGB(0,255,0),1);
		//Spline.push_back(tmp);
	}
	
	
	cvNamedWindow("Interpolation",CV_WINDOW_AUTOSIZE);
	
	cvShowImage("Interpolation",img);
	cvWaitKey(0);
	
}

CPoterieCourbe::CPoterieCourbe (vector <Point *> *pts)
{
	InterpolationBSpline(pts);
}