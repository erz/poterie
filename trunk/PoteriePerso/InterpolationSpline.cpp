#include "stdafx.h"
#include "InterpolationSpline.h"
#include <math.h>

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
int    l,m,i1,im,ilm;
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


/******************************************************************************/
/* SOUS PROGRAMME DE CALCULS DE LA NORME DES VECTEURS DES SOUS MATRICES       */
/******************************************************************************/ 

void normrs(matrice a, int n, int l, int k, int nmax, int *k1, float *e1)
{
    /* System generated locals */
    int a_dim1, i__1, i__2;
    float r__1;

    /* Local variables */
    static float e;
    static int i, j;
    static float e0;

    /* Parameter adjustments */
    a_dim1 = nmax;

    /* Function Body */
    *e1 = (float)0.;
    i__1 = n;
    for (j = k; j <= i__1; ++j) 
    {
	e = (float)0.;
	i__2 = l;
	for (i = k; i <= i__2; ++i) 
        {
            /* Computing 2nd power */
	    r__1 = a[i + j * a_dim1];
	    e += r__1 * r__1;
	}
	e0 = sqrt(e);
	if (*e1 <= e0) 
        {
	    *e1 = e0;
	    *k1 = j;
	}
    }
    return ;
} /* normrs */

/******************************************************************************/
/* SOUS PROGRAMME DE RESOLUTION D'UN SYSTEME TRIANGULAIRE SUPERIEURE          */
/******************************************************************************/

void resors(matrice a, int ns, int nc, int nmax)
{
    /* System generated locals */
    int a_dim1, i__1, i__2, i__3;

    /* Local variables */
    static int i, j, l, m, i1, ncj;

    /* Parameter adjustments */
    a_dim1 = nmax;

    /* Function Body */
    i__1 = ns;
    for (j = 1; j <= i__1; ++j) 
    {
	ncj = nc + j;
	a[nc + ncj * a_dim1] /= a[nc + nc * a_dim1];
	i__2 = nc;
	for (l = 2; l <= i__2; ++l) 
        {
	    i1 = nc + 1 - l;
	    m = i1 + 1;
	    i__3 = nc;
	    for (i = m; i <= i__3; ++i) 
            {
		a[i1 + ncj * a_dim1] -= a[i1 + i * a_dim1] * a[i + ncj * 
			a_dim1];
	    }
	    a[i1 + ncj * a_dim1] /= a[i1 + i1 * a_dim1];
	}
    }
    return ;
} /* resors */



/******************************************************************************/
/* HOUSRS:RESOLUTION D'UN SYSTEME LINEAIRE CARRE OU RECTANGULAIRE PAR LA      */
/*        METHODE DE HOUSEHOLDER.                                             */
/*        SI IR=0 LA RESOLUTION EST IMPOSSIBLE NC>NL                          */
/*        SINON IR REPRESENTE LE EPS-RANG DE LA MATRICE                       */
/*        SI IR=NC ALORS LA RESOLUTION EST NORMALE                            */
/*                 SINON LES COLONNES LES +LINEAIREMENT DEPENDANTES SONT      */
/*                       DONNEES PAR JF(IR+1) A JF(NC).                       */
/*                                                                            */
/*        A  :MATRICE( NL LIGNES,NC+NS COLONNES)                              */
/*        NL : NBRE DE LIGNES                                                 */
/*        NC : NBRE DE COLONNES                                               */
/*        NS : NBRE DE SECONDS MEMBRES                                        */
/*       NMAX :NBRE DE LIGNES DU DIMENSIONNEMENT DE A DANS LE PROGRAMME PPAL  */
/*       EPS  : PRECISION POUR LA DETERMINATION DU RANG NUM. DE LA MATRICE A  */
/*        IR   :INDICATEUR                                                    */
/*        JF   :VECTEUR DE TRAVAIL DE LONGUEUR NC                             */
/*        GA,BA,ETA  SONT DES VARIABLES AUX.(CF ALGORITHME HOUSEHOLDER)       */
/*        APPELS AUX SOUS-PROGRAMMES NORMRS ET RESORS.                        */
/******************************************************************************/

