#pragma once
//#include "VariablesGlobales.h"
#include <vector>
#include "Outils.h"

using namespace std;

class CCourbesIntermediaires
{
	private :
		vector<vector<Point*>> *listeCourbes; 
	public :
		CCourbesIntermediaires();
		void calculerCourbesIntermediaires();
		double interpolationCubique(double y0,double y1,double y2,double y3,double mu);

		vector<vector<Point*>> *getListeCourbes();
};
