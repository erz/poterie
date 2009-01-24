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
		//float 	xi[30],
		 //       yi[30];
		//cout<<"Courbes Intermediaires:"<<endl;
		
		
		for(int i=0;i<seq->getCourbe(0)->getPointsControle()->size();i++)
		{

			vector<Point*> courbeIntermediaire;
			for(int j=0;j<seq->getNbImages()-4;j++)
			{
				Point *Nv= new Point();

				if(j<seq->getNbImages()-5)
				{
					vector<Point*> tmp0=*(seq->getCourbe(j)->getPointsControle());
					vector<Point*> tmp1=*(seq->getCourbe(j+1)->getPointsControle());
					vector<Point*> tmp2=*(seq->getCourbe(j+2)->getPointsControle());
					vector<Point*> tmp3=*(seq->getCourbe(j+3)->getPointsControle());

					//Nv->x=(int)tmp0[i]->x+300*j+150;

					Nv->y=(int)interpolationCubique(tmp0[i]->y,tmp1[i]->y,tmp2[i]->y,tmp3[i]->y,0.5);
					Nv->x=(int)(tmp0[i]->x+tmp1[i]->x)/2;

					courbeIntermediaire.push_back(Nv);
				}
				else
				{
					
					vector<Point*> tmp0=*(seq->getCourbe(j+1)->getPointsControle());
					vector<Point*> tmp1=*(seq->getCourbe(j+2)->getPointsControle());
					Nv->y=(int)interpolationLinéaire(tmp0[i]->y,tmp1[i]->y,0.5);
					Nv->x=(tmp0[i]->x+tmp1[i]->x)/2;
					courbeIntermediaire.push_back(Nv);

					tmp0=*(seq->getCourbe(j+2)->getPointsControle());
					tmp1=*(seq->getCourbe(j+3)->getPointsControle());
					Nv->y=(int)interpolationLinéaire(tmp0[i]->y,tmp1[i]->y,0.5);
					Nv->x=(tmp0[i]->x+tmp1[i]->x)/2;
					courbeIntermediaire.push_back(Nv);

				}
				
				
				//cout<<"x:\t"<<Nv->x<<"  y\t"<<Nv->y<<endl;
			}
			listeCourbes->push_back(courbeIntermediaire);
			
		}
		/*
		vector<CPoterieCourbe *> listeCourbes;
		vector<Point *> courbesTransv ;
		for(int j=0;j<19;j++)
		{

			for(int i=0;i<seq->getNbImages();i++)
			{
				vector<Point*> tmp0=*(seq->getCourbe(i)->getPointsControle());
				Point *Nv = new Point();
				Nv->x=tmp0[j]->x;
				Nv->y=tmp0[j]->y;
				courbesTransv.push_back(Nv);
			}
			CPoterieCourbe * courbeInt= new CPoterieCourbe(&courbesTransv);
			listeCourbes.push_back(courbeInt);
		}
		
		*/
		
	cvNamedWindow( "Interpolation", 1 );
	IplImage* BSpline = cvCreateImage( cvSize(300,300), 8, 1 );
	
	vector<Point *> courbeIntermediaire;
	
	int numeroCourbe=7;
	for(int k=0;k<seq->getCourbe(0)->getPointsControle()->size();k++)
	{
		Point * Pt= new Point();
		Pt->x=(*listeCourbes)[k][numeroCourbe]->x;
		Pt->y=(*listeCourbes)[k][numeroCourbe]->y;
		courbeIntermediaire.push_back(Pt);
	}
	
	CPoterieCourbe * courbe= new CPoterieCourbe(&courbeIntermediaire);
	
	for(int i=0;i<(courbe->getBspline()->size())-1;i++)
	{
		CvPoint pt[2], *rect = pt;
		int count=2;
		pt[0].x=(*courbe->getBspline())[i]->x;
		pt[0].y=(*courbe->getBspline())[i]->y;

		pt[1].x=(*courbe->getBspline())[i+1]->x;
		pt[1].y=(*courbe->getBspline())[i+1]->y;
		cvPolyLine( BSpline, &rect, &count, 1, 0, CV_RGB(255,255,255), 1, 0, 0 );
	}
	
	/*
	int numeroCourbe=6;
	for(int i=0;i<19-1;i++)
	{
		CvPoint pt[2], *rect = pt;
		int count=2;

		pt[0].x=(*listeCourbes)[i][numeroCourbe]->x;
		pt[0].y=(*listeCourbes)[i][numeroCourbe]->y;

		pt[1].x=(*listeCourbes)[i+1][numeroCourbe]->x;
		pt[1].y=(*listeCourbes)[i+1][numeroCourbe]->y;
		cvPolyLine( BSpline, &rect, &count, 1, 0, CV_RGB(255,255,255), 1, 0, 0 );
		cout<<"X:"<<pt[0].x<<"\tY:"<<pt[0].y<<endl;

		
	}
	*/
	cvShowImage( "Interpolation", BSpline );

	}
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


double CCourbesIntermediaires::interpolationLinéaire(double v1, double v2, double mu)
  {
      return(v1*(1-mu)+v2*mu);
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