void housrs(matrice a, int nmax, int nl, int nc, int ns, float eps, int *ir, table_travail_int jf)
{
    /* System generated locals */
    int a_dim1, i__1, i__2;
    float r__1;

    /* Local variables */
    static float boolean, d;
    static int i, j, k, l, m;
    static float e1;
    static int k1, m1;
    static float ba, ga, ar, pp;
    static int nc1, kp1, ir1;
    static float eta;
    static int ind, jnc, ntc;
    static float aux;


    /* Parameter adjustments */
    a_dim1 = nmax;

    /* Function Body */
    ntc = nc + ns;
    i__1 = nc;
    for (i = 1; i <= i__1; ++i) 
    {
	jf[i] = i;
    }
    i__1 = nl ; 

/* TEST SI NBRE DE COL >NBRE DE LIGNES                                        */
    if (nc > nl) 
    {
	*ir = 0;
	return ;
    }
    else 
    {
	boolean = (float)0.;
	k = 1;
L20:
	if (k <= nc && boolean == (float)0.) 
        {
	    normrs(a, nc, nl, k, nmax, &k1, &e1);
/* PERMUTATIONS DE COLONNES (LA + GRANDE NORME DEVIENT LE PREMIER VECTEUR     */
/* DE LA SOUS MATRICE DE TRAVAIL.                                             */
	    aux = (float) jf[k];
	    jf[k] = jf[k1];
	    jf[k1] = (int)aux;
	    if (e1 > eps) 
            {
		i__1 = nl;
		for (i = 1; i <= i__1; ++i) 
                {
		    d = a[i + k * a_dim1];
		    a[i + k * a_dim1] = a[i + k1 * a_dim1];
		    a[i + k1 * a_dim1] = d;
		}
		if (a[k + k * a_dim1] == (float)0.) 
                {
		    ar = -e1;
		} 
                else 
                {
		    ar = -e1 * (a[k + k * a_dim1] / (r__1 = a[k + 
			    k * a_dim1], abs(r__1)));
		}
/*                         CALCUL DE ETA                                      */
		eta = ar * (ar - a[k + k * a_dim1]);
/*                         CALCUL DES BETA ET DELTA                           */
		kp1 = k + 1;
		i__1 = ntc;
		for (j = kp1; j <= i__1; ++j) 
                {
		    ba = (float)0.;
		    i__2 = nl;
		    for (i = k; i <= i__2; ++i) 
                    {
			if (i <= k) 
                        {
			    ga = a[k + k * a_dim1] - ar;
			} 
                        else 
                        {
			    ga = a[i + k * a_dim1];
			}
			ba += ga * a[i + j * a_dim1];
		    }
		    i__2 = nl;
		    for (i = k; i <= i__2; ++i) 
                    {
			if (i <= k) 
                        {
			    ga = a[k + k * a_dim1] - ar;
			} 
                        else 
                        {
			    ga = a[i + k * a_dim1];
			}
			a[i + j * a_dim1] -= ga * ba / eta;
		    }
		}
		a[k + k * a_dim1] = ar;
		i__1 = nl;
		for (i = kp1; i <= i__1; ++i) 
                {
		    a[i + k * a_dim1] = (float)0.;
		}
	    } 
            else 
            {
		*ir = k - 1;
		boolean = (float)1.;
	    }
	    ++k;
	    goto L20;
	}
	if (boolean == (float)0.)
        {
	    *ir = nc;
	}

/* SI LA MATRICE EST DE RANG MAX. ALORS RESOLUTION DU SYSTEME                 */
/*                                SINON SORTIE                                */

	if (*ir < nc) 
        {
	    ir1 = *ir + 1;
	    return ;
	} 
        else 
        {
	    if (ns > 0) 
            {

/*                  RESOLUTION DU SYSTEME APRES TRIANGULARISATION             */

		resors(a, ns, nc, nmax);

/*                  REMISE EN ORDRE DES SOLUTIONS                             */

		nc1 = nc - 1;
		i__1 = nc1;
		for (m = 1; m <= i__1; ++m) 
                {
		    pp = (float) jf[m];
		    ind = m;
		    m1 = m + 1;
		    i__2 = nc;
		    for (l = m1; l <= i__2; ++l) 
                    {
			if (pp > (float) jf[l]) 
                        {
			    pp = (float) jf[l];
			    ind = l;
			}
		    }
		    aux = (float) jf[ind];
		    jf[ind] = jf[m];
		    jf[m] = (int)aux;
		    i__2 = ns;
		    for (j = 1; j <= i__2; ++j) 
                    {
			jnc = j + nc;
			aux = a[ind + jnc * a_dim1];
			a[ind + jnc * a_dim1] = a[m + jnc * a_dim1];
			a[m + jnc * a_dim1] = aux;
		    }
		}
	    }
	}
    }
    return ;
} /* housrs */



