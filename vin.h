#ifndef __VIN_H
#define __VIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"


struct Vin
{
    long IdVin;
    char producteur[50];
    char NomCuvee[50];
    char Appellation[40];
    char Region[25];
    char Pays[50];
    char Couleur[20];
    char Annee[5];
    char Bio;
    char Garde[5];
};

struct IndVin
{
    char Pays[50];
    char Region[25];
    char Appellation[40];
    char Producteur[50];
    char Annee[5];
    long IdVin;
    struct IndVin *psvt;
};

/**
 * @brief encode a wine into a struct Vin.
 *
 * @param vin   all infos about a bottle of wine
 * @param nvin  how many wine have been encoded till now
 * @return 0    : If input has been interrupted by the user.
 * @return 1    : If all data have been successfully encodedd into the vin struct without beeing interrupted.
 */

short EncodeVin(struct IndVin **index, int nvin);
/**
 * @brief print all the fields of a given ID if it exists in the array of struct to the screen.
 *
 * @param vin   valid struct vin
 * @param nvin  how many wine have been encoded till now
 * @param ID    ID to look for in the array <vin>
 *
 * @return 0: if the ID has been found in the array <vin>
 * @return -1: If the ID doesn't exist. So the wine has not yet been created.
 */

void AfficheVin(struct Vin* vin);
/**
 * @brief Sort all the encoded wines in the array <vin> by country, region and appellation
 *
 * @param vin   valid struct vin
 * @param index valid struct index, that contains all the encode sorted wine
 * @param nvin  how many wine have been encoded till now
 */
int InsertionIND(struct IndVin** index, struct Vin *vin);

void RechercheAppellation(struct IndVin *index, int nvin, char *Appellation);
void RechercheMillesime(struct IndVin *index, int nvin, char *Millesime);
short RechercheExistant(struct IndVin *index, struct Vin vin);
void afficherToutVin(struct IndVin *index);
int modifierVin(struct IndVin **index, long id);
void supressionIND(struct IndVin **ptete, long idVin);

#endif