/* date de derniere modification : 19 mars 1993
   -----------------------------
Ce fichier .h concerne les courbes, d'ou le suffixage par _c ou _C.
Certaines definitions n'utilisent pas ce suffixage car elles interviennent aussi
dans le cas des surfaces (MAX_ORDRE,table_fonctions,table_travail).

             POUR UTILISER CETTE BIBLIOTHEQUE, L'UTILISATEUR DOIT DEFINIR
             LES DIFFERENTES CONSTANTES CI-DESSOUS (avant de faire le #include bspline.h)
exemple de definition  :
#define MAX_ORDRE 10     : ORDRE MAXIMUM DES FONCTIONS DE BASE (courbe ou surface)
#define MAX_PTS_C 1000   : NOMBRE DE POINTS DE CONTROLE MAXIMUM SUR UNE COURBE
 */
/*           definition des types de manipulations de courbes B-splines
             les types table_fonctions et table_travail ne sont effectivement utilise qu'a partir
             de l'indice 1
             Les +1 proviennent du depart systematique de C a l'indice 0
 */

#pragma once

#define MAX_ORDRE 10
#define MAX_PTS_C 1000

typedef float matrice[MAX_PTS_C+1*MAX_PTS_C+1];
typedef float coor_pts[MAX_PTS_C+1]; 
typedef float coor_pts_controle_c[MAX_PTS_C+1];      /* toujours le dilemme  n points, n+1 points */
typedef float vecteur_noeuds[MAX_PTS_C+1+MAX_ORDRE]; /* idem */
typedef float table_fonctions[MAX_ORDRE+1];
typedef float table_travail[1+MAX_ORDRE*(MAX_ORDRE+1)/2];
typedef float table_travail_int[1+MAX_ORDRE*(MAX_ORDRE+1)/2];

/*
             fonctions
 */

void posit();
/*
       vecteur_noeuds   vknot;
       float            t;
       int              *i,k,imax;
 */
void calbsp();
/*
       vecteur_noeuds     vknot;
       float              t;
       int                i,k;
       table_fonctions    b;
 */
void calc2x();
/*
       coor_pts_controle_c xcontr,ycontr;
       float               t,*xcal,*ycal;
       vecteur_noeuds      vknot;
       int                 imax,k;
       table_fonctions     b;
       int                 *i;
 */