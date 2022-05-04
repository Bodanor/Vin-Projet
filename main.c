/**
 * @file main.c
 * @author Christos Papadopoulos (Christos.papadopoulos@student.hepl.be)
 * @brief Dossier 4
 * @version 0.1
 * @date 2022-02-17
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdio.h>


#include "utils.h"
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
/* fonction pour menu sur emplacement ou idbouteille*/
void show_consommation_menu(void);
/*  */



int main(int argc, char* argv[])
{

    /* Variable pour le vin */
    struct Vin vin;
    int nvin;   /* nombre de vins encodés */
    struct IndVin *index = NULL;
    FILE *fvins = NULL;
    char choice[3], appellation[40], millesime[5], idVin[10];
    int i, status, menu_option = 0, c, id;
    
    nvin = 0;
    /* Fin Variable des vins */

    /* Variable pour les bouteilles */
    FILE *fbouteilles = NULL;
    struct Bouteille bout;
    int nbouteilles = 0;
    long bout_bytes;
    char emplacement[7];
    char Identifiant_bouteille[10];
    long Id_bout;
     /* Fin Variable des bouteilles */
    

    fvins = fopen("vins.dat", "rb");
    if (fvins == NULL)
    {
        printf("Ouverture du fichier vins.dat impossible !\nVous traivaillez en mode local\n");
    }
    else
    {
        printf("Chargement des vins en cours ...\n");
        while (fread(&vin, sizeof(struct Vin), 1, fvins))
        {
            InsertionIND(&index, &vin);
            nvin++;
        }
        printf("Nombre de vins charge : %d\n\n" ,nvin);
        fclose(fvins);
    }

    fbouteilles = fopen("bouteilles.dat", "rb");
    if (fbouteilles == NULL)
    {
         printf("Ouverture du fichier bouteilles.dat impossible !\nVous traivaillez en mode local\n");
    }
    else
    {
        printf("Chargement des bouteilles en cours ...\n");
        while (fread(&bout, sizeof(struct Bouteille), 1, fbouteilles))
        {
            nbouteilles++;
        }
        printf("Nombre de bouteilles charge : %d\n\n" ,nbouteilles);
        fclose(fbouteilles);
    }
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
                                while (nvin < 1000 && EncodeVin(&index, nvin))
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
                                afficherToutVin(index);
                            }
                            else
                                printf("\n\nAucun vin n'a encore ete encoder !\n\n");

                            break;
                        
                        case 3:
                            if (nvin > 0)
                            {
                                printf("Entrez l'appellation a rechercher : ");
                                secureInput(appellation, sizeof(appellation));
                                RechercheAppellation(index, nvin, appellation);
                            }
                            else
                                printf("\n\nAucun vin n'a encore ete encoder !\n\n");
                            break;



                        case 4:
                            if (nvin > 0)
                            {
                                printf("Entrez le millesime a rechercher : ");
                                secureInput(millesime, sizeof(millesime));
                                RechercheMillesime(index, nvin, millesime);
                            }
                            else
                                printf("\n\nAucun vin n'a encore ete encoder !\n\n");
                            break;
                        
                        case 5:
                            if (nvin > 0)
                            {
                                do
                                {
                                    status = 0;
                                    printf("Entrez l'id du vin a modifier : ");
                                    status = secureInput(idVin, sizeof(idVin));
                                    if (status == 0)
                                    {
                                        printf("Id mal forme !\n");
                                        status = -1;
                                    }
                                    i = 0;
                                    while (status != -1 && idVin[i] != '\0')
                                    {
                                        if (idVin[i] != '\0' && !isdigit(idVin[i]))
                                        {
                                            printf("Id mal forme !\n");
                                            status = -1;
                                            i = 0;
                                        }
                                        else
                                            i++;
                                    }
                                    id = atoi(idVin);
                                    if (id > nvin)
                                    {
                                        printf("L'ID n'existe pas !\n");
                                        status = -1;
                                    }
                                }while (status == -1);

                                modifierVin(&index, id);
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

                            while (nvin < 1000 && (status = EncodeBouteille(nbouteilles, &vin, nvin)) == 1)
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
                                if (openDatabase(&fbouteilles, FILENAMEBOUTEILLE) != -1)
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
                                else
                                    return -1;
                               
                            }
                            else
                                printf("\n\nAucune bouteille n'a encore ete encoder !\n\n");

                            break;
                        
                        case 3:

                            if (nbouteilles > 0)
                            {
                                do 
                                {
                                    printf("Entrez l'emplacement a de la bouteille a rechercher : ");
                                    status = secureInput(emplacement, sizeof(emplacement));

                                } while (status == 0);

                                if (openDatabase(&fbouteilles, FILENAMEBOUTEILLE) != -1)
                                {
                                    rewind(fbouteilles);
                                    bout_bytes = RechercheBoutempl(emplacement, nbouteilles);
                                    if (bout_bytes != 0)
                                    {
                                        fseek(fbouteilles, bout_bytes-sizeof(struct Bouteille), SEEK_SET);
                                        lireBouteille(&bout, fbouteilles);
                                        affichageBouteille(&bout);
                                    }

                                    else
                                        printf("\n\nAucune bouteille n'a ete trouver avec comme emplacement \"%s\" !\n\n", emplacement);

                                }
                                else
                                    return -1;
                            }
                            else
                                printf("\n\nAucune bouteilles n'a encore ete encode !\n\n");
                            
                            break;
                        
                        case 4:
                            if (nbouteilles > 0)
                            {
                                do
                                {
                                    do
                                    {
                                        show_header();
                                        show_consommation_menu();
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
                                            do
                                            {
                                                do
                                                {
                                                    printf("Entrez l'Identifiant de la bouteille : ");
                                                    status = secureInput(Identifiant_bouteille, sizeof(Identifiant_bouteille));
                                                }while (status == 0);

                                                if (verifyInt(Identifiant_bouteille, status) == -1)
                                                {
                                                    printf("Identifiant mal forme !\n");
                                                    Id_bout = -1;
                                                }
                                                else
                                                {
                                                    sscanf(Identifiant_bouteille, "%ld", &Id_bout);
                                                    if (Id_bout <= 0)
                                                        printf("\nIdentifiant Invalide !\n\n");

                                                }
                                            }while (Id_bout <= 0);


                                            if (openDatabase(&fbouteilles,  FILENAMEBOUTEILLE) != -1)
                                            {
                                                bout_bytes = RechercheBoutId(Id_bout, nbouteilles);
                                                if (bout_bytes != 0)
                                                {
                                                    fseek(fbouteilles, bout_bytes-sizeof(struct Bouteille), SEEK_SET);
                                                    lireBouteille(&bout, fbouteilles);
                                                    consommerBouteille(&bout);
                                                    fseek(fbouteilles, bout_bytes-sizeof(struct Bouteille), SEEK_SET);
                                                    ecrireBouteille(&bout, fbouteilles);
                                                }
                                                else
                                                    printf("\n\nAucune bouteille n'a ete trouver avec comme Id \"%ld\" !\n\n", Id_bout);
                                                
                                                fclose(fbouteilles);
                                            }
                                            break;

                                        case 2:
                                            do
                                            {
                                                printf("Entrez l'emplacement de la bouteille : ");
                                                status = secureInput(emplacement, sizeof(emplacement));
                                            }while (status == 0);

                                            if (openDatabase(&fbouteilles,  FILENAMEBOUTEILLE) != -1)
                                            {
                                                status =fseek(fbouteilles, 0, SEEK_SET);
                                                
                                                bout_bytes = RechercheBoutempl(emplacement, nbouteilles);
                                                if (bout_bytes != 0)
                                                {
                                                    fseek(fbouteilles, bout_bytes-sizeof(struct Bouteille), SEEK_SET);
                                                    lireBouteille(&bout, fbouteilles);
                                                    consommerBouteille(&bout);
                                                    fseek(fbouteilles, bout_bytes-sizeof(struct Bouteille), SEEK_SET);
                                                    ecrireBouteille(&bout, fbouteilles);

                                                }

                                                else
                                                    printf("\n\nAucune bouteille n'a ete trouver avec comme emplacement \"%s\" !\n\n", emplacement);
                                                fclose(fbouteilles);

                                            }

                                            break;
                                        
                                    }
                                }while (menu_option != 99);
                            }
                            else
                                printf("\nAucune bouteille n'a encore ete encode !\n\n");

                            menu_option = 0;
                            break;
                        
                        default:
                            if (menu_option != 99)
                                printf("\nChoix invalide !\n");
                            
                        
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
    printf("\tProjet Vin\t");

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
    printf("4) Rechercher par Millesime\n");
    printf("5) Modifier un vin\n\n");
    printf("99) Revenir au menu precedent\n\n");
}

void show_menu_bouteille(void)
{
    printf("1) Ajout d'une nouvelle bouteille\n");
    printf("2) Affichage du fichier bouteilles\n");
    printf("3) Recherche de la fiche d'une bouteille\n");
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

void show_consommation_menu(void)
{
    printf("1) Rechercher par Identifiant.\n");
    printf("2) Rechercher par emplacement.\n\n");
    printf("99) Revenir en arriere.\n\n");
}
