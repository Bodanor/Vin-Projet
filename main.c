/**
 * @file main.c
 * @author Christos Papadopoulos (Christos.papadopoulos@student.hepl.be)
 * @brief Dossier 1
 * @version 0.1
 * @date 2022-02-17
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


const char* couleur_types[] = {
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

/**
 *
 * @brief Prints a nice Header on the terminal
 *
 */

void show_header(void);

/**
 * @brief   Function that can be used to safely write data from the stdin file.
 *
 * @param str   char pointer to a valid memory location
 * @param size_str  maximum size in bytes of the first valid parameter.
 * @return  0 : if user has interrupted the input by hitting Enter at the beginning.
 * @return  1 : if the input has successfully been written to destination memory location.
 */
short secureInput(char* str, int size_str);

/**
 * @brief   Prints the main menu with the options available.
 *
 */
void show_main_menu(void);

/**
 * @brief   Prints all the possible colors for a bottle of wine in form of a menu.
 *
 */
void show_color_menu(void);
/**
 * @brief encode a wine into a struct Vin.
 *
 * @param vin   all infos about a bottle of wine
 * @param nvin  how many wine have been encoded till now
 * @return 0    : If input has been interrupted by the user.
 * @return 1    : If all data have been successfully encodedd into the vin struct without beeing interrupted.
 */

short EncodeVin(struct Vin* vin, int nvin);


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

short AfficheVin(struct Vin* vin, int nvin, int ID);

/**
 * @brief Show all the encoded wine in the array <vin>
 *
 * @param vin   valid struct vin
 * @param index valid struct index, that contains all the encode sorted wine
 * @param nvin  how many wine have been encoded till now
 */
void show_all(struct Vin* vin, struct IndVin* index, int nvin);

/**
 * @brief Sort all the encoded wines in the array <vin> by country, region and appellation
 *
 * @param vin   valid struct vin
 * @param index valid struct index, that contains all the encode sorted wine
 * @param nvin  how many wine have been encoded till now
 */
void InsertionIND(struct Vin* vin, struct IndVin* index, int nvin);


short convertToINT(char *str, int str_length, int *to_convert);

int main(int argc, char* argv[])
{
    struct Vin vins[1000];
    int nvin;   /* nombre de vins encodés */
    struct IndVin index[1000];  /* index */
    char choice[3];
    int menu_option = 0;
    char id[3];
    int i, status;

    nvin = 0;

    do
    {
        do
        {
            show_header();
            show_main_menu();

            status = 0;
            printf("Choix --> ");
            secureInput(choice, sizeof(choice));

            i = 0;
            while (status != -1 && choice[i] != '\0')
            {
                if (choice[i] != '\0' && !isdigit(choice[i]))
                {
                    printf("\nChoix mal formé !\n");
                    status = -1;
                    i = 0;
                }
                else
                    i++;
            }
        }while (status == -1);

        if (status == -1)
            menu_option = 0;
        else
            menu_option = atoi(choice);

        if (menu_option == 1)
        {
            do
            {
                status = EncodeVin(&vins[nvin], nvin);
                if (!status)
                    printf("\n\nEncodage interrompu par l'utilisateur !\n\n");
                else
                {
                    InsertionIND(&vins[nvin], index, nvin);
                    printf("\n\t\t\t\t\t\tVin encode !\n");
                    printf("\t\t\t\t\t\tId : %ld\n", (vins + nvin)->IdVin);
                    printf("\t\t\t\t\t\tTotal vin : %d\n\n", nvin + 1);
                    nvin++;
                }
            } while (status);
        }
        else if (menu_option == 2)
        {
            show_all(vins, index, nvin);
        }
        else if (menu_option == 3)
        {
            do
            {
                status = 0;
                printf("Entrez l'ID : ");
                secureInput(id, sizeof(id));

                i = 0;
                status = 0;
                while (status != -1 && id[i] != '\0')
                {
                    if (id[i] != '\0' && !isdigit(id[i]))
                    {   
                        printf("L'ID est mal forme !\n");
                        i = 0;
                        status = -1;
                    }
                    else
                        i++;
                }

            } while (status == -1);

            i = AfficheVin(vins, nvin, atoi(id));
            if (i == -1)
                printf("\nAucun vin ne correspond a l'ID : %d\n", atoi(id));
        }
        else
        {
            if (menu_option != 99)
                printf("\nChoix invalide !\n");
        }
    }while (menu_option != 99);

    return 0;

}
/********************************************/
/*  INPUT : /                               */
/*  PROCESS : Affiche l'en-tête du menu     */
/*  OUTPUT : /                              */
/********************************************/