/******************************************************************************/
/* LI2COC:  LISSAGE COURBE 2D AVEC CONTRAINTE D'EXTREMITE                     */
/*         DETERMINATION DES POINTS DE CONTROLE DU POLYGONE CARACTERISTIQUE   */
/*         ASSOCIE A LA B-SPLINE PASSANT A TRAVERS UN NUAGE DE POINTS DONNE   */
/*         DU PLAN (AU SENS DES MOINDRES CARRES) (POINTS DISTINCTS)           */
/*         MAIS EN IMPOSANT LE PASSAGE PAR LES POINTS EXTREMES                */
/*        CE PROGRAMME TRAITE AUSSI LE CAS PARTICULIER DE L'INTERPOLATION(M=N)*/
/*                                                                            */
/*       X       : VECTEURS DES COORDONNEES DES POINTS A LISSER               */
/*       Y       :                        (BI=0,BS>=N)                        */
/*       N       : (N+1) POINTS A LISSER                                      */
/*       M       : (M+1) POINTS DE CONTROLE DE LA B-SPLINE SOLUTION           */
/*                 SI M=N IL S'AGIT D'UN PROBLEME D'INTERPOLATION             */
/*                 SINON  K-1<=M<=N                                           */
/*       K       : ORDRE DE LA B-SPLINE DE LISSAGE                            */
/*       ZETA    : VECTEUR DES PARAMETRES (BI=0,BS>=N)                        */
/*       BNIK    : MATRICE DES NIK                                            */
/*                    INDICE DE LIGNES    (BI=1,BS>=N-1)                      */
/*                    INDICE DE COLONNES  (BI=1,BS>=M+1)                      */
/*      NMAX     :NOMBRE DE LIGNES MAXIMUM DE LA MATRICE BNIK(DIMENSIONNEMENT)*/
/*       B       : VECTEUR DE TRAVAIL     (BI=1,BS>=K)                        */
/*       JF      :        "               (BI=1,BS>=N-1) (ENTIERS)            */
/*       XCONTR  : VECTEURS RESULTATS :COORDONNEES DES POINTS DE CONTROLE     */
/*       YCONTR  :                        (BI=0,BS>=M)                        */
/*       VKNOT   : VECTEUR DE NOEUDS      (BI=0,BS>M+K)                       */
/*  CHOIX_NOEUDS : CHOIX DU VECTEUR DE NOEUDS 1 (UNIFORME), 2 (DE BOOR)       */
/*       IMAX    : INDICE DU DERNIER ELEMENT DE VKNOT (=M+K)                  */
/*       IR      : INDICATEUR DE BON DEROULEMENT DU CALCUL                    */
/*                     =-2 M  EST INCOMPATBLE AVEC N ET K (CF CI-DESSUS)      */
/*                     =-1 LE SYSTEME N'EST PAS DE RANG MAXIMUM, LES RESULTATS*/
/*                         N'ONT PAS ETE CONSERVES                            */
/*                     >0  CONDITION NECESSAIRE MAIS NON SUFFISANTE POUR QUE  */
/*                         LES RESULTATS SOIENT VALIDES. LE SYSTEME EST DE    */
/*                         RANG MAXIMUM, IR=M-1                               */
/*      CONDI   : CONDITIONNEMENT DU SYSTEME RESOLU POUR TROUVER LA SOLUTION  */
/*                IL EST IMPORTANT DE CONTROLER QUE CETTE VALEUR NE DEVIENT   */
/*                PAS TROP GRANDE. IL S'AGIT D'UNE VALEUR APPROXIMATIVE DU    */
/*                CONDITIONNEMENT (PAR VALEUR INFERIEURE). POUR OBTENIR LE    */
/*                VRAI CONDITIONNEMENT, MULTIPLIER CETTE VALEUR PAR UN        */
/*                FACTEUR COMPRIS ENTRE 2 ET 4 ENVIRON                        */
/*      EMOY    : ERREURS QUADRATIQUE MOYENNE ET SUPERIEURE CALCULEES AUX     */
/*                POINTS DONNES.                                              */
/*      ESUP      INFORMATION INSUFFISANTE POUR GARANTIR LA VALIDITE DE       */
/*                LA SOLUTION N'EST A PRENDRE EN COMPTE QUE SI LE             */
/*                CONDITIONNEMENT N'EST PAS TROP GRAND                        */
/******************************************************************************/

