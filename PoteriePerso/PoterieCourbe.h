#pragma once

#include "Outils.h"
#include <vector>

class CPoterieCourbe
{
	public:
		int B0(int i,int x);
		float B1(int i,int x);
		float B2(int i,int x);
		void calculcoeff(int n,std::vector<Point *> points);
		void InterpolationBSpline(std::vector<Point *>*);
		CPoterieCourbe (std::vector<Point *>*);
	private:
		int t[100];
		float A[200];

};