void show_header(void)
{
    int i;
    for (i = 0; i < 40; i++)
        putc('-', stdout);

    fputs("\n|\t", stdout);
    printf("\tDossier 1\t");

    for (i = 0; i < 7; i++)
        putc(' ', stdout);
    puts("|");

    for (i = 0; i < 40; i++)
        putc('-', stdout);

    puts("\n");

}

/********************************************/
/*  INPUT : /                               */
/*  PROCESS : Affiche les options du menu   */
/*  OUTPUT : /                              */
/********************************************/

void show_main_menu(void)
{
    printf("1) Ajouter des vins\n");
    printf("2) Afficher tout les vins\n");
    printf("3) Afficher un vin specifique\n\n");
    printf("99) Quitter\n\n");
}

/****************************************************************/
/*  INPUT : /                                                   */
/*  PROCESS : Affiche la liste des couleurs possible d'un vin   */
/*  OUTPUT : /                                                  */
/****************************************************************/

void show_color_menu(void)
{
    int i;
    for (i = 0; i < 7; i++)
    {
        printf("%d) %s\n", i + 1, couleur_types[i]);
    }
    puts("\n\n");
}
/********************************************************************/
/*  INPUT : pointeur de char :  adresse ou on veux stocker un input */
/*          entier size_str : La taille max du pointeur de char     */
/*  PROCESS : recupere un input charactere par charactere et permet */
/*            De ne pas dépasser le buffer du pointeur de char.     */
/*            Si la taille est dépassée, ce qui suite la taille     */
/*            Max du buffer sera ignoré !                           */
/*  OUTPUT : 0 si l'utilisateur à appuyer sur enter des le debut    */
/*           1 Si l'Input à bien été stocker dans le pointeur       */
/********************************************************************/
short secureInput(char* str, int size_str)
{
    int c, i = 0;

    while (((c = getchar()) != '\n') && c != EOF)
    {
        if (i < size_str-1)
            *str++ = c;
        i++;
    }
    *str = '\0';

    if (i == 0)
        return 0;
    return 1;
    /****************************************************************************/
    /*  INPUT : pointeur de structure vin                                       */
    /*          entier nvin : nombre de vin déja encoder                        */
    /*  PROCESS : Permet de renseigner les différents                           */
    /*            Champs de la structure vin                                    */
    /*  OUTPUT :  0 : Si l'utilisateur a appuyez sur ENTER pour revenir au menu */
    /*              1 : Si l'Input à bien été stocker dans le pointeur          */
    /****************************************************************************/

}

short EncodeVin(struct Vin* vin, int nvin)
{
    assert(vin != NULL);

    int status = 0, color_choice, i, digit_check, date, garde_check, garde;
    char buffer[10];
    vin->IdVin = ++nvin;
    printf("Producteur : ");
    status = secureInput(vin->producteur, sizeof(vin->producteur));
    if (status == 0)
        return 0;
    printf("nom de cuvee : ");
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
            printf("\nChoix mal formé ou inexistant!\n");

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
            printf("\nDate mal formée !\n");
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
        status = secureInput(vin->Garde, sizeof(vin->Garde));
        if (!status)
            return 0;

        if (convertToINT(vin->Garde, 4, &garde) == -1)
        {
            printf("\nGarde Invalide !\n");
            garde_check = -1;
        }
        else
        {
            if (strlen(vin->Garde) != 4)
                garde_check = -1;
        }
    } while (garde_check == -1);

    // If User didn't unterrupt the encoding, then we increment the index.
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


