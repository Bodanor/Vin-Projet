#include "bouteille.h"
 


int fileexist(FILE**srcFile, const char *filename)
{
    *srcFile = fopen(filename, "ab+");
    if (*srcFile == NULL)
    {
        printf("Ouverture du fichier %s impossible\n%s\n", filename, strerror(errno));
        return -1;
    }
    else
        return 1;

}

void affichageBouteille(struct Bouteille *bout)
{
    printf("\nId Bouteille : %ld\n", bout->IdBouteille);
    if (bout->DateAchat.annee != 0)
    {
        printf("Date achat : %hd/%hd/%hd\n",bout->DateAchat.jour, bout->DateAchat.mois, bout->DateAchat.annee);
        printf("Prix achat : %d\n", bout->PrixAchat);
    }
    printf("Contenance : %d\n",bout->Contenance);
    printf("Volume d'alcool : %d\n", bout->VolumeAlcool);
    printf("Emplacement : %s\n", bout->Emplacement);
    printf("Id du Fournisseur : %ld\n", bout->IdFournisseur);
    printf("Id du Vin : %ld\n", bout->IdVin);
    if (bout->DateConso.annee != 0)
        printf("Date achat : %hd/%hd/%hd\n",bout->DateConso.jour, bout->DateConso.mois, bout->DateConso.annee);
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
short EncodeBouteille(struct Bouteille *bout, int nbouteille, struct Vin *vins, int nvin, FILE *SrcFile)
{
    int status = 0;
    char buffer[10];

    bout->IdBouteille = nbouteille + 1;
    /*
    printf("Entrez la date d'achat : ");
    scanf("%hd/%hd/%hd", &bout->DateAchat.jour, &bout->DateAchat.mois, &bout->DateAchat.annee);
    printf("%hd %hd %hd", bout->DateAchat.jour, bout->DateAchat.mois, bout->DateAchat.annee);
    secureInput(prix, sizeof(prix));
    */
    do
    {
        printf("Entrez le prix d'achat : ");
        status = secureInput(buffer, sizeof(buffer));
        if (status == 0)
            return 0;
        if (verifyInt(buffer, status) == -1)
        {
            printf("\nPrix d'achat mal forme !\n");
            bout->PrixAchat = -1;
        }
        else
            sscanf(buffer, "%d", &bout->PrixAchat);
            if (bout->PrixAchat <= -1)
                printf("\nPrix d'achat invalide !\n");

    }while (bout->PrixAchat <= -1);

    do
    {
        printf("Entrez la contenance : ");
        status = secureInput(buffer, sizeof(buffer));
        if (status == 0)
            return 0;
        if (verifyInt(buffer, status) == -1)
        {
            printf("\nContenance mal forme !\n");
            bout->Contenance = -1;
        }
        else
            sscanf(buffer, "%d", &bout->Contenance);
            if (bout->Contenance <= 0)
                printf("\nContenance invalide !\n");

    }while (bout->Contenance <= 0);


    do
    {
        printf("Entrez le volume d'alcool : ");
        status = secureInput(buffer, sizeof(buffer));
        if (status == 0)
            return 0;
        if (verifyInt(buffer, status) == -1)
        {
            printf("\nVolume d'alcool mal forme !\n");
            bout->VolumeAlcool = -1;
        }
        else
            sscanf(buffer, "%d", &bout->VolumeAlcool);
            if (bout->VolumeAlcool <= 1)
                printf("\nVolume d'alcool invalide ! \n");

    }while(bout->VolumeAlcool <= 1);

    printf("Entrez l'emplacement : ");
    status = secureInput(bout->Emplacement, sizeof(bout->Emplacement));
    if (status == 0)
        return 0;

    do
    {
        printf("Entrez l'ID du fournisseur : ");
        status = secureInput(buffer, sizeof(buffer));
        if (status == 0)
            return 0;
        if (verifyInt(buffer, status) == -1)
        {
            printf("\nID du fournisseur mal forme !\n");
            bout->IdFournisseur = -1;
        }
        else
            sscanf(buffer, "%ld", &bout->IdFournisseur);
            if (bout->IdFournisseur <= -1)
                printf("\nID du fournisseur invalide !\n");

    }while(bout->IdFournisseur <= -1);


    do
    {
        printf("Entrez l'ID du vin : ");
        status = secureInput(buffer, sizeof(buffer));
        if (status == 0)
            return 0;
        if (verifyInt(buffer,status) == -1)
            printf("\nID du vin mal forme !\n");
        else
        {
            sscanf(buffer, "%ld", &bout->IdVin);
            if (bout->IdVin < 1 || bout->IdVin > nvin)
            {
                printf("\nID n'existe pas !\n");
                bout->IdVin = -1;
            }
        }

    }while ( bout->IdVin == -1);

    bout->DateConso.annee = 0;
    bout->DateConso.jour = 0;
    bout->DateConso.mois = 0;
    *bout->NoteConso = '\0';
}
/*
    //fonction de recherche de bouteille en fct de l'emplacement
    void RechercheBoutempl(struct Bouteille *bout,FILE*srcFile )
    {
        int trouv=0;
        char nomempl[7];
        fflsuh(stdin);
        gets(nomempl);
        *srcFile=fopen("FileBouteilles.dat,"rb");
        if(*srcFile !=NULL) 
        {2
            while(!trouve && fread())
            
        }
        
        
    }
    */



