#pragma once
#include "afxwin.h"
#include <afxstr.h>
#include <iostream>
#include <CString>

#define MAX_ORDRE 10
#define MAX_PTS_C 1000

typedef float *matrice;
typedef float* coor_pts; 
typedef float* vecteur_parametres; 
typedef int* table_travail_int;
typedef float* coor_pts_controle_c;      /* toujours le dilemme  n points, n+1 points */
typedef float* vecteur_noeuds; /* idem */
typedef float* table_fonctions;
typedef float* table_travail;


/*
             fonctions
 */

/*
       vecteur_noeuds   vknot;
       float            t;
       int              *i,k,imax;
 */
void posit();

/*
       vecteur_noeuds     vknot;
       float              t;
       int                i,k;
       table_fonctions    b;
 */
void calbsp();


/*
       coor_pts_controle_c xcontr,ycontr;
       float               t,*xcal,*ycal;
       vecteur_noeuds      vknot;
       int                 imax,k;
       table_fonctions     b;
       int                 *i;
 */
void calc2x();

/*
	matrice a;
	int n, l, k, nmax, *k1;
	float *e1;
*/
void normrs(matrice, int, int, int, int, int *,float *);

/*
	matrice a;
	int ns, nc, nmax;
*/
void resors(matrice, int, int, int);

/*
	matrice a;
	int nmax, nl, nc, ns;
	float eps;
	int *ir;
	table_travail_int jf;
*/
void housrs(matrice, int, int, int, int, float, int *, table_travail_int);

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
void li2coc(coor_pts, coor_pts, int, int, int, vecteur_parametres,
            matrice, int, table_fonctions, table_travail_int,
            coor_pts_controle_c, coor_pts_controle_c, vecteur_noeuds, 
            int *, int *, float *, float *, float *);