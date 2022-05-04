#ifndef __FOURNISSEURS_
#define __FOURNISSEURS_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"


struct fournisseur
{
    long idFournisseur;
    char nom[50];
    char rue[50];
    char numero[8];
    char codePostal[10];
    char localite[50];
    char pays[33];
    struct fournisseur *psvt;
};

int InsertionINDFournisseurs(struct fournisseur** index, struct fournisseur four);
void RechercheAppellationFournisseurs(struct fournisseur *index, int nfournisseur, char *nom);
void afficherToutFournisseurs(struct fournisseur *index);
int modifierFournisseurs(struct fournisseur **index, char nom);
void supressionINDFournisseurs(struct fournisseur **ptete, long idfournisseur);
int ajouterFournisseurs(struct fournisseur **index, int nfournisseur);
#endif