#ifndef __BOUTEILLE_H
#define __BOUTEILLE_H

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#include "vin.h"
#include "utils.h"

#define FILENAMEBOUTEILLE "bouteilles.dat"

struct date
{
    short jour;
    short mois;
    short annee;
};

struct Bouteille
{
    long IdBouteille;
    struct date DateAchat;
    int PrixAchat;
    int Contenance;
    int VolumeAlcool;
    char Emplacement[7];
    long IdFournisseur;
    long IdVin;
    struct date DateConso;
    char NoteConso [50];
    
};

void affichageBouteille(struct Bouteille *bout);
short ecrireBouteille(struct Bouteille *bout, FILE *srcFile);
short lireBouteille(struct Bouteille *bout, FILE *srcFile);
short EncodeBouteille(struct Bouteille *bout, int nbouteille, struct Vin *vins, int nvin);
long RechercheBoutempl(char *recherchern, int nbouteilles);
long RechercheBoutId(long Id_recherche, int nbouteilles);
int consommerBouteille(struct Bouteille *bout);


#endif
