#pragma once

#include "Outils.h"
#include <vector>

class CPoterieCourbe
{
	public:
		//int B0(int i,int x);
		//float B1(int i,int x);
		//float B2(int i,int x);
		//void calculcoeff(int n,std::vector<Point *> points);
		void InterpolationBSpline(std::vector<Point *>*);
		CPoterieCourbe (std::vector<Point *>*);
		
		std::vector<Point *>* getPointsControle();
		float* getVecteurNoeuds();
		std::vector<Point *>* getBspline();

	private:
		//int t[100];
		//float A[200];
		std::vector<Point *>* pointsControle;
		float* vecteurNoeuds;
		std::vector<Point *>* bspline;
};