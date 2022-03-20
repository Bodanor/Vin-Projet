#include "vin.h"

const char* couleur_types[] = {
    "rouge tranquille",
    "blanc tranquille",
    "rose tranquille",
    "blanc effervescent",
    "rose effervescent",
    "rouge liquoreux",
    "blanc liquoreux"
};


/****************************************************************/
/*  INPUT : /                                                   */
/*  PROCESS : Affiche la liste des couleurs possible d'un vin   */
/*  OUTPUT : /                                                  */
/****************************************************************/

static void show_color_menu(void)
{
    int i;
    for (i = 0; i < 7; i++)
    {
        printf("%d) %s\n", i + 1, couleur_types[i]);
    }
    puts("\n\n");
}


/********************************************************************************/
/*  INPUT : pointeur de structure vin                                           */
/*          pointeur de structure index                                         */
/*          entier nvin : nombre de vin déja encoder                            */
/*  PROCESS : Permet d'inserer un element de type struct IndVin de manière trié */
/*  OUTPUT : /                                                                  */
/********************************************************************************/


void InsertionIND(struct Vin* vin, struct IndVin* index, int nvin)
{
    int i;
    i = nvin - 1;
    while (i >= 0 && strcmp((index + i)->Pays, vin->Pays) > 0)
    {
        *(index + i + 1) = *(index + i);
        i--;
    }
    while (i >= 0 && strcmp((index + i)->Pays, vin->Pays) == 0 && strcmp((index + i)->Region, vin->Region) > 0)
    {
        *(index + i + 1) = *(index + i);
        i--;
    }
    while (i >= 0 && strcmp((index + i)->Pays, vin->Pays) == 0 && strcmp((index + i)->Region, vin->Region) == 0 && strcmp((index + i)->Appellation, vin->Appellation) > 0)
    {
       *(index + i + 1) = *(index + i);
        i--;
    }
    while (i >= 0 && strcmp((index + i)->Appellation, vin->Appellation) == 0 && strcmp((index + i)->Pays, vin->Pays) == 0 && strcmp((index + i)->Region, vin->Region) == 0 && strcmp((index + i)->Annee, vin->Annee) < 0)
    {
        *(index + i + 1) = *(index + i);
        i--;
    }


    (index + i + 1)->IdVin = vin->IdVin;
    strcpy((index + i + 1)->Annee, (vin->Annee));
    strcpy((index + i + 1)->Producteur, (vin->producteur));
    strcpy((index + i + 1)->Appellation, (vin->Appellation));
    strcpy((index + i + 1)->Region, (vin->Region));
    strcpy((index + i + 1)->Pays, (vin->Pays));
}




void RechercheAppellation(struct Vin *vin, struct IndVin *index, int nvin, char *Appellation)
{
    int i = 0;
    while (i < nvin)
    {
        if (strcmp((index+i)->Appellation, Appellation) == 0)
        {
            AfficheVin(vin + ((index + i)->IdVin-1));
        }
        i++;
    }
}

void RechercheMillesime(struct Vin *vin, struct IndVin *index, int nvin, char *Millesime)
{
    int i = 0;
    while (i < nvin)
    {
        if (strcmp((index+i)->Annee, Millesime) == 0)
        {
            AfficheVin(vin + ((index + i)->IdVin-1));
        }
        i++;
    }
}

long RechercheExistant(struct Vin *vin, struct IndVin *index, int nvin, struct Vin *vinrecherche)
{
    int i;

    long found = 0;
    for (i = 0;i < nvin; i++)
    {
        if (strcmp((vin+((index + i)->IdVin-1))->Annee, vinrecherche->Annee) == 0)
        {
            if (strcmp((vin+((index + i)->IdVin-1))->producteur, vinrecherche->producteur) == 0)
                if (strcmp((vin+((index + i)->IdVin-1))->Couleur, vinrecherche->Couleur) == 0)
                    if (strcmp((vin+((index + i)->IdVin-1))->NomCuvee, vinrecherche->NomCuvee) == 0)
                        if (strcmp((vin+((index + i)->IdVin-1))->Appellation, vinrecherche->Appellation) == 0)
                            found = (vin+((index + i)->IdVin-1))->IdVin;
        }
    }

    return found;


}


