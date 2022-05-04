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


int InsertionIND(struct IndVin** index, struct Vin *vin)
{
    struct IndVin *pt = NULL, *pt_prec = NULL, *tmp = NULL;

    tmp = (struct IndVin*)malloc(sizeof(struct IndVin));
    if (tmp == NULL)
    {
        printf("Demande d'allocation memoire echoué !\n");
        return -1;
    }

    strcpy(tmp->Pays, vin->Pays);
    strcpy(tmp->Region, vin->Region);
    strcpy(tmp->Appellation, vin->Appellation);
    strcpy(tmp->Producteur, vin->producteur);
    strcpy(tmp->Annee, vin->Annee);
    tmp->IdVin = vin->IdVin;

    if (*index == NULL || strcmp(tmp->Pays, (*index)->Pays) < 0)
    {
        tmp->psvt = *index;
        *index = tmp;
    }
    else if (strcmp(tmp->Pays, (*index)->Pays) == 0 && strcmp(tmp->Region, (*index)->Region) < 0)
    {
        tmp->psvt = *index;
        *index = tmp;
    }
    else if (strcmp(tmp->Pays, (*index)->Pays) == 0 && strcmp(tmp->Region, (*index)->Region) == 0 && strcmp(tmp->Appellation, (*index)->Appellation) < 0)
    {
        tmp->psvt = *index;
        *index = tmp;
    }
    else if (strcmp(tmp->Pays, (*index)->Pays) == 0 && strcmp(tmp->Region, (*index)->Region) == 0 && strcmp(tmp->Appellation, (*index)->Appellation) == 0 && strcmp(tmp->Annee, (*index)->Annee) > 0)
    {
        tmp->psvt = *index;
        *index = tmp;
    }
    else
    {
        pt = *index;

        while (pt != NULL && strcmp(tmp->Pays, pt->Pays) >= 0)
        {
            pt_prec = pt;
            pt = pt->psvt;
        }

        while (pt != NULL && strcmp(tmp->Pays, pt->Pays) == 0 && strcmp(tmp->Region, (*index)->Region) >= 0)
        {
            pt_prec = pt;
            pt = pt->psvt;
        }

        while (pt != NULL && strcmp(tmp->Pays, pt->Pays) == 0 && strcmp(tmp->Region, (*index)->Region) == 0 && strcmp(tmp->Appellation, (*index)->Appellation) >= 0)
        {
            pt_prec = pt;
            pt = pt->psvt;
        }

        while (pt != NULL && strcmp(tmp->Pays, pt->Pays) == 0 && strcmp(tmp->Region, (*index)->Region) == 0 && strcmp(tmp->Appellation, (*index)->Appellation) == 0 && strcmp(tmp->Annee, (*index)->Annee) <= 0)
        {
            pt_prec = pt;
            pt = pt->psvt;
        }

        pt_prec->psvt = tmp;
        tmp->psvt = pt;

    }
    return 0;
}




void RechercheAppellation(struct IndVin *index, int nvin, char *Appellation)
{
    struct IndVin *pt = NULL;
    struct Vin vin;
    FILE *fp = NULL;
    char c;

    pt = index;

    if (openDatabase(&fp, "vins.dat"))
    {
        if (nvin > 0)
        {
            while (pt != NULL && strcmp(Appellation, pt->Appellation) != 0)
            {
                pt = pt->psvt;
            }
            c = '\n';
            while (pt != NULL && strcmp(Appellation, pt->Appellation) == 0 && c == '\n')
            {
                fseek(fp, sizeof(struct Vin) *(pt->IdVin-1), SEEK_SET);
                fread(&vin, sizeof(struct Vin), 1, fp);
                AfficheVin(&vin);
                pt = pt->psvt;

                printf("Appuyez sur enter pour afficher le vin suivant !\n");
                c = getchar();

            }
            fclose(fp);
        }
        else
            printf("\n\nAucun vin n'a encore ete encoder !\n\n");
    }
}

void RechercheMillesime(struct IndVin *index, int nvin, char *Millesime)
{
    struct IndVin *pt = NULL;
    struct Vin vin;
    FILE *fp = NULL;
    char c = 0;

    pt = index;

    if (openDatabase(&fp, "vins.dat"))
    {
        if (nvin > 0)
        {
            while (pt != NULL && strcmp(Millesime, pt->Annee) != 0)
            {
                pt = pt->psvt;
            }

            c = '\n';
            while (pt != NULL && strcmp(Millesime, pt->Annee) == 0 && c == '\n')
            {
                fseek(fp, sizeof(struct Vin) *(pt->IdVin-1), SEEK_SET);
                fread(&vin, sizeof(struct Vin), 1, fp);
                AfficheVin(&vin);
                pt = pt->psvt;

                printf("Appuyez sur enter pour afficher le vin suivant !\n");
                c = getchar();

            }
            fclose(fp);
        }
        else
            printf("\n\nAucun vin n'a encore ete encoder !\n\n");
    };
}

