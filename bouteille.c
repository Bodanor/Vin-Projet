#include "bouteille.h"

 
static short compareDate(struct date *date1, struct date *date2)//date2 plus grand que date 1 == 0 sinon -1
{
    int diffa=0,diffm=0,diffj=0,a=0;
    diffa=(date2->annee)-(date1->annee);
    diffm=(date2->mois)-(date1->mois);
    diffj=(date2->jour)-(date1->jour);

    if(diffa<0)   
        a=-1;
    else if(diffa ==0 && diffm ==0 && diffj ==0)
        a=0;
     else if(diffa ==0 && diffm <0)
         a=-1;
      else if(diffa ==0 && diffm ==0 && diffj < 0)
          a=-1;
      else
          a=1;

    return a;
}

double convertoToFloat(int input, int decimals)
{
    char buffer[10];
    char convert[10];
    char *pt_convert = convert;
    char *pt_buffer = buffer;
    long size_of_buffer;
    int i;
    double final_convert;

    sprintf(buffer, "%d", input);
    size_of_buffer = strlen(buffer);
    for (i = 0; i < size_of_buffer - decimals; i++)
        *pt_convert++ = *pt_buffer++;

    *pt_convert++ = '.';

    for (i = 0; i < decimals ;i++)
        *pt_convert++ = *pt_buffer++;
    
    *pt_convert = '\0';

    sscanf(convert, "%lf", &final_convert);
    return final_convert;
}
int verifyEmplacement(char *input)
{
    int i;
    char *pt = input;
    for (i = 0; i < 4; i++)
    {
        if (*pt != 'i' && *pt != 'I' && *pt != 'v' && *pt != 'V' && *pt != 'x' && *pt != 'X')
            return -1;
        pt++;

    }
    if (isalpha(*pt++) == 0)
        return -1;
    if (isdigit(*pt++) == 0)
        return -1;
    return 0;
}
void affichageBouteille(struct Bouteille *bout)
{
    printf("\nId Bouteille : %ld\n", bout->IdBouteille);
    if (bout->DateAchat.annee != 0)
    {
        printf("Date achat : %hd/%hd/%hd\n",bout->DateAchat.jour, bout->DateAchat.mois, bout->DateAchat.annee);
        printf("Prix achat : %2.lf €\n",convertoToFloat(bout->PrixAchat, 2));
    }
    printf("Contenance : %1.lf cl\n",convertoToFloat(bout->Contenance, 1));
    printf("Volume d'alcool : %1.lf%%\n", convertoToFloat(bout->VolumeAlcool, 1));
    if (*bout->Emplacement != '\0')
        printf("Emplacement : %s\n", bout->Emplacement);
    printf("Id du Fournisseur : %ld\n", bout->IdFournisseur);
    printf("Id du Vin : %ld\n", bout->IdVin);
    if (bout->DateConso.annee != 0)
        printf("Date conso : %hd/%hd/%hd\n",bout->DateConso.jour, bout->DateConso.mois, bout->DateConso.annee);
    if (*bout->NoteConso != '\0')
        printf("NoteConso : %s\n\n", bout->NoteConso);
}

