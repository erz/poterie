#include "stdafx.h"
#include "CourbesIntermediaires.h"
#include "VariablesGlobales.h"

CCourbesIntermediaires::CCourbesIntermediaires()
{
	listeCourbes = new vector<vector<Point*>>;
	calculerCourbesIntermediaires();
}

void CCourbesIntermediaires::calculerCourbesIntermediaires()
{
	if(seq!=NULL && seq->getNbImages() > 0)
	{	
		float 	xi[100],
		        yi[100];
		//cout<<"Courbes Intermediaires:"<<endl;
		
		/*
		for(int i=0;i<19;i++)
		{

			vector<Point*> courbeIntermediaire;
			for(int j=0;j<seq->getNbImages()-4;j++)
			{
				Point *Nv= new Point();
				vector<Point*> tmp0=*(seq->getCourbe(j)->getPointsControle());
				vector<Point*> tmp1=*(seq->getCourbe(j+1)->getPointsControle());
				vector<Point*> tmp2=*(seq->getCourbe(j+2)->getPointsControle());
				vector<Point*> tmp3=*(seq->getCourbe(j+3)->getPointsControle());

				//Nv->x=(int)tmp0[i]->x+300*j+150;
				Nv->y=(int)interpolationCubique(tmp0[i]->y,tmp1[i]->y,tmp2[i]->y,tmp3[i]->y,0.5);
				Nv->x=(int)(tmp0[i]->x+tmp1[i]->x)/2;
				
				lagrange()
				
				//courbeIntermediaire.push_back(Nv);
				//cout<<"x:\t"<<Nv->x<<"  y\t"<<Nv->y<<endl;
			}
			listeCourbes->push_back(courbeIntermediaire);
			
		}

		*/
		/*
		for(int i=0;i<19;i++)
		{
			vector<Point*> courbeIntermediaire;
			vector<Point*> tmp0;
			for(int j=0;j<seq->getNbImages();j++)
			{
				    tmp0=*(seq->getCourbe(j)->getPointsControle());
					xi[j]=(float)(tmp0[i]->x-tmp0[0]->x+10*j);
					yi[j]=(float)(tmp0[i]->y);
					cout<<"X:"<<xi[j]<<"\tY:"<<yi[j]<<endl;
			}
			
			float pas=1.0;
			float inf=0;
			float sup=xi[seq->getNbImages()];
			int n=abs(sup-inf)/pas;

			for(int k=0;k<n;k++)
			{
				Point *Nv= new Point();
				Nv->x=(int)inf;
				Nv->y=(int)lagrange(xi, yi,(int)Nv->x,seq->getNbImages() );
				inf+=pas;
				courbeIntermediaire.push_back(Nv);
				cout<<"retour lagrange :"<<Nv->y<<endl;
			}
			listeCourbes->push_back(courbeIntermediaire);
		}
	}
		
	cvNamedWindow( "Interpolation", 1 );
	IplImage* BSpline = cvCreateImage( cvSize(300,300), 8, 1 );

	int numeroCourbe=0;
	for(int i=0;i<(*listeCourbes)[numeroCourbe].size()-1;i++)
	{
		CvPoint pt[2], *rect = pt;
		int count=2;

		pt[0].x=(*listeCourbes)[numeroCourbe][i]->x;
		pt[0].y=(*listeCourbes)[numeroCourbe][i]->y;

		pt[1].x=(*listeCourbes)[numeroCourbe][i+1]->x;
		pt[1].y=(*listeCourbes)[numeroCourbe][i+1]->y;
		cvPolyLine( BSpline, &rect, &count, 1, 0, CV_RGB(255,255,255), 1, 0, 0 );
		cout<<"X:"<<pt[0].x<<"\tY:"<<pt[0].y<<endl;

		*/
	}
	
	//cvShowImage( "Interpolation", BSpline );

}

double CCourbesIntermediaires::interpolationCubique(double y0,double y1,double y2,double y3,double mu)
{
     double a0,a1,a2,a3,mu2;
  
     mu2 = mu*mu;
     a0 = y3 - y2 - y0 + y1;
     a1 = y0 - y1 - a0;
     a2 = y2 - y0;
     a3 = y1;
     return (a0*mu*mu2+a1*mu2+a2*mu+a3);
}

float CCourbesIntermediaires::lagrange(float xi[], float yi[], int x, int n)
{
	int i,j;
	float somme=0,mul;

		for(i=0;i<n;i++)
		{
			mul=1;
			for(j=0;j<n;j++)
			{
				if(i!=j)
					mul*=(x-xi[j])/(xi[i]-xi[j]);
			}
			somme+=yi[i]*mul;
		}

	return somme;
}

vector<vector<Point*>>* CCourbesIntermediaires::getListeCourbes()
{
	return listeCourbes;
}