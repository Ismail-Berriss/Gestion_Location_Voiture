#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestion_Voitures.h"
#include "basic_Functions.h"
#define TAILLE_MAX 1000

void listeVoitures()
{
    FILE *fichierVoitures = NULL;
    char ligne[TAILLE_MAX];

    fichierVoitures = fopen("D:\\SMI\\S4\\Programmation 2\\Mini-Projet\\fichiers\\voitures.txt", "r"); // Ouvrir le fichier en mode lecture

    if (fichierVoitures != NULL)
    {
        rewind(fichierVoitures); // Se d�place au d�but du fichier

        printf("\n");

        while (fgets(ligne, TAILLE_MAX, fichierVoitures) != NULL)
        {
            printf("%s", ligne);
        }

        fclose(fichierVoitures); // Fermeture du fichier
    }
    else
    {
        printf("\nImpossible d'ouvrir le fichier");
    }
}

int ajouterVoiture() // "int" pour controller les erreurs
{
    FILE *fichierVoitures = NULL; // Pointeur sur fichier
    Voiture voiture;

    fichierVoitures = fopen("D:\\SMI\\S4\\Programmation 2\\Mini-Projet\\fichiers\\voitures.txt", "a"); // Ouvrir le fichier en mode "ajout"

    if (fichierVoitures != NULL) // Si l'ouverture a r�ussi
    {
        printf("\n----- Saisir les informations de la voiture -----\n");

        printf("\n-Saisir le ID de la voiture (8 chiffres): ");
        voiture.idVoiture = lireLong();

        printf("\n-Saisir la marque de la voiture (14 caractere max): ");
        lire(voiture.marque, 15);

        printf("\n-Saisir le nom de la voiture (14 caractere max): ");
        lire(voiture.nomVoiture, 15);

        printf("\n-Saisir la couleur de la voiture (7 caractere max): ");
        lire(voiture.couleur, 8);

        printf("\n-Saisir le nombre de places (2 chiffres max): ");
        voiture.nombrePlaces = lireLong();

        printf("\n-Saisir le prix par jour (5 chiffres max): ");
        voiture.prixJour = lireLong();

        do
        {
            printf("\n-Indiquer si la voiture est en location par oui ou non : ");
            lire(voiture.enLocation, 4);
        } while (strcmp(voiture.enLocation, "oui") != 0 && strcmp(voiture.enLocation, "non") != 0);

        fprintf(fichierVoitures, "%8ld;%14s;%14s;%7s;%2ld;%5ld;%3s;\n", voiture.idVoiture, voiture.marque, voiture.nomVoiture, voiture.couleur, voiture.nombrePlaces, voiture.prixJour, voiture.enLocation);

        fclose(fichierVoitures);

        return 1;
    }
    else
    {
        printf("Impossible d'ouvrir le fichier voitures.txt");

        return 0;
    }
}

int modifierVoiture()
{
    FILE *fichierVoitures = NULL; // Pointeur sur fichier
    Voiture voiture;
    long idVoiture;
    char ligne[TAILLE_MAX];
    int choix = 0;

    fichierVoitures = fopen("D:\\SMI\\S4\\Programmation 2\\Mini-Projet\\fichiers\\voitures.txt", "r+"); // Ouvrir le fichier en mode "lecture et �criture"

    if (fichierVoitures != NULL) // Si l'ouverture � r�ussi
    {
        printf("\n-- Saisir l'ID de la voiture a modifier (8 chiffres): ");
        voiture.idVoiture = lireLong();

        /* Trouver l'ID de la voiture � modifier */

        rewind(fichierVoitures); // Se d�place au d�but du fichier

        fscanf(fichierVoitures, "%ld", &idVoiture); // On stocke le premier nombre de la ligne (qui est l'ID de la voiture de ligne 1) dans la variable idVoiture

        while (idVoiture != voiture.idVoiture) // On teste l'ID de chaque voiture avec l'ID qu'on cherche. Quand on sort de la boucle, on est sure de deux chose : on a l'ID qu'on cherche, et le curseur pointe sur la ligne o� se trouve cette ID (exactement entre l'ID et le 1er point-virgule)
        {
            if (fgets(ligne, TAILLE_MAX, fichierVoitures) == NULL) // Placer le curseur dans la ligne suivante. On teste aussi si on a arriv� � la fin du fichier. Si c'est le cas, aucune voiture a cette ID
            {
                printf("-\nID introuvable!");

                return 0;
            }

            fscanf(fichierVoitures, "%ld", &idVoiture); // On r�cupp�re l'ID de la voiture suivante
        }

        while (choix < 1 || choix > 7)
        {
            printf("\n----Que voulez-vous changer ? ----\n");
            printf("1 : ID de la voiture?\n");
            printf("2 : Marque de la voiture?\n");
            printf("3 : Nom de la voiture?\n");
            printf("4 : Couleur de la voiture?\n");
            printf("5 : Nombre de places de la voiture?\n");
            printf("6 : Prix par jour de la voiture?\n");
            printf("7 : Etat de location?\n");
            printf("Votre choix ? ");
            choix = lireLong();
        }

        switch (choix)
        {
        case 1:
            printf("\nSaisir la nouvelle ID (8 chiffres): ");
            voiture.idVoiture = lireLong();
            changeIDCar(fichierVoitures, voiture.idVoiture);

            break;

        case 2:
            printf("\nSaisir la nouvelle marque (14 caractere max): ");
            lire(voiture.marque, 15);
            changeMarque(fichierVoitures, voiture.marque);

            break;

        case 3:
            printf("\nSaisir le nouveau nom (14 caractere max): ");
            lire(voiture.nomVoiture, 15);
            changeNomCar(fichierVoitures, voiture.nomVoiture);

            break;

        case 4:
            printf("\nSaisir la nouvelle (7 caractere max): ");
            lire(voiture.couleur, 8);
            changeCouleur(fichierVoitures, voiture.couleur);

            break;

        case 5:
            printf("\nSaisir le nouveau nombre de places (2 chiffres max): ");
            voiture.nombrePlaces = lireLong();
            changeNbPlaces(fichierVoitures, voiture.nombrePlaces);

            break;

        case 6:
            printf("\nSaisir le nouveau prix par jour (5 chiffres max): ");
            voiture.prixJour = lireLong();
            changePrixJour(fichierVoitures, voiture.prixJour);

            break;

        case 7:
            do
            {
                printf("\nSaisir le nouveau etat de location (oui ou non) : ");
                lire(voiture.enLocation, 4);
            } while (strcmp(voiture.enLocation, "oui") != 0 && strcmp(voiture.enLocation, "non") != 0);

            changeEnLocation(fichierVoitures, voiture.enLocation);

            break;
        }

        fclose(fichierVoitures);

        return 1;
    }
    else
    {
        printf("Impossible d'ouvrir le fichier voitures.txt");

        return 0;
    }
}

