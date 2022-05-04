#include "utils.h"


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

    return i;
    /****************************************************************************/
    /*  INPUT : pointeur de structure vin                                       */
    /*          entier nvin : nombre de vin déja encoder                        */
    /*  PROCESS : Permet de renseigner les différents                           */
    /*            Champs de la structure vin                                    */
    /*  OUTPUT :  0 : Si l'utilisateur a appuyez sur ENTER pour revenir au menu */
    /*              1 : Si l'Input à bien été stocker dans le pointeur          */
    /****************************************************************************/

}

short verifyInt(char *str, int str_length)
{
    int i;
    for (i = 0; i < str_length ; i++)
    {
        if ( *(str + i) != '\0' && !isdigit(*(str + i)))
            return -1;
    }
    return 0;
}

int openDatabase(FILE**srcFile, char *filename)
{
    *srcFile = fopen(filename, "rb+"); // SI il existe pas return NULL, sinon c'est que le fichier existe
    if (*srcFile == NULL)
    {
        *srcFile = fopen(filename, "w+b");  // W+B force la creation du fichier.
        if (*srcFile == NULL)
        {
            printf("\nOuverture du fichier \"%s\" impossible\n%s\n\n", filename, strerror(errno));  
            return -1;
        }
    }
    return 1;

}

int verifyDate(char *buffer)
{
    char *pt = buffer;
    int i;
    for (i = 0; i < 2; i++)
    {
        if (isdigit(*pt) != 0)
        {
            pt++;
        }
        else
            return -1;
    }
    if (*pt++ == '/')
    {
        for (i = 0; i < 2; i++)
        {
            if (isdigit(*pt) != 0)
                pt++;
            else
                return -1;
        }

        if (*pt++ == '/')
        {
            for (i = 0; i < 4 ; i++)
            {
                if (isdigit(*pt) != 0)
                    pt++;
                else
                    return -1;
            }
            if (*pt != '\0')
                return -1;
            else
                return 0;
        }
        else
            return -1;
    }
    else    
        return -1;
}