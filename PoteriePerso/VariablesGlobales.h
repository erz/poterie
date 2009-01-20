/*
	Variables globales utilisées dans le programme.
*/

#include "PoterieSequence.h"

//Sequence d'images chargée
extern CPoterieSequence *seq;

//Echelle permettant la correspondance echelle/cm
extern double echelle;

//Fichier d'enregistrement des données
extern FILE *fichierSortie;

//Données dépendantes de la forme de la poterie
extern float volumeMatiere;
extern float epaisseurMoyenne;
extern float pourcentageBas;
extern float pourcentageMilieu;
extern float pourcentageHaut;