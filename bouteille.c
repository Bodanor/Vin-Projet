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