void changeIDCar(FILE *fileV, long id)
{
    fseek(fileV, -8, SEEK_CUR); // Se d�placer vers le d�but de la ligne

    fprintf(fileV, "%8ld", id); // Ecrire � la place de l'encienne valeur
}

void changeMarque(FILE *fileV, char *marque)
{
    fseek(fileV, 1, SEEK_CUR); // Se d�placer vers le champ de la marque

    fprintf(fileV, "%14s", marque);
}

void changeNomCar(FILE *fileV, char *nom)
{
    fseek(fileV, 16, SEEK_CUR); // Se d�placer vers le champ du nom

    fprintf(fileV, "%14s", nom);
}

void changeCouleur(FILE *fileV, char *couleur)
{
    fseek(fileV, 31, SEEK_CUR);

    fprintf(fileV, "%7s", couleur);
}

void changeNbPlaces(FILE *fileV, long nbPlaces)
{
    fseek(fileV, 39, SEEK_CUR);

    fprintf(fileV, "%2ld", nbPlaces);
}

void changePrixJour(FILE *fileV, long prixJour)
{
    fseek(fileV, 42, SEEK_CUR);

    fprintf(fileV, "%5ld", prixJour);
}

void changeEnLocation(FILE *fileV, char *EnLocation)
{
    fseek(fileV, 48, SEEK_CUR);

    fprintf(fileV, "%3s", EnLocation);
}

int supprimerVoiture()
{
    /* On compare l'ID, donn�e pas l'utilisateur, avec l'ID de chaque ligne. S'ils sont diff�rent, on copie la ligne dans un fichier temporaire, sinon on ne la copie pas (on ignore la ligne � supprimer). A la fin, on supprime le fichier original, et on renomme le fichier temporaire et on le donne le nom du fichier supprim� */

    FILE *fichierVoitures = NULL, *fileReceipient = NULL; // Pointeur sur fichier
    Voiture voiture;
    long idVoiture;
    char ligne[TAILLE_MAX];

    fichierVoitures = fopen("D:\\SMI\\S4\\Programmation 2\\Mini-Projet\\fichiers\\voitures.txt", "r");   // Ouvrir le fichier en mode lecture
    fileReceipient = fopen("D:\\SMI\\S4\\Programmation 2\\Mini-Projet\\fichiers\\voituresNew.txt", "w"); // Ouvrir le fichier temporaire en mode �criture

    rewind(fichierVoitures); // Se d�place au d�but du fichier
    rewind(fileReceipient);  // Se d�place au d�but du fichier

    if (fichierVoitures != NULL && fileReceipient != NULL) // Si l'ouverture a r�ussi
    {
        printf("\nSaisir l'ID de la voiture a supprimer (8 caractere): "); // Demander la voiture � supprimer par son ID
        idVoiture = lireLong();

        while (fgets(ligne, TAILLE_MAX, fichierVoitures) != NULL) // Tant qu'on n'a pas arriver � la fin du fichier
        {
            sscanf(ligne, "%ld", &voiture.idVoiture); // R�cup�rer l'ID de la voiture

            if (idVoiture != voiture.idVoiture) // Si cette ID n'est pas la souhait�e
            {
                fprintf(fileReceipient, ligne); // copier la ligne
            }
        }

        fclose(fichierVoitures); // Fermeture du fichier
        fclose(fileReceipient);  // Fermeture du fichier

        remove("D:\\SMI\\S4\\Programmation 2\\Mini-Projet\\fichiers\\voitures.txt");                                                                         // Suppression du fichier original
        rename("D:\\SMI\\S4\\Programmation 2\\Mini-Projet\\fichiers\\voituresNew.txt", "D:\\SMI\\S4\\Programmation 2\\Mini-Projet\\fichiers\\voitures.txt"); // Donner au fichier temporaire le nom du fichier original

        return 1;
    }
    else
    {
        printf("\nImpossible d'ouvrir le fichier");

        return 0;
    }
}
