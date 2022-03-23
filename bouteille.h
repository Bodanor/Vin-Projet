#ifndef __BOUTEILLE_H
#define __BOUTEILLE_H

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "vin.h"

#define FILENAME "FileBouteilles.dat"

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

int openDatabase(FILE**srcFile);
void affichageBouteille(struct Bouteille *bout);
short ecrireBouteille(struct Bouteille *bout, FILE *srcFile);
short lireBouteille(struct Bouteille *bout, FILE *srcFile);
short EncodeBouteille(struct Bouteille *bout, int nbouteille, struct Vin *vins, int nvin);
int RechercheBoutempl(char *recherchern, int nbouteilles);

#endif
