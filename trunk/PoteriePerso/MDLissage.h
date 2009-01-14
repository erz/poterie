/******************************************************************************/
/*                                                                            */
/*                       Eric SAUX  (OCTOBRE 1995)                            */
/*                                                                            */
/*             E.C.N.    1 RUE DE LA NOE  44072 NANTES CEDEX 3                */
/*             INSTITUT DE RECHERCHE EN INFORMATIQUE DE NANTES                */
/*                                                                            */
/******************************************************************************/

#pragma once

#include "stdafx.h"


void normrs(matrice, int, int, int, int, int *,float *);
/*
	matrice a;
	int n, l, k, nmax, *k1;
	float *e1;
*/

void resors(matrice, int, int, int);
/*
	matrice a;
	int ns, nc, nmax;
*/

void housrs(matrice, int, int, int, int, float, int *, table_travail_int);
/*
	matrice a;
	int nmax, nl, nc, ns;
	float eps;
	int *ir;
	table_travail_int jf;
*/

void li2coc(coor_pts, coor_pts, int, int, int, vecteur_parametres,
            matrice, int, table_fonctions, table_travail_int,
            coor_pts_controle_c, coor_pts_controle_c, vecteur_noeuds, 
            int *, int *, float *, float *, float *);
/*
	coor_pts x, y;
	int n, m, k;
	vecteur_parametres zeta;
	matrice bnik;
	int nmax;
	table_fonctions b;
	table_travail_int jf;
	coor_pts_controle_c xcontr, ycontr;
	vecteur_noeuds vknot;
	int *imax, *ir;
	float *condi, *emoy, *esup;
*/