#ifndef __BOUTEILLE_H
#define __BOUTEILLE_H

#include <stdio.h>
#include <errno.h>
#include <string.h>

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
int fileexist(FILE**srcFile, const char *filename);
void affichageBouteille(struct Bouteille bout);

#endif