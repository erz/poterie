
/* declarations a ne pas mettre en commentaire pour pouvoir effectuer
   la compilation separee de ce fichier. Ces valeurs ne sont pas forcement
   celles de l'utilisateur, mais ceci n'a aucune importance puisqu'il s'agit de vecteurs
   (sorte de dimensionnement variable)
 */
#define MAX_PTS_C 100
#define MAX_ORDRE 10

#include "stdafx.h"
#include "MDBSpline.h"
/*---------------------------------------------------------------------------------------

    M. DANIEL 
    ECN        1 rue de la noe 44072 Nantes cedex 03  tel : 40.37.25.98

    date de derniere modification : 22/03/1993
-----------------------------------------------------------------------------------------
                       fonctions C de base pour le calcul de points
                       d'une courbe B-spline
 */
/*---------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------*/
/*                     positionnement du parametre dans le vecteur de noeuds 
 */
void posit(vecteur_noeuds vknot,float t,int *i,int k,int imax)
{
float  tmin,tmax;

tmin=vknot[0];
tmax=vknot[imax-k+1];
 
if ((t<tmin) || (t>tmax))
   *i=-1;                       /* en dehors de l'intervalle parametrique    */
else
   {
   if (t==tmax)
      {
      *i=imax-k;                /* theoriquement, i=imax-k en sortie         */
      while ((vknot[*i]==vknot[*i+1]) && (*i>0))
         *i=*i-1;
      if (*i==0)
         *i=-2;                 /* erreur dans le vecteur de noeuds          */
      }
   else
      {
      *i=k-1;                   /* cas general : recherche a partir du debut */
      while ((t>=vknot[*i]) && (*i<imax))
         *i=*i+1;
      if (*i==imax)
         *i=-2;
      else
         *i=*i-1;
      }
   }
}
/*---------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------*/
/*                     calcul des k fonctions de base non nulles en t
 */
void calbsp(vecteur_noeuds vknot,float t,int i,int k,table_fonctions b)
{
int    l,m,i1,il,im,ilm;
float  bb,bh;

b[1]=1;
i1=i+1;
bb=b[1];
if (k>1)
   {   /* ce test est inutile si l'on peut s'assurer que l'utilisateur n'utilisera jamais
          l'ordre "idiot" k=1.
          On calcule ici les fonctions pour l'ordre 2 */
   b[1]=bb*(vknot[i1]-t)/(vknot[i1]-vknot[i]);
   b[2]=bb*(t-vknot[i])/(vknot[i1]-vknot[i]);
   }
 
for (l=3;l<=k;l=l+1)
   {
   bb=b[1];
   b[1]=bb*(vknot[i1]-t)/(vknot[i1]-vknot[i-l+2]);
   for (m=2;m<=l-1;m=m+1)
      {
      im=i+m;
      ilm=i-l+m;
      bh=bb;
      bb=b[m];
      b[m]=bh*(t-vknot[ilm])/(vknot[im-1]-vknot[ilm]);
      b[m]=b[m]+bb*(vknot[im]-t)/(vknot[im]-vknot[ilm+1]);
      }
   b[l]=bb*(t-vknot[i])/(vknot[i+l-1]-vknot[i]);
   }
}
/*---------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------*/
/*                     calcul d'un point d'une courbe plane (en t)
 */
void calc2x(coor_pts_controle_c xcontr, coor_pts_controle_c ycontr, float t, float *xcal, float *ycal, vecteur_noeuds vknot, int imax, int k,table_fonctions b,int *i)
{
int j,l;

posit(vknot,t,i,k,imax);
if (*i>0)
   {
   l=*i;
   calbsp(vknot,t,l,k,b);
   *xcal=0.0;
   *ycal=0.0;
   for (j=1;j<=k;j=j+1)
      {
      *xcal=*xcal+b[j]*xcontr[*i-k+j];
      *ycal=*ycal+b[j]*ycontr[*i-k+j];
      }
   }
}
