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

void affichageBouteille(struct Bouteille bout)
{
    printf("\nId Bouteille : %ld\n", bout.IdBouteille);
    if (bout.DateAchat.annee != 0)
    {
        printf("Date achat : %hd/%hd/%hd\n",bout.DateAchat.jour, bout.DateAchat.mois, bout.DateAchat.annee);
        printf("Prix achat : %d\n", bout.PrixAchat);
    }
    printf("Contenance : %d\n",bout.Contenance);
    printf("Volume d'alcool : %d\n", bout.VolumeAlcool);
    printf("Emplacement : %s\n", bout.Emplacement);
    printf("Id du Fournisseur : %ld\n", bout.IdFournisseur);
    printf("Id du Vin : %s\n", bout.IdVin);
    if (bout.DateConso.annee != 0)
        printf("Date achat : %hd/%hd/%hd\n",bout.DateConso.jour, bout.DateConso.mois, bout.DateConso.annee);
    if (bout.NoteConso != '\0')
        printf("NoteConso : %s\n\n", bout.NoteConso);
}



