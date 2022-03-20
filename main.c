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


#include "util_vin.h"
#include "vin.h"

/**
 *
 * @brief Prints a nice Header on the terminal
 *
 */

void show_header(void);


/**
 * @brief   Prints the main menu with the options available.
 *
 */
void show_main_menu(void);






int main(int argc, char* argv[])
{
    struct Vin vins[2];
    int nvin;   /* nombre de vins encodés */
    struct IndVin index[1000];  /* index */
    char choice[3], appellation[40], millesime[5], id[3];
    int i, status, menu_option = 0;

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
                    printf("\nChoix mal forme !\n");
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

            while (nvin < 1000 && EncodeVin(vins, index, &vins[nvin], nvin))
            {
                nvin++;
            }
            if (nvin == 1000)
            {
                printf("\n\nLa taille maximum du tableau vin a ete atteinte !\n\n");
            }
            else
                printf("\n\nEncodage interrompu par l'utilisateur !\n\n");
        }
        else if (menu_option == 2)
        {
            int i = 0;
            char c = '\0';
            if (nvin > 0)
            {
                printf("Appuyez sur enter pour afficher le vin suivant !\n");
                while(i < nvin && c == '\0')
                {
                    AfficheVin((vins+((index+i)->IdVin -1)));
                    secureInput(choice, sizeof(choice));
                    c = *choice;    // Essaye de contourner ca.
                    i++;
                }
            }
            else
                printf("\n\nAucun vin n'a encore ete encoder !\n\n");


        }
        else if (menu_option == 3)
        {
            if (nvin > 0)
            {
                printf("Entrez l'appellation a rechercher : ");
                secureInput(appellation, sizeof(appellation));
                RechercheAppellation(vins, index, nvin, appellation);
            }
            else
                printf("\n\nAucun vin n'a encore ete encoder !\n\n");
        }
        else if (menu_option == 4)
        {
            if (nvin > 0)
            {
                printf("Entrez le millesime a rechercher : ");
                secureInput(millesime, sizeof(millesime));
                RechercheMillesime(vins, index, nvin, millesime);
            }
            else
                printf("\n\nAucun vin n'a encore ete encoder !\n\n");
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
    printf("\tDossier 3\t");

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
    printf("3) Rechercher par Appellation\n");
    printf("4) Rechercher par Millesime\n\n");
    printf("99) Quitter\n\n");
}

