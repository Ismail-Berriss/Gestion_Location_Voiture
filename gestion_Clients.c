#include <stdio.h>
#include <stdlib.h>
#include "gestion_Clients.h"
#include "basic_Functions.h"
#define TAILLE_MAX 1000

void listeClients()
{
    FILE *fichierClients = NULL;
    char ligne[TAILLE_MAX];

    fichierClients = fopen("D:\\SMI\\S4\\Programmation 2\\Mini-Projet\\fichiers\\clients.txt", "r"); // Ouvrir le fichier en mode lecture

    if (fichierClients != NULL)
    {
        rewind(fichierClients); // Se d�place au d�but du fichier

        printf("\n");

        while (fgets(ligne, TAILLE_MAX, fichierClients) != NULL)
        {
            printf("%s", ligne);
        }

        fclose(fichierClients); // Fermeture du fichier
    }
    else
    {
        printf("\nImpossible d'ouvrir le fichier clients.txt");
    }
}

int ajouterClient() // "int" pour controller les erreurs
{
    FILE *fichierClients = NULL; // Pointeur sur fichier
    Client client;

    fichierClients = fopen("D:\\SMI\\S4\\Programmation 2\\Mini-Projet\\fichiers\\clients.txt", "a"); // Ouvrir le fichier en mode "ajout"

    if (fichierClients != NULL) // Si l'ouverture a r�ussi
    {
        printf("\n----- Saisir les informations du client -----\n");

        printf("\n-Saisir le ID du client (8 chiffres): ");
        client.idClient = lireLong();

        printf("\n-Saisir le nom du client (19 caractere max): ");
        lire(client.nom, 20);

        printf("\n-Saisir le prenom du client (19 caractere max): ");
        lire(client.prenom, 20);

        printf("\n-Saisir le CIN du client (8 chiffres): ");
        client.cin = lireLong();

        printf("\n-Saisir l'adresse du client (14 caractere max): ");
        lire(client.adresse, 15);

        printf("\n-Saisir le numero de telephone du client (12 chiffres): ");
        client.telephone = lireLong();

        fprintf(fichierClients, "%8ld;%19s;%19s;%8ld;%14s;%12ld;", client.idClient, client.nom, client.prenom, client.cin, client.adresse, client.telephone);

        fprintf(fichierClients, "\n");

        fclose(fichierClients);

        return 1;
    }
    else
    {
        printf("Impossible d'ouvrir le fichier clients.txt");

        return 0;
    }
}

int modifierClient()
{
    FILE *fichierClients = NULL; // Pointeur sur fichier
    Client client;
    long idClient;
    char ligne[TAILLE_MAX];
    int choix = 0;

    fichierClients = fopen("D:\\SMI\\S4\\Programmation 2\\Mini-Projet\\fichiers\\clients.txt", "r+"); // Ouvrir le fichier en mode "lecture et �criture"

    if (fichierClients != NULL) // Si l'ouverture � r�ussi
    {
        printf("\n-- Saisir l'ID du client a modifier (8 nombres): ");
        client.idClient = lireLong();

        /* Trouver l'ID du client � modifier */

        rewind(fichierClients); // Se d�place au d�but du fichier

        fscanf(fichierClients, "%ld", &idClient); // On stocke le premier nombre de la ligne (qui est l'ID du client de ligne 1) dans la variable idClient

        while (idClient != client.idClient) // On teste l'ID de chaque client avec l'ID qu'on cherche. Quand on sort de la boucle, on est sure de deux chose : on a l'ID qu'on cherche, et le curseur pointe sur la ligne o� se trouve cette ID (exactement entre l'ID et le 1er point-virgule)
        {
            if (fgets(ligne, TAILLE_MAX, fichierClients) == NULL) // Placer le curseur dans la ligne suivante. On teste aussi si on a arriv� � la fin du fichier. Si c'est le cas, aucun client � cette ID
            {
                printf("-\nID introuvable!");

                return 0;
            }

            fscanf(fichierClients, "%ld", &idClient); // On r�cupp�re l'ID du client suivant
        }

        while (choix < 1 || choix > 6)
        {
            printf("\n----Que voulez-vous changer ? ----\n");
            printf("1 : ID du client?\n");
            printf("2 : Nom du client?\n");
            printf("3 : Prenom du client?\n");
            printf("4 : CIN du client?\n");
            printf("5 : Adresse du client?\n");
            printf("6 : Numero de telephone du client?\n");
            printf("Votre choix ? ");
            choix = lireLong();
        }

        switch (choix)
        {
        case 1:
            printf("\nSaisir la nouvelle ID (8 nombres): ");
            client.idClient = lireLong();
            changeIDClient(fichierClients, client.idClient);

            break;

        case 2:
            printf("\nSaisir le nouveau nom (19 caractere max): ");
            lire(client.nom, 20);
            changeNomClient(fichierClients, client.nom);

            break;

        case 3:
            printf("\nSaisir le nouveau prenom (19 caractere max): ");
            lire(client.prenom, 20);
            changePrenom(fichierClients, client.prenom);

            break;

        case 4:
            printf("\nSaisir le nouveau CIN (8 nombres): ");
            client.cin = lireLong();
            changeCIN(fichierClients, client.cin);

            break;

        case 5:
            printf("\nSaisir la nouvelle adresse (14 caractere max): ");
            lire(client.adresse, 15);
            changeAdresse(fichierClients, client.adresse);

            break;

        case 6:
            printf("\nSaisir le nouveau numero de telephone (12 nombres): ");
            client.telephone = lireLong();
            changeTelephone(fichierClients, client.telephone);

            break;
        }

        fclose(fichierClients);

        return 1;
    }
    else
    {
        printf("Impossible d'ouvrir le fichier clients.txt");

        return 0;
    }
}