short AfficheVin(struct Vin* vin, int nvin, int ID)
{
    int i;

    for (i = 0; i < nvin; i++)
    {
        if ((vin + i)->IdVin == ID)
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
            printf("Garde : %s\n\n", vin->Garde);
            return 0;
        }
    }
    return -1;
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
    while (i >= 0 && strcmp((((index + i)->Pays)), vin->Pays) > 0)
    {
        strcpy(((index + i + 1)->Pays), ((index + i)->Pays));
        strcpy(((index + i + 1)->Annee), ((index + i)->Annee));
        strcpy(((index + i + 1)->Producteur), ((index + i)->Producteur));
        strcpy(((index + i + 1)->Appellation), ((index + i)->Appellation));
        strcpy(((index + i + 1)->Region), ((index + i)->Region));

        ((index + i + 1)->IdVin) = ((index + i)->IdVin);
        i--;
    }
    while (i >= 0 && strcmp((((index + i)->Region)), vin->Region) > 0)
    {
        strcpy(((index + i + 1)->Region), ((index + i)->Region));
        strcpy(((index + i + 1)->Pays), ((index + i)->Pays));
        strcpy(((index + i + 1)->Annee), ((index + i)->Annee));
        strcpy(((index + i + 1)->Producteur), ((index + i)->Producteur));
        strcpy(((index + i + 1)->Appellation), ((index + i)->Appellation));
        ((index + i + 1)->IdVin) = ((index + i)->IdVin);
        i--;
    }
    while (i >= 0 && strcmp((((index + i)->Appellation)), vin->Appellation) > 0)
    {
        strcpy(((index + i + 1)->Appellation), ((index + i)->Appellation));
        strcpy(((index + i + 1)->Pays), ((index + i)->Pays));
        strcpy(((index + i + 1)->Annee), ((index + i)->Annee));
        strcpy(((index + i + 1)->Producteur), ((index + i)->Producteur));
        ((index + i + 1)->IdVin) = ((index + i)->IdVin);
        i--;
    }


    ((index + i + 1)->IdVin) = vin->IdVin;
    strcpy(((index + i + 1)->Annee), (vin->Annee));
    strcpy(((index + i + 1)->Producteur), (vin->producteur));
    strcpy(((index + i + 1)->Appellation), (vin->Appellation));
    strcpy(((index + i + 1)->Region), (vin->Region));
    strcpy(((index + i + 1)->Pays), (vin->Pays));
}

/****************************************************************************/
/*  INPUT : pointeur de structure vin                                       */
/*          pointeur de structure index                                     */
/*          entier nvin : nombre de vin déja encoder                        */
/*  PROCESS : Permet d'afficher à l'ecran tout les vins déja encoder de     */
/*              manière triée                                               */
/*  OUTPUT : /                                                              */
/****************************************************************************/


void show_all(struct Vin* vin, struct IndVin* index, int nvin)
{
    assert(vin != NULL && index != NULL);
    int i;

    if (nvin != 0)
    {
        for (i = 0; i < nvin; i++)
        {
            if ((index + i)->IdVin != 0)
            {
                printf("\nID : %ld\n", ((vin + ((index + i)->IdVin - 1))->IdVin));
                printf("Producteur : %s\n", ((vin + ((index + i)->IdVin - 1))->producteur));
                printf("Nom de cuvee : %s\n", ((vin + ((index + i)->IdVin - 1))->NomCuvee));
                printf("Appellation : %s\n", ((vin + ((index + i)->IdVin - 1))->Appellation));
                printf("Region : %s\n", ((vin + ((index + i)->IdVin - 1))->Region));
                printf("Pays : %s\n", ((vin + ((index + i)->IdVin - 1))->Pays));
                printf("Couleur : %s\n", ((vin + ((index + i)->IdVin - 1))->Couleur));
                printf("Annee : %s\n", ((vin + ((index + i)->IdVin - 1))->Annee));
                printf("Bio : %c\n", ((vin + ((index + i)->IdVin - 1))->Bio));
                printf("Garde : %s\n\n", ((vin + ((index + i)->IdVin - 1))->Garde));
            }
        }
        printf("\n\n");
    }
    else
        printf("\n\nAucun vin n'a encore ete encode !\n\n");
}

short convertToINT(char *str, int str_length, int *to_convert)
{
    int i;
    for (i = 0; i < str_length ; i++)
    {
        if (!isdigit(*(str + i)))
            return -1;
    }
    *to_convert = atoi(str);
    return 0;
}