short EncodeVin(struct Vin *vins, struct IndVin *index, struct Vin* vin, int nvin)
{

    long idExistant;
    int status = 0, color_choice, date, garde_check, garde;
    char buffer[10];
    vin->IdVin = nvin + 1;
    printf("Producteur : ");
    status = secureInput(vin->producteur, sizeof(vin->producteur));
    if (status == 0)
        return 0;
    printf("Nom de cuvee : ");
    status = secureInput(vin->NomCuvee, sizeof(vin->NomCuvee));
    if (status == 0)
        return 0;
    printf("Appellation : ");
    status = secureInput(vin->Appellation, sizeof(vin->Appellation));
    if (status == 0)
        return 0;
    printf("Region : ");
    status = secureInput(vin->Region, sizeof(vin->Region));
    if (status == 0);
    printf("Pays : ");
    status = secureInput(vin->Pays, sizeof(vin->Pays));
    if (status == 0);

    do
    {
        printf("Choissisez la couleur : \n\n");
        show_color_menu();
        printf("Couleur : ");
        status = secureInput(buffer, sizeof(buffer));
        if (!status)
            return 0;
        if (convertToINT(buffer, 1, &color_choice) == -1 || (color_choice < 1 || color_choice > 7))
            printf("\nChoix mal forme ou inexistant!\n");

    } while (color_choice < 1 || color_choice > 7);

    strcpy(vin->Couleur, couleur_types[color_choice - 1]);

    do
    {
        printf("Entrez la date (a partir de 1800): ");
        status = secureInput(vin->Annee, sizeof(vin->Annee));
        if (!status)
            return 0;
        if (convertToINT(vin->Annee, 4, &date) == -1  || date < 1800)
        {
            printf("\nDate mal formee !\n");
            date = 0;
        }

    } while (date < 1800);

    do
    {
        printf("Bio ? (O/N) : ");
        status = secureInput(buffer, sizeof(buffer));
        if (status == 0)
            return 0;
    } while (*buffer != 'O' && *buffer != 'o' && *buffer != 'N' && *buffer != 'n');

    vin->Bio = tolower((int)*buffer);
    do
    {
        garde_check = 0;
        printf("Entrez la garde : ");
        status = secureInput(vin->Garde, sizeof(vin->Garde) + 1);
        if (!status)
            return 0;

        if (convertToINT(vin->Garde, 4, &garde) == -1 || ((*(vin->Garde + 4) != '\0') && (strlen(vin->Garde) != 4)))
        {
            printf("\nGarde Invalide !\n");
            garde_check = -1;
        }
    } while (garde_check == -1);
    
    if ((idExistant = RechercheExistant(vins, index, nvin, vin)))
        {
            printf("\n\nCe vin est deja encoder avec comme ID : %ld!\n\n", idExistant);
            return 0;
        }
    else
    {
        InsertionIND(&vins[nvin], index, nvin);
        printf("\n\t\t\t\t\t\tVin encode !\n");
        printf("\t\t\t\t\t\tId : %ld\n", (vins + nvin)->IdVin);
        printf("\t\t\t\t\t\tTotal vin : %d\n\n", nvin + 1);
    }

    return 1;

}

/****************************************************************************/
/*  INPUT : pointeur de structure vin                                       */
/*          entier nvin : nombre de vin déja encoder                        */
/*          entier ID : l'ID du vin qui doit être afficher                  */
/*  PROCESS : Permet de chercher si l'ID d'un vin existe dans la structure  */
/*            de vin et d'afficher les differents champs de ce dernier      */
/*  OUTPUT :  0 : Si l'ID à été trouver                                     */
/*           -1 : Si l'ID n'a pas été trouver                               */
/****************************************************************************/


void AfficheVin(struct Vin* vin)
{
    printf("\nId : %ld\n", vin->IdVin);
    printf("Producteur : %s\n", vin->producteur);
    printf("Nom de cuvee : %s\n", vin->NomCuvee);
    printf("Appelation : %s\n", vin->Appellation);
    printf("Region : %s\n", vin->Region);
    printf("Pays : %s\n", vin->Pays);
    printf("Couleur : %s\n", vin->Couleur);
    printf("Annee : %s\n", vin->Annee);
    printf("Bio : %c\n", vin->Bio);
    printf("Garde : %.2s a %s ans\n\n", vin->Garde, vin->Garde + 2);
}
