#include "util_vin.h"


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