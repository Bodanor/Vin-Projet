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
#include "bouteille.h"

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
void show_main_menu(int nvin);


void show_menu_bouteille(void);
void show_menu_vin(void);


int main(int argc, char* argv[])
{

    /* Variable pour le vin */
    struct Vin vins[2];
    int nvin;   /* nombre de vins encodés */
    struct IndVin index[1000];  /* index */
    char choice[3], appellation[40], millesime[5], id[3];
    int i, status, menu_option = 0, c;

    nvin = 0;
    /* Fin Variable des vins */

    /* Variable pour les bouteilles */
    struct Bouteille bout;
    FILE *fbouteilles= NULL;
    int nbouteilles = 0;
     /* Fin Variable des bouteilles */
    
    do
    {
        do
        {
            show_header();
            show_main_menu(nvin);
            
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

        menu_option = atoi(choice);

        switch(menu_option)
        {
            case 1:
                do
                {
                    do
                    {
                        show_header();
                        show_menu_vin();
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

                    menu_option = atoi(choice);
                
                    switch(menu_option)
                    {
                        case 1:
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
                                
                                break;
                        
                        case 2:
                            i = 0;
                            c = '\n';
                            if (nvin > 0)
                            {
                                while(i < nvin && c == '\n')
                                {
                                    AfficheVin((vins+((index+i)->IdVin -1)));
                                    if (i + 1 != nvin && nvin >= 2)
                                    {
                                        printf("Appuyez sur enter pour afficher le vin suivant !\n");
                                        c = getchar();
                                    }
                                    
                                    i++;
                                }
                            }
                            else
                                printf("\n\nAucun vin n'a encore ete encoder !\n\n");

                            break;
                        
                        case 3:
                            if (nvin > 0)
                            {
                                printf("Entrez l'appellation a rechercher : ");
                                secureInput(appellation, sizeof(appellation));
                                RechercheAppellation(vins, index, nvin, appellation);
                            }
                            else
                                printf("\n\nAucun vin n'a encore ete encoder !\n\n");
                            break;



                        case 4:
                            if (nvin > 0)
                            {
                                printf("Entrez le millesime a rechercher : ");
                                secureInput(millesime, sizeof(millesime));
                                RechercheMillesime(vins, index, nvin, millesime);
                            }
                            else
                                printf("\n\nAucun vin n'a encore ete encoder !\n\n");
                            break;
                        
                        
                        default:
                            if (menu_option != 99)
                                printf("\nChoix invalide !\n");
                        
                    }
                }while(menu_option != 99);

                menu_option = 0;
                break;

            case 2:
            if (nvin > 0)
            {
                do
                {
                    do
                    {
                        show_header();
                        show_menu_bouteille();
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
                    menu_option = atoi(choice);

                    switch (menu_option)
                    {
                        
                        case 1:

                            while (nvin < 1000 && (status = EncodeBouteille(&bout, nbouteilles, vins, nvin)) == 1)
                            {
                                nbouteilles++;
                            }
                            if (nvin == 1000)
                            {
                                printf("\n\nLa taille maximum du tableau bouteille a ete atteinte !\n\n");
                            }
                            else if (status == 0)
                                printf("\n\nEncodage interrompu par l'utilisateur !\n\n");
                            
                            break;
                        case 2:
                            i = 0;
                            c = '\n';

                            if (nbouteilles > 0)
                            {
                                if (openDatabase(&fbouteilles) != -1)
                                {
                                    rewind(fbouteilles);
                                    while (i < nbouteilles && (lireBouteille(&bout, fbouteilles) != -1) && c == '\n')
                                    {
                                        affichageBouteille(&bout);
                                        if (i + 1 != nbouteilles && nbouteilles >= 2)
                                        {
                                            printf("Appuyez sur enter pour afficher la bouteille suivante !\n");
                                            c = getchar();
                                        }
                                        i++;
                                    }
                                    fclose(fbouteilles);

                                }
                                return -1;
                               
                            }
                            else
                                printf("\n\nAucune bouteille n'a encore ete encoder !\n\n");

                            break;
                        
                    }

                }while(menu_option != 99);
                menu_option = 0;
                break;
            }
            default:
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

void show_menu_vin(void)
{
    printf("1) Ajouter des vins\n");
    printf("2) Afficher tout les vins\n");
    printf("3) Rechercher par Appellation\n");
    printf("4) Rechercher par Millesime\n\n");
    printf("99) Revenir au menu precedent\n\n");
}

void show_menu_bouteille(void)
{
    printf("1) Ajout d'une nouvelle bouteille (en fin de fichier)\n");
    printf("2) Affichage du fichier bouteilles(avec arret premature si souhaite)\n");
    printf("3) Recherche de la fiche d'une bouteille (dont on donne l'emplacement)\n");
    printf("4) Consommation d'une bouteille\n\n");
    printf("99) Revenir au menu precedent\n\n");

}

void show_main_menu(int nvin)
{
    printf("1) Vins\n");
    if (nvin > 0)
        printf("2) Bouteilles\n\n");
    printf("99) Quitter\n\n");
}
