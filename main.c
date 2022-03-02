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

int Id_init = 1;

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

/**
 * 
 * @fn void show_header(void)
 * @brief Prints a nice Header on the terminal
 * 
 */

void show_header(void);

/**
 * @brief Function that can be used to safely write data from the stdin file.
 * 
 * @param str char pointer to a valid memory location
 * @param size_str maximum size in bytes of the first valid parameter. 
 * @return 0 : if user has interrupted the input by hitting Enter at the beginning.
 * @return 1 : if the input has successfully been written to destination memory location. 
 */
short secureInput(char *str, int size_str);

/**
 * @brief Prints the main menu with the options available.
 * 
 */
void show_main_menu(void);

/**
 * @brief Prints all the possible colors for a bottle of wine in form of a menu.
 * 
 */
void show_color_menu(void);
/**
 * @brief encode a wine into a struct Vin.
 * 
 * @param vin all infos about a bottle of wine
 * @return 0 : If input has been interrupted by the user.
 * @return 1 : If all data have been successfully encodedd into the vin struct without beeing interrupted.
 */

short EncodeVin(struct Vin *vin);

/**
 * @brief The main function where all the magic happens
 * 
 * @param argc Number of arguments passed when running the binary. (always 1 : path of the binary)
 * @param argv Array that contains the arguments passed to the running binary
 * @return int 
 */

/**
 * @brief print all the fiels of the struct Vin to the screen
 * 
 * @param vin valid struct vin
 */


void AfficheVin(struct Vin *vin, struct IndVin *index);


void show_all(struct Vin *vin, struct IndVin *index, int struct_size);

void InsertionID(struct Vin *vin, struct IndVin *index, int nv_vin);

int main(int argc, char *argv[])
{
    struct Vin vins[1000];
    int nvin;   /* nombre de vins encodés */
    struct IndVin index[1000];  /* index */
    char choice[3];
    int running = 1;
    int menu_option = 0;
    char id[3];
    int i, status;

    nvin = 0;

    while (running)
    {
        show_header();
        show_main_menu();

        printf("Choix --> ");
        secureInput(choice, sizeof(choice));

        for (i = 0; i < sizeof(choice)-1; i++)
        {
            if(choice[i] != '\0' && !isdigit(choice[i]))
                status = -1;
        }
        if (status == -1)
            menu_option = 0;
        else
            menu_option = atoi(choice);

        if (menu_option == 1)
        {
            do
            {
                status = EncodeVin(&vins[Id_init-1]);
                if (!status)
                    printf("\n\nEncodage interrompu par l'utilisateur !\n\n");
                else
                {
                    InsertionID(&vins[Id_init-1], index, nvin);
                    Id_init++;
                    nvin++;
                    printf("\nVin encode !\n\n");
                }
            }while (status);
        }
        else if (menu_option == 2)
        {
            show_all(vins, index, nvin);
        }
        else if (menu_option == 3)
        {
            printf("Entrez l'ID : ");
            secureInput(id, sizeof(id));
            
            for (i = 0; i < 1000; i++)
            {
                if (vins[i].IdVin == atoi(id))
                {
                    AfficheVin(&vins[i], &index[i]);
                }
            }
        }
        else if (menu_option == 99)
            running = 0;
        else
        {
            printf("\nChoix invalide !\n");
        }
    }

    return 0;

}

void show_header(void)
{
    int i;
    for (i = 0; i < 40 ;i++)
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

void show_main_menu(void)
{
    printf("1) Ajouter des vins\n");
    printf("2) Afficher tout les vins\n");
    printf("3) Afficher un vin spécifique\n\n");
    printf("99) Quitter\n\n"); 
}

void show_color_menu(void)
{
    int i;
    for (i = 0; i < 7; i++)
    {
        printf("%d) %s\n", i + 1, couleur_types[i]);
    }
    puts("\n\n");
}

short secureInput(char *str, int size_str)
{
    int c, i = 0;

    while (((c = getchar()) != '\n') && c != EOF)
    {
        if (i < size_str)
            *str++ = c;
        i++;
    }
    *str = '\0';

    if (i == 0)
        return 0;
    else
        return 1;


}

short EncodeVin(struct Vin *vin)
{
    assert(vin != NULL);

    int status = 0, color_choice, i, digit_check, date, c;
    char buffer[10];
    vin->IdVin = Id_init;

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
        digit_check = 1;

        printf("Choissisez la couleur : \n\n");
        show_color_menu();
        printf("Couleur : ");
        status = secureInput(buffer, sizeof(buffer));
        if (status == 0)
            return 0;
        for (i = 0; i < 1; i++)
        {
            if (!isdigit(buffer[i]))
                digit_check = 0;
        }

         color_choice = atoi(buffer);

        if (digit_check == 0 || (color_choice < 1 || color_choice > 7))
            printf("\nChoix Invalide !\n");

    }while(digit_check == 0 || (color_choice < 1 || color_choice > 7));
    strcpy(vin->Couleur, couleur_types[color_choice-1]);

    do
    {
        digit_check = 1;

        printf("Entrez la date (à partir de 1800): ");
        status = secureInput(vin->Annee, sizeof(vin->Annee));
        if (status == 0)
            return 0;

        for (i = 0; i < 4; i++)
        {
            if (!isdigit(vin->Annee[i]))
            digit_check = 0;
        }

       date = atoi(vin->Annee);
        if (digit_check == 0 || date < 1800)
            printf("\nDate Invalide !\n");

    }while (digit_check == 0 || date < 1800);
    
    do
    {
        printf("Bio ? (O/N) : ");
        status = secureInput(buffer, sizeof(buffer));
        if (status == 0)
            return 0;
        
        if (*buffer == 'o' || *buffer == 'O')
            vin->Bio = 'T';
        else if (*buffer == 'n' || *buffer == 'N')
            vin->Bio = 'F';
        
        if (buffer[1] != '\0')
            c = '\0';

    } while (*buffer != 'O' && *buffer != 'o' && *buffer != 'N' && *buffer != 'n');

    do
    {
        digit_check = 1;

        printf("Entrez la garde : ");
        status = secureInput(vin->Garde, sizeof(vin->Garde));
        if (!status)
            return 0;
        for (i = 0; i < sizeof(vin->Garde)-1; i++)
        {
            if (!isdigit(vin->Garde[i]))
                digit_check = 0;

        }
        if (!digit_check || strlen(vin->Garde) != 4)
        {
            printf("\nGarde Invalide !\n");
            digit_check = 0;
        }
    }while (digit_check == 0);

    // If User didn't unterrupt the encoding, then we increment the index.
    return 1;
    
}