void li2coc(coor_pts x, coor_pts y, int n, int m, int k, vecteur_parametres zeta, 
			matrice bnik, int nmax, table_fonctions b, table_travail_int jf, 
			coor_pts_controle_c xcontr, coor_pts_controle_c ycontr, vecteur_noeuds vknot,
            int *imax, int *ir, float *condi, float *emoy, float *esup)
{
    /* System generated locals */
    int bnik_dim1, i__1, i__2;
    float r__1, r__2;


    /* Local variables */
    static float ecou;
    static int i, j;
    static int nc, ii, li, ip, nl, ns;
    static float xx, yy;
    static float eps;


    /* Parameter adjustments */
    bnik_dim1 = nmax;

    /* Function Body */

/*                       CONTROLE DE LA VALIDITE DE M                         */
    if (m > n || m + 1 < k) 
    {
	*ir = -2;
	return ;
    }

/*                    INITIALISATION DE LA MATRICE BNIK                       */
    i__1 = n - 1;
    for (i = 1; i <= i__1; ++i) 
    {
	i__2 = m - 1;
	for (j = 1; j <= i__2; ++j) 
        {
	    bnik[i + j * bnik_dim1] = (float)0.;
	}

/*                              SECOND MEMBRE                                 */
	bnik[i + m * bnik_dim1] = x[i];
	bnik[i + (m + 1) * bnik_dim1] = y[i];
    }

/*                    DETERMINATION DE LA MATRICE DES NIK(ZETA(I))            */
/*                    LA PREMIERE EQUATION EST XCONTR(0)=X(0) IDEM POUR Y     */
/*                    LA DERNIERE    "         XCONTR(M)=X(N)    "            */
/*                    ON IMPOSE CES VALEURS                                   */
/*                                                                            */
/*                    L'ELIMINATION DES INCONNUES SE FAIT EN MEME TEMPS       */
/*                    LE TRAITEMENT EST PARTICULIER DANS LE CAS DE LA COURBE  */
/*                    DE BEZIER                                               */

    if (m + 1 == k) 
    {
	i__1 = n - 1;
	for (li = 1; li <= i__1; ++li) 
        {
	    posit(vknot, zeta[li], &ip, k, *imax);
	    calbsp(vknot, zeta[li], ip, k, b);
	    i__2 = k - 1;
	    for (j = 2; j <= i__2; ++j) 
            {
		bnik[li + (ip + j - k) * bnik_dim1] = b[j];
	    }
	    bnik[li + m * bnik_dim1] = bnik[li + m * bnik_dim1] - x[0] * 
                                       b[1] - x[n] * b[k];
	    bnik[li + (m + 1) * bnik_dim1] = bnik[li + (m + 1) * bnik_dim1] 
		                             - y[0] * b[1] - y[n] * b[k];
	}

/*                               CAS GENERAL                                  */
    } 
    else 
   {
	i__1 = n - 1;
	for (li = 1; li <= i__1; ++li) 
        {
	    posit(vknot, zeta[li], &ip, k, *imax);
	    calbsp(vknot, zeta[li], ip, k, b);

/*      SUIVANT IP LES POINTS ET INCONNUES EXTREMES ONT DE L'INFLUENCE        */
/*      CHOIX SELON IP                                                        */

/*                   CALCUL SUR LE PREMIER INTERVALLE: IP=K-1                 */
	    if (ip == k - 1) 
            {
		i__2 = k;
		for (j = 2; j <= i__2; ++j) 
                {
		    bnik[li + (ip + j - k) * bnik_dim1] = b[j];
		}
		bnik[li + m * bnik_dim1] -= x[0] * b[1];
		bnik[li + (m + 1) * bnik_dim1] -= y[0] * b[1];
		goto L59;
	    }

/*                   CALCUL SUR LE DERNIER INTERVALLE: IP=M                   */
	    if (ip == m) 
            {
		i__2 = k - 1;
		for (j = 1; j <= i__2; ++j)
                {
		    bnik[li + (ip + j - k) * bnik_dim1] = b[j];
		}
		bnik[li + m * bnik_dim1] -= x[n] * b[k];
		bnik[li + (m + 1) * bnik_dim1] -= y[n] * b[k];
		goto L59;
	    }

/*                   AUTRES INTERVALLES: OTHERWISE                            */
	    i__2 = k;
	    for (j = 1; j <= i__2; ++j) 
            {
		bnik[li + (ip + j - k) * bnik_dim1] = b[j];
	    }

L59:
	    ;
	}
    }

/*             RESOLUTION DU SYSTEME PAR LA METHODE DE HOUSEHOLDER            */
    nl = n - 1;
    nc = m - 1;
    ns = 2;
    eps = (float)1e-5;
    housrs(bnik, nmax, nl, nc, ns, eps, ir, jf);

/*             LE CONDITIONNEMENT EST MIS A O SI LE SYSTEME N'EST PAS         */
/*             DE RANG MAXIMUM                                                */
    *condi = (float)0.;

/*               LES RESULTATS SONT LES POINTS DU POLYGONE CARACTERISTIQUE    */
/*               CORRESPONDANT A LA B-SPLINE DE LISSAGE                       */
/*               ILS SONT CONSERVES SI LE SYSTEME EST DE RANG MAXIMUM         */
/*               LES POITS EXTREMES SONT VALORISES                            */
    if (*ir == nc) 
    {
	*condi = (r__1 = bnik[bnik_dim1 + 1], abs(r__1)) / (r__2 = bnik[nc + 
		nc * bnik_dim1], abs(r__2));
	xcontr[0] = x[0];
	ycontr[0] = y[0];
	i__1 = m - 1;
	for (i = 1; i <= i__1; ++i) 
        {
	    xcontr[i] = bnik[i + m * bnik_dim1];
	    ycontr[i] = bnik[i + (m + 1) * bnik_dim1];
	}
	xcontr[m] = x[n];
	ycontr[m] = y[n];

/*                    CALCUL DES ERREURS                                      */
	*emoy = (float)0.;
	*esup = (float)0.;
	i__1 = n;
	for (i = 0; i <= i__1; ++i) 
        {
	    calc2x(xcontr, ycontr, zeta[i], &xx, &yy, vknot, *imax, k, b, &ii);
	    /* Computing 2nd power */
	    r__1 = xx - x[i];
	    /* Computing 2nd power */
	    r__2 = yy - y[i];
	    ecou = r__1 * r__1 + r__2 * r__2;
	    *emoy += ecou;
	    ecou = sqrt(ecou);
	    if (ecou > *esup) 
            {
		*esup = ecou;
	    }
	}
	*emoy = sqrt(*emoy / (n + 1));
    } 
    else 
    {
        printf("Probleme dans la resolution du systeme d'equation \n");
        printf("Systeme de rang non maximum \n");
	*ir = -1;
    }
} /* li2coc */

