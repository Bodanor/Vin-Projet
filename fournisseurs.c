#include "fournisseurs.h"


void afficherFounisseur(struct fournisseur *four)
{
    printf("\nNom : %s\n", four->nom);
    printf("\nrue : %s\n", four->rue);
    printf("\nnumero : %s\n", four->numero);
    printf("\ncode postal : %s\n", four->codePostal);
    printf("\nlocalite : %s\n", four->localite);
    printf("\npays : %s\n\n", four->pays);


}
int InsertionINDFournisseurs(struct fournisseur** index, struct fournisseur four)
{
     struct fournisseur *pt = NULL, *pt_prec = NULL, *tmp = NULL;

    tmp = (struct fournisseur*)malloc(sizeof(struct fournisseur));
    if (tmp == NULL)
    {
        printf("Demande d'allocation memoire echoué !\n");
        return -1;
    }

    strcpy(tmp->nom, four.nom);
    strcpy(tmp->rue, four.rue);
    strcpy(tmp->numero, four.numero);
    strcpy(tmp->codePostal, four.codePostal);
    strcpy(tmp->localite, four.localite);
    strcpy(tmp->pays, four.pays);
    tmp->idFournisseur = four.idFournisseur;

    if (*index == NULL || strcmp(tmp->pays, (*index)->pays) < 0)
    {
        tmp->psvt = *index;
        *index = tmp;
    }
    else if (strcmp(tmp->pays, (*index)->pays) == 0 && strcmp(tmp->localite, (*index)->localite) < 0)
    {
        tmp->psvt = *index;
        *index = tmp;
    }
    else if (strcmp(tmp->pays, (*index)->pays) == 0 && strcmp(tmp->localite, (*index)->localite) == 0 && strcmp(tmp->nom, (*index)->nom) < 0)
    {
        tmp->psvt = *index;
        *index = tmp;
    }
    else
    {
        pt = *index;

        while (pt != NULL && strcmp(tmp->pays, pt->pays) >= 0)
        {
            pt_prec = pt;
            pt = pt->psvt;
        }

        while (pt != NULL && strcmp(tmp->pays, pt->pays) == 0 && strcmp(tmp->localite, (*index)->localite) >= 0)
        {
            pt_prec = pt;
            pt = pt->psvt;
        }

        while (pt != NULL && strcmp(tmp->pays, pt->pays) == 0 && strcmp(tmp->localite, (*index)->localite) == 0 && strcmp(tmp->nom, (*index)->nom) >= 0)
        {
            pt_prec = pt;
            pt = pt->psvt;
        }

        pt_prec->psvt = tmp;
        tmp->psvt = pt;

    }
    return 0;
}

void RechercheAppellationFournisseurs(struct fournisseur *index, int nfournisseur, char *nom)
{

}
void afficherToutFournisseurs(struct fournisseur *index)
{
    struct fournisseur *pt = index;
    struct fournisseur four;
    FILE *fp = fopen("fournisseurs.dat", "rb");
    while (pt != NULL)
    {

        fseek(fp, sizeof(struct fournisseur)*(pt->idFournisseur -1), SEEK_SET);
        fread(&four, sizeof(struct fournisseur), 1, fp);
        afficherFounisseur(&four);
        pt = pt->psvt;
    }

}
int modifierFournisseurs(struct fournisseur **index, char nom)
{
    return 0;

}
void supressionINDFournisseurs(struct fournisseur **ptete, long idfournisseur)
{
    struct fournisseur *pt = NULL, *pt_prec = NULL;

    pt = *ptete;

    while (pt != NULL && pt->idFournisseur != idfournisseur)
    {
        pt_prec = pt;
        pt = pt->psvt;
    }

    if (pt != NULL && pt->idFournisseur == idfournisseur)
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
int ajouterFournisseurs(struct fournisseur **index, int nfournisseur)
{
    FILE *fp = NULL;
    struct fournisseur four;
    int status = 0;

    fp = fopen("fournisseurs.dat", "ab");
    if (fp == NULL)
    {
        printf("erreur d'ouverture !\n");
        return -1;
    }
    four.idFournisseur = nfournisseur + 1;
    
    printf("nom : ");
    status = secureInput(four.nom, sizeof(four.nom));
    if (status == 0)
        return 0;
    printf("rue : ");
    status = secureInput(four.rue, sizeof(four.rue));
    if (status == 0)
        return 0;
    printf("numero : ");
    status = secureInput(four.numero, sizeof(four.numero));
    if (status == 0)
        return 0;
    printf("code postal : ");
    status = secureInput(four.codePostal, sizeof(four.codePostal));
    if (status == 0)
        return 0;
    printf("localite : ");
    status = secureInput(four.localite, sizeof(four.localite));
    if (status == 0)
        return 0;
    printf("pays : ");
    status = secureInput(four.pays, sizeof(four.pays));
    if (status == 0)
        return 0;
    
    InsertionINDFournisseurs(index, four);
    fseek(fp, 0, SEEK_END);
    fwrite(&four, sizeof(struct fournisseur), 1, fp);
    fclose(fp);
    return 0;

}