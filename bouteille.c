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
