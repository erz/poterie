/*
	Variables globales utilis�es dans le programme.
*/

#include "PoterieSequence.h"

//Sequence d'images charg�e
extern CPoterieSequence *seq;

//Echelle permettant la correspondance echelle/cm
extern double echelle;

//Fichier d'enregistrement des donn�es
extern FILE *fichierSortie;

//Donn�es d�pendantes de la forme de la poterie
extern float volumeMatiere;
extern float epaisseurMoyenne;
extern float pourcentageBas;
extern float pourcentageMilieu;
extern float pourcentageHaut;