void changeIDClient(FILE *fileV, long id)
{
    fseek(fileV, -8, SEEK_CUR); // Se d�placer vers le d�but de la ligne

    fprintf(fileV, "%8ld", id); // Ecrire � la place de l'encienne valeur
}

void changeNomClient(FILE *fileV, char *nom)
{
    fseek(fileV, 1, SEEK_CUR); // Se d�placer vers le champ du nom

    fprintf(fileV, "%19s", nom);
}

void changePrenom(FILE *fileV, char *prenom)
{
    fseek(fileV, 21, SEEK_CUR); // Se d�placer vers le champ du nom

    fprintf(fileV, "%19s", prenom);
}

void changeCIN(FILE *fileV, long cin)
{
    fseek(fileV, 41, SEEK_CUR); // Se d�placer vers le champ du nom

    fprintf(fileV, "%8ld", cin);
}

void changeAdresse(FILE *fileV, char *adresse)
{
    fseek(fileV, 50, SEEK_CUR); // Se d�placer vers le champ du nom

    fprintf(fileV, "%14s", adresse);
}

void changeTelephone(FILE *fileV, long telephone)
{
    fseek(fileV, 65, SEEK_CUR); // Se d�placer vers le champ du nom

    fprintf(fileV, "%12ld", telephone);
}

int supprimerClient()
{
    /* On compare l'ID, donn�e pas l'utilisateur, avec l'ID de chaque ligne. S'ils sont diff�rent, on copie la ligne dans un fichier temporaire, sinon on ne la copie pas (on ignore la ligne � supprimer). A la fin, on supprime le fichier original, et on renomme le fichier temporaire et on le donne le nom du fichier supprim� */

    FILE *fichierClients = NULL, *fileReceipient = NULL; // Pointeur sur fichier
    Client client;
    long idClient;
    char ligne[TAILLE_MAX];

    fichierClients = fopen("D:\\SMI\\S4\\Programmation 2\\Mini-Projet\\fichiers\\clients.txt", "r");    // Ouvrir le fichier en mode lecture
    fileReceipient = fopen("D:\\SMI\\S4\\Programmation 2\\Mini-Projet\\fichiers\\clientsNew.txt", "w"); // Ouvrir le fichier temporaire en mode �criture

    rewind(fichierClients); // Se d�place au d�but du fichier
    rewind(fileReceipient); // Se d�place au d�but du fichier

    if (fichierClients != NULL && fileReceipient != NULL) // Si l'ouverture a r�ussi
    {
        printf("\nSaisir l'ID du client a supprimer (8 nombres): "); // Demander le client � supprimer par son ID
        idClient = lireLong();

        while (fgets(ligne, TAILLE_MAX, fichierClients) != NULL) // Tant qu'on n'a pas arriver � la fin du fichier
        {
            sscanf(ligne, "%ld", &client.idClient); // R�cup�rer l'ID du client

            if (idClient != client.idClient) // Si cette ID n'est pas la souhait�e
            {
                fprintf(fileReceipient, ligne); // copier la ligne
            }
        }

        fclose(fichierClients); // Fermeture du fichier
        fclose(fileReceipient); // Fermeture du fichier

        remove("D:\\SMI\\S4\\Programmation 2\\Mini-Projet\\fichiers\\clients.txt");                                                                        // Suppression du fichier original
        rename("D:\\SMI\\S4\\Programmation 2\\Mini-Projet\\fichiers\\clientsNew.txt", "D:\\SMI\\S4\\Programmation 2\\Mini-Projet\\fichiers\\clients.txt"); // Donner au fichier temporaire le nom du fichier original

        return 1;
    }
    else
    {
        printf("\nImpossible d'ouvrir le fichier");

        return 0;
    }
}