void AfficheVin(struct Vin *vin, struct IndVin *index)
{
    printf("\n\nId : %ld\t",vin->IdVin);
    printf("Producteur : %s\t", vin->producteur);
    printf("Nom de cuvee : %s\t", vin->NomCuvee);
    printf("Appelation : %s\t", vin->Appellation);
    printf("Region : %s\t", vin->Region);
    printf("Pays : %s\t", vin->Pays);
    printf("Couleur : %s\t", vin->Couleur);
    printf("Annee : %s\t", vin->Annee);
    printf("Bio : %c\t", vin->Bio);
    printf("Garde : %s\n\n", vin->Garde);
}

void InsertionID(struct Vin *vin, struct IndVin *index, int nb_vin)
{
    int i;
    i = nb_vin-1;
    while(i>=0 && strcmp((((index+i)->Pays)),vin->Pays)>0)
    {
        strcpy(((index+i+1)->Pays),((index+i)->Pays));
        strcpy(((index+i+1)->Annee),((index+i)->Annee));
        strcpy(((index+i+1)->Producteur),((index+i)->Producteur));
        strcpy (((index+i+1)->Appellation),((index+i)->Appellation));
        strcpy (((index+i+1)->Region),((index+i)->Region));

        ((index+i+1)->IdVin) = ((index+i)->IdVin);
        i--;
    }
        while(i>=0&& strcmp((((index+i)->Region)),vin->Region)>0)
    {
        strcpy(((index+i+1)->Region),((index+i)->Region));
        strcpy(((index+i+1)->Pays),((index+i)->Pays));
        strcpy(((index+i+1)->Annee),((index+i)->Annee));
        strcpy(((index+i+1)->Producteur),((index+i)->Producteur));
        strcpy (((index+i+1)->Appellation),((index+i)->Appellation));
        ((index+i+1)->IdVin) = ((index+i)->IdVin);
        i--;
    }
        while(i>=0&& strcmp((((index+i)->Appellation)),vin->Appellation)>0)
    {
        strcpy(((index+i+1)->Appellation),((index+i)->Appellation));
        strcpy(((index+i+1)->Pays),((index+i)->Pays));
        strcpy(((index+i+1)->Annee),((index+i)->Annee));
        strcpy(((index+i+1)->Producteur),((index+i)->Producteur));
        ((index+i+1)->IdVin) = ((index+i)->IdVin);
        i--;
    }


    ((index+i+1)->IdVin) = vin->IdVin;
    strcpy(((index+i+1)->Annee),(vin->Annee));
    strcpy(((index+i+1)->Producteur),(vin->producteur));
    strcpy (((index+i+1)->Appellation),(vin->Appellation));
    strcpy (((index+i+1)->Region),(vin->Region));
    strcpy (((index+i+1)->Pays),(vin->Pays));
}

void show_all(struct Vin *vin, struct IndVin *index, int nb_vin)
{
    assert(vin != NULL && index != NULL);
    int i;

    if (nb_vin != 0)
    {
        for (i = 0; i < nb_vin; i++)
        {
            if ((index+i)->IdVin != 0)
            {
                printf("\n\nId : %ld\t",((vin+((index+i)->IdVin -1))->IdVin));
                printf("Producteur : %s\t", ((vin+((index+i)->IdVin -1))->producteur));
                printf("Nom de cuvee : %s\t", ((vin+((index+i)->IdVin -1))->NomCuvee));
                printf("Appelation : %s\t", ((vin+((index+i)->IdVin -1))->Appellation));
                printf("Region : %s\t", ((vin+((index+i)->IdVin -1))->Region));
                printf("Pays : %s\t", ((vin+((index+i)->IdVin -1))->Pays));
                printf("Couleur : %s\t", ((vin+((index+i)->IdVin -1))->Couleur));
                printf("Annee : %s\t", ((vin+((index+i)->IdVin -1))->Annee));
                printf("Bio : %c\t", ((vin+((index+i)->IdVin -1))->Bio));
                printf("Garde : %s\n\n", ((vin+((index+i)->IdVin -1))->Garde));
            }
        }
    }
    else
        printf("\nAucun vin n'a encore été encodé !\n");
}