short RechercheExistant(struct IndVin *index, struct Vin vin)
{
    struct IndVin *pt = index;
    struct Vin vin_tmp;
    FILE *fp = NULL;

    fp = fopen("vins.dat", "rb");
    if (fp == NULL)
    {
        printf("Ouverture du fichier impossible !\n");
    }
    else
    {
        while (pt != NULL)
        {
            fseek(fp, sizeof(struct Vin) *(pt->IdVin-1), SEEK_SET);
            fread(&vin_tmp, sizeof(struct Vin), 1, fp);
            if (strcmp(vin.Annee,vin_tmp.Annee) == 0)
                if (strcmp(vin.producteur,vin_tmp.producteur) == 0 )
                    if (strcmp(vin.Couleur,vin_tmp.Couleur) == 0)
                        if (strcmp(vin.NomCuvee,vin_tmp.NomCuvee) == 0)
                            if (strcmp(vin.Appellation,vin_tmp.Appellation) == 0)
                                return 1;
            pt = pt->psvt;
        }
    }
    return 0;

}


short EncodeVin(struct IndVin **index, int nvin)
{

    long idExistant = 0;
    int status = 0, color_choice, date, garde_check;
    char buffer[10];
    struct Vin vin;
    FILE *fp = NULL;

    do
    {
        fp = fopen("vins.dat", "ab");
        if (fp == NULL)
        {
            printf("erreur d'ouverture !\n");
            return -1;
        }
        if (idExistant == 0)
            vin.IdVin = nvin + 1;
        printf("Producteur : ");
        status = secureInput(vin.producteur, sizeof(vin.producteur));
        if (status == 0)
            return 0;
        printf("Nom de cuvee : ");
        status = secureInput(vin.NomCuvee, sizeof(vin.NomCuvee));
        if (status == 0)
            return 0;
        printf("Appellation : ");
        status = secureInput(vin.Appellation, sizeof(vin.Appellation));
        if (status == 0)
            return 0;
        printf("Region : ");
        status = secureInput(vin.Region, sizeof(vin.Region));
        if (status == 0)
            return 0;
        printf("Pays : ");
        status = secureInput(vin.Pays, sizeof(vin.Pays));
        if (status == 0)
            return 0;

        do
        {
            printf("Choissisez la couleur : \n\n");
            show_color_menu();
            printf("Couleur : ");
            status = secureInput(buffer, sizeof(buffer));
            if (!status)
                return 0;
            
            if (verifyInt(buffer, status) == -1)
            {
                printf("\nChoix mal forme !\n");
            }
            else
            {
                sscanf(buffer, "%d", &color_choice);
                if (color_choice < 1 || color_choice > 7)
                    printf("\nChoix inexistant !\n");
            }

        } while (color_choice < 1 || color_choice > 7);

        strcpy(vin.Couleur, couleur_types[color_choice - 1]);

        do
        {
            printf("Entrez la date (a partir de 1800): ");
            status = secureInput(vin.Annee, sizeof(vin.Annee));
            if (!status)
                return 0;
            
            if (verifyInt(vin.Annee, status) == -1)
            {
                printf("\nDate mal forme !\n");
                date = 0;
            }
            else
            {
                sscanf(vin.Annee, "%d", &date);
                if (date < 1800)
                    printf("\nLa date est inferieure a 1800 !\n");
            }

        } while (date < 1800);

        do
        {
            printf("Bio ? (O/N) : ");
            status = secureInput(buffer, sizeof(buffer));
            if (status == 0)
                return 0;
        } while (*buffer != 'O' && *buffer != 'o' && *buffer != 'N' && *buffer != 'n');

        vin.Bio = tolower((int)*buffer);
        do
        {
            garde_check = 0;
            printf("Entrez la garde : ");
            status = secureInput(vin.Garde, sizeof(vin.Garde) + 1);
            if (!status)
                return 0;

            if (verifyInt(vin.Garde, status) == -1 || ((*(vin.Garde + 4) != '\0') && (strlen(vin.Garde) != 4)))
            {
                printf("\nGarde Invalide !\n");
                garde_check = -1;
            }
        } while (garde_check == -1);

        if (RechercheExistant(*index, vin))
        {
            printf("Ce vin existe déja !\n");
            idExistant = 1;
        }
        else
        {
            InsertionIND(index, &vin);
            fseek(fp, 0, SEEK_END);
            fwrite(&vin, sizeof(struct Vin), 1, fp);
            fclose(fp);
            idExistant = 0;
        }
    }while (idExistant == 1);



    return 1;
    /*
    Id : 1
Producteur : jsp
Nom de cuvee : fd
Appelation : fd
Region : coucou
Pays : 1800
Couleur : rouge tranquille
Annee : 1800
Bio : o
Garde : 29 a 83 ans
*/
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

void afficherToutVin(struct IndVin *index)
{
    struct IndVin *tmp;
    struct Vin vin;
    FILE *fp = NULL;
    char c;

    fp = fopen("vins.dat", "rb");
    if (fp == NULL)
    {
        printf("Erreur d'ouverture du fichier !\n");
    }
    else
    {
        c = '\n';
        tmp = index;
        while (tmp != NULL && c == '\n')
        {
            fseek(fp, sizeof(struct Vin)*(tmp->IdVin -1), SEEK_SET);
            fread(&vin, sizeof(struct Vin), 1, fp);
            AfficheVin(&vin);
            tmp = tmp->psvt;
            printf("Appuyez sur enter pour afficher la bouteille suivante !\n");
            c = getchar();
            
        }
        fclose(fp);
    }

}

int modifierVin(struct IndVin **index, long id)
{
    struct Vin vin;
    int status = 0;
    int color_choice = 0;
    int garde_check;
    FILE *fp = NULL;
    char tmp[100];
    int idExistant;

    supressionIND(index, id);
    do
    {
        fp = fopen("vins.dat", "rb+");
        if (fp == NULL)
        {
            printf("Ouverture du fichier impossible !\n");
            return -1;
        }
        else
        {
            fseek(fp, sizeof(struct Vin)*(id -1), SEEK_SET);
            fread(&vin, sizeof(struct Vin), 1, fp);
            fseek(fp, sizeof(struct Vin)*(id -1), SEEK_SET);

            printf("Appuyer sur enter sur le champ que vous ne souhaitez pas modifier !\n");
            
            printf("Producteur : ");
            status = secureInput(tmp, sizeof(tmp));
            if (status != 0)
                strcpy(vin.producteur, tmp);
            printf("Nom de cuvee : ");
            status = secureInput(tmp, sizeof(tmp));
            if (status != 0)
                strcpy(vin.NomCuvee, tmp);
            printf("Appellation : ");
            status = secureInput(tmp, sizeof(tmp));
            if (status != 0)
                strcpy(vin.Appellation, tmp);
            printf("Region : ");
            status = secureInput(tmp, sizeof(tmp));
            if (status != 0)
                strcpy(vin.Region, tmp);
            printf("Pays : ");
            status = secureInput(tmp, sizeof(tmp));
            if (status != 0)
                strcpy(vin.Pays, tmp);
            

            do
            {
                printf("Choissisez la couleur : \n\n");
                show_color_menu();
                printf("Couleur : ");
                status = secureInput(tmp, sizeof(tmp));
                if (status != 0)
                {
                    if (verifyInt(tmp, status) == -1)
                    {
                        printf("\nChoix mal forme !\n");
                    }
                    else
                    {
                        sscanf(tmp, "%d", &color_choice);
                        if (color_choice < 1 || color_choice > 7)
                            printf("\nChoix inexistant !\n");
                    }
                    strcpy(vin.Couleur, couleur_types[color_choice - 1]);
                }

            } while ((color_choice < 1 || color_choice > 7) && *tmp != '\0');


            do
            {
                printf("Bio ? (O/N) : ");
                status = secureInput(tmp, sizeof(tmp));
                if (status != 0)
                    vin.Bio = tolower((int)*tmp);
            } while (*tmp != 'O' && *tmp != 'o' && *tmp != 'N' && *tmp != 'n' && *tmp != '\0');

            do
            {
                garde_check = 0;
                printf("Entrez la garde : ");
                status = secureInput(tmp, sizeof(tmp) + 1);
                if (status != 0)
                {
                    if ((verifyInt(tmp, status) == -1 || ((*(tmp + 4) != '\0') && (strlen(tmp) != 4))) && *tmp != '\0')
                    {
                        printf("\nGarde Invalide !\n");
                        garde_check = -1;
                    }
                    else
                    {
                        strcpy(vin.Garde, tmp);
                        garde_check = 0;
                    }
                }
            } while (garde_check == -1 && *vin.Garde != '\0');


            if (RechercheExistant(*index, vin))
            {
                printf("Ce vin existe déja !\n");
                idExistant = 1;
                fclose(fp);
            }
            else
            {
                InsertionIND(index, &vin);
                idExistant = 0;
            }
        }
    }while (idExistant == 1);

    fwrite(&vin, sizeof(struct Vin), 1, fp);
    fclose(fp);
    return 1;
}

void supressionIND(struct IndVin **ptete, long idVin)
{
    struct IndVin *pt = NULL, *pt_prec = NULL;

    pt = *ptete;

    while (pt != NULL && pt->IdVin != idVin)
    {
        pt_prec = pt;
        pt = pt->psvt;
    }

    if (pt != NULL && pt->IdVin == idVin)
    {
        if (pt_prec == NULL)
        {
            *ptete = pt->psvt;
        }
        else
        {
            pt_prec->psvt = pt->psvt;
        }
    }
}

int read_single_wine(long id, struct Vin *vin)
{
    FILE *fp = fopen("vins.dat", "rb");
    if (fp == NULL)
    {
        printf("Ouverture du fichier impossible !\n");
    }
    else
    {
        fseek(fp, sizeof(struct Vin)*(id-1), SEEK_SET);
        fread(vin, sizeof(struct Vin), 1, fp);
        fclose(fp);
    }
    return 0;
}