short ecrireBouteille(struct Bouteille *bout, FILE *srcFile)
{
    if (fwrite(bout,sizeof(struct Bouteille),1, srcFile) != 1)
    {
        printf("Erreur lors de l'ecriture de la bouteille.\n%s\n", strerror(errno));
        return -1;
    }
    return 1;
    

}
short lireBouteille (struct Bouteille *bout, FILE *srcFile)
{
    if (fread(bout,sizeof(struct Bouteille),1, srcFile) != 1)
    {
        printf("Erreur lors de la lecture de la bouteille.\n%s\n", strerror(errno));
        return -1;
    }
    return 1;
}
short EncodeBouteille(int nbouteille, struct Vin *vins, int nvin)
{
    int status = 0, date_verif = 0;
    char buffer[10], emplacement[7];
    FILE *srcFile;
    struct Bouteille bout;
    struct Vin vin;
    bout.IdBouteille = nbouteille + 1;
    int annee_tmp;
    char dateBuffer[100];

    do
    {
        printf("Entrez l'ID du vin : ");
        status = secureInput(buffer, sizeof(buffer));
        if (status == 0)
            return 0;
        if (verifyInt(buffer,status) == -1)
        {
            printf("\nID du vin mal forme !\n");
            bout.IdVin = -1;
        }
        else
        {
            sscanf(buffer, "%ld", &bout.IdVin);
            if (bout.IdVin < 1 || bout.IdVin > nvin)
            {
                printf("\nID n'existe pas !\n");
                bout.IdVin = -1;
            }
        }

    }while ( bout.IdVin == -1);
    
    do
    {
        printf("Entrez la date d'achat : ");
        status = secureInput(dateBuffer, sizeof(dateBuffer));
        date_verif = verifyDate(dateBuffer);
        if (status == 0)
           return 0;
        else if (date_verif == -1)
            printf("La date est mal forme !\n");
        else
        {
            sscanf(dateBuffer, "%hd/%hd/%hd", &bout.DateAchat.jour, &bout.DateAchat.mois, &bout.DateAchat.annee);
            read_single_wine(bout.IdVin, &vin);
            annee_tmp = atoi(vin.Annee);
            
            if(bout.DateAchat.annee < annee_tmp)
            {
                printf("La date d'achat est inferieure a l'annee du vin !\n");
                date_verif = -1;
            }
        }



    }while (date_verif == -1);

    do
    {
        printf("Entrez le prix d'achat : ");
        status = secureInput(buffer, sizeof(buffer));
        if (status == 0)
            return 0;
        if (verifyInt(buffer, status) == -1)
        {
            printf("\nPrix d'achat mal forme !\n");
            bout.PrixAchat = -1;
        }
        else
        {
            sscanf(buffer, "%d", &bout.PrixAchat);
            if (bout.PrixAchat <= -1)
             printf("\nPrix d'achat invalide !\n");
        }

    }while (bout.PrixAchat <= -1);

    do
    {
        printf("Entrez la contenance : ");
        status = secureInput(buffer, sizeof(buffer));
        if (status == 0)
            return 0;
        if (verifyInt(buffer, status) == -1)
        {
            printf("\nContenance mal forme !\n");
            bout.Contenance = -1;
        }
        else
        {
            sscanf(buffer, "%d", &bout.Contenance);
            if (bout.Contenance <= 0)
                printf("\nContenance invalide !\n");
        }

    }while (bout.Contenance <= 0);


    do
    {
        printf("Entrez le volume d'alcool : ");
        status = secureInput(buffer, sizeof(buffer));
        if (status == 0)
            return 0;
        if (verifyInt(buffer, status) == -1)
        {
            printf("\nVolume d'alcool mal forme !\n");
            bout.VolumeAlcool = -1;
        }
        else
        {
            sscanf(buffer, "%d", &bout.VolumeAlcool);
            if (bout.VolumeAlcool <= 1)
                printf("\nVolume d'alcool invalide ! \n");
        
        }

    }while(bout.VolumeAlcool <= 1);

    do
    {
        printf("Entrez l'emplacement : ");
        status = secureInput(emplacement, sizeof(emplacement));
        if (status == 0)
            return 0;

        if (verifyEmplacement(emplacement) == -1)
        {
            printf("\nEmplacement mal forme !\n");
           status = -1;
        }

        else if (RechercheBoutempl(emplacement, nbouteille))
        {
            printf("\nCet emplacement existe deja !\n");
            status = -1;
        }
        else
        {
            strcpy(bout.Emplacement, emplacement);
            status = 0;
        }
    }while(status == -1);


    do
    {
        printf("Entrez l'ID du fournisseur : ");
        status = secureInput(buffer, sizeof(buffer));
        if (status == 0)
            return 0;
        if (verifyInt(buffer, status) == -1)
        {
            printf("\nID du fournisseur mal forme !\n");
            bout.IdFournisseur = -1;
        }
        else
        {
            sscanf(buffer, "%ld", &bout.IdFournisseur);
            if (bout.IdFournisseur <= -1)
                printf("\nID du fournisseur invalide !\n");
        }

    }while(bout.IdFournisseur <= -1);

    bout.DateConso.annee = 0;
    bout.DateConso.jour = 0;
    bout.DateConso.mois = 0;
    *bout.NoteConso = '\0';

    if (openDatabase(&srcFile, FILENAMEBOUTEILLE) != -1)
    {
        fseek(srcFile, 0, SEEK_END);
        if (ecrireBouteille(&bout, srcFile) == -1)
        {
            fclose(srcFile);
            return -1;
        }  
        else
        
            fclose(srcFile);
    }
    else
        return -1;
    
    return 1;
}
//fonction de recherche de bouteille en fct de l'ID
long RechercheBoutempl(char *rechercher, int nbouteilles)
{
    
    struct Bouteille bout;
    int i;
    long curr_bytes;
    FILE *SrcFile;

    i = 0;
    if (i < nbouteilles)
    {
        if(openDatabase(&SrcFile, FILENAMEBOUTEILLE) != -1) 
        {
            rewind(SrcFile);
            while(i < nbouteilles && (lireBouteille(&bout, SrcFile)) != -1)
            {
                if(strcmp(rechercher,bout.Emplacement) == 0)
                {
                    curr_bytes = ftell(SrcFile);
                    fclose(SrcFile);
                    return curr_bytes;
                }
                i++;
            }
            fclose(SrcFile);
            
        }
    }
    return 0;
    
}

