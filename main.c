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
 * @return 1 : If all data have been successfully encodede into the vin struct without beeing interrupted.
 */

short encodeVin(struct Vin vin[]);

/**
 * @brief The main function where all the magic happens
 * 
 * @param argc Number of arguments passed when running the binary. (always 1 : path of the binary)
 * @param argv Array that contains the arguments passed to the running binary
 * @return int 
 */
int main(int argc, char *argv[])
{
    struct Vin vins[1000];
    int nvin;   /* nombre de vins encodés */
    struct IndVin index[1000];  /* index */
    int choice;
    int running = 1;

    while (running)
    {
        show_header();
        show_main_menu();

        printf("Choix --> ");
        scanf("%d%*c", &choice);    /* "*d" is used here in order to eat the newline from the return character. */

        if (choice == 1)
        {
            encodeVin(vins);
        }
        else if (choice == 1)
            ;
        else if (choice == 2)
            ;
        else if (choice == 3)
            ;
        else if (choice == 99)
            running = 0;
        else
        {
            printf("Choix invalide !\n");
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

    while (i < size_str &&((c = getchar()) != '\n') && c != EOF)
    {
        *str++ = c;
        i++;
    }
    *str = '\0';

    if (i == 0)
        return 0;
    else
        return 1;


}

short encodeVin(struct Vin vin[])
{
    assert(vin != NULL);

    int status = 0, color_choice, i, digit_check;
    char buffer[10];
    vin->IdVin = Id_init++;

    printf("Producteur : ");
    status = secureInput(vin->producteur, sizeof(vin->producteur));
    printf("nom de cuvee : ");
    status = secureInput(vin->NomCuvee, sizeof(vin->NomCuvee));
    printf("Appellation : ");
    status = secureInput(vin->Appellation, sizeof(vin->Appellation));
    printf("Region : ");
    status = secureInput(vin->Region, sizeof(vin->Region));
    printf("Pays : ");
    status = secureInput(vin->Pays, sizeof(vin->Pays));

    do
    {
        digit_check = 1;

        printf("Choissisez la couleur : \n\n");
        show_color_menu();
        printf("Couleur : ");
        status = secureInput(buffer, sizeof(buffer));
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
    


}