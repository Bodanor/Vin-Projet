#include <stdio.h>

const char *couleur_types[] = {
    "rouge tranquille",
    "blanc tranquille",
    "rose tranquille",
    "blanc effervescent",
    "rose effervescent",
    "rouge liquoreux",
    "blanc liquoreux"
};

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
};


int main(int argc, char *argv[])
{

}