long RechercheBoutId(long Id_recherche, int nbouteilles)
{
    
    struct Bouteille bout;
    int i;
    long curr_bytes;
    FILE *SrcFile;

    i = 0;
    if (i < nbouteilles)
    {
        if(openDatabase(&SrcFile, FILENAMEBOUTEILLE) != -1) 
        {
            rewind(SrcFile);
            while(i < nbouteilles && (lireBouteille(&bout, SrcFile)) != -1)
            {
                if(Id_recherche == bout.IdBouteille)
                {
                    curr_bytes = ftell(SrcFile);
                    fclose(SrcFile);
                    return curr_bytes;
                }
                i++;
            }
            fclose(SrcFile);
            
        }
    }
    return 0;
}    


int consommerBouteille(struct Bouteille *bout)
{
    int status = 0, date_verif = 0;
    *bout->Emplacement = '\0';
    char dateBuffer[100];
    
    if (bout->DateConso.annee == 0)
    {
        do
        {
            printf("Entrez la date de consommation : ");
            status = secureInput(dateBuffer, sizeof(dateBuffer));
            date_verif = verifyDate(dateBuffer);
            if (status == 0)
            return 0;
            else if (date_verif == -1)
                printf("La date est mal forme !\n");
            else
            {
                sscanf(dateBuffer, "%hd/%hd/%hd", &bout->DateConso.jour, &bout->DateConso.mois, &bout->DateConso.annee);
                
                if(compareDate(&bout->DateAchat, &bout->DateConso) < 0)
                {
                    printf("La date de consommation est inferieure a la date d'achat !\n");
                    date_verif = -1;
                }

            }
        }while (date_verif == -1);

        printf("Entrez une note de consommation (optionel): ");
        secureInput(bout->NoteConso, sizeof(bout->NoteConso));
        return 1;
    }
    else
    {
        printf("La bouteille a deja ete consommee !\n");
        return -1;
    }


}

int read_single_bottle(long id, struct Bouteille *bout)
{
    FILE *fp = fopen("bouteilles.dat", "rb");
    if (fp == NULL)
    {
        printf("Ouverture du fichier impossible !\n");
    }
    else
    {
        fseek(fp, sizeof(struct Bouteille)*(id-1), SEEK_SET);
        fread(bout, sizeof(struct Bouteille), 1, fp);
        fclose(fp);
    }
    return 0;

}