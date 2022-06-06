#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "basic_Functions.h"

void viderBuffer()
{
    /* Chaque fois on lit un caractère dans la variable temporaire tant qu'on n'a pas arrivé à la fin du buffer ('\n' ou EOF) */
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

int lire(char *chaine, int longueur)
{
    char *positionEntree = NULL;

    if (fgets(chaine, longueur, stdin) != NULL) // Si la saisie est correcte
    {
        positionEntree = strchr(chaine, '\n'); // On cherche la position de '\n'
        if (positionEntree != NULL)            // Si on a réussi à le trouver, on veut dire que l'utilisateur n'a pas dépasser le stock disponible
        {
            *positionEntree = '\0'; // On place '\0' à sa place pour marquer la fin de la chaine
        }
        else // S'il a dépasser le, on vide ce qui a resté dans le buffer
        {
            viderBuffer();
        }
        return 1;
    }
    else // S'il y a une erreur de saisie, on vide le buffer anyway
    {
        viderBuffer();
        return 0;
    }
}

long lireLong()
{
    char nombreTexte[100] = {0}; // 100 cases devraient suffire

    if (lire(nombreTexte, 100))
    {
        // Si lecture du texte ok, convertir le nombre en long et le retourner
        return strtol(nombreTexte, NULL, 10);
    }
    else
    {
        // Si problème de lecture, renvoyer 0
        return 0;
    }
}

double lireDouble()
{
    char nombreTexte[100] = {0}; // 100 cases devraient suffire

    if (lire(nombreTexte, 100))
    {
        // Si lecture du texte ok, convertir le nombre en double et le retourner
        return strtod(nombreTexte, NULL);
    }
    else
    {
        // Si problème de lecture, renvoyer 0
        return 0;
    }
}

