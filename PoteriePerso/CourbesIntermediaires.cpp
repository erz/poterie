#include "stdafx.h"
#include "CourbesIntermediaires.h"



void calculerCourbesIntermediaires()
{
	bool sequenceBalaye=false;
	if(seq->getIdCour()==seq->getNbImages()-1)
	{
		sequenceBalaye=true;
	}

	if(sequenceBalaye==true)
	{
		vector<vector<Point*>> listeCourbes; 
		cout<<"Courbes Intermediaires:"<<endl;
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
				Nv->x=(tmp0[i]->x+tmp1[i]->x)/2;
				courbeIntermediaire.push_back(Nv);
				cout<<"x:\t"<<Nv->x<<"  y\t"<<Nv->y<<endl;
			}
			listeCourbes.push_back(courbeIntermediaire);
		}
	}
}

double interpolationCubique(double y0,double y1,double y2,double y3,double mu)
  {
     double a0,a1,a2,a3,mu2;
  
     mu2 = mu*mu;
     a0 = y3 - y2 - y0 + y1;
     a1 = y0 - y1 - a0;
     a2 = y2 - y0;
     a3 = y1;
	//cout<<"**********"<<endl;
	//cout<<a0*mu*mu2+a1*mu2+a2*mu+a3<<endl;
     return (a0*mu*mu2+a1*mu2+a2*mu+a3);
  }

