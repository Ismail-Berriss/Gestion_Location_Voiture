#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "location_Voiture.h"
#include "gestion_Voitures.h"
#include "gestion_Clients.h"
#include "basic_Functions.h"
#define TAILLE_MAX 1000

char ligne[TAILLE_MAX]; // Variable globale

void visualiserContrat()
{
    FILE *fichierLocation = NULL;
    Contrat contrat;
    double numContrat;
    bool exist = false;

    fichierLocation = fopen("D:\\SMI\\S4\\Programmation 2\\Mini-Projet\\fichiers\\contrats.txt", "r");

    if (fichierLocation != NULL)
    {
        printf("\n-Saisir le numero du contrat (8 chiffres): ");
        numContrat = lireLong();

        while (fgets(ligne, TAILLE_MAX, fichierLocation) != NULL)
        {
            sscanf(ligne, "%lf;%ld;%ld;%ld/%ld/%ld;%ld/%ld/%ld;%ld;", &contrat.numContrat, &contrat.idVoiture, &contrat.idClient, &contrat.debut.jour, &contrat.debut.mois, &contrat.debut.annee, &contrat.fin.jour, &contrat.fin.mois, &contrat.fin.annee, &contrat.cout);

            if (numContrat == contrat.numContrat)
            {
                exist = true;
                break;
            }
        }

        if (!exist)
        {
            printf("\n-Ce numero de contrat n'existe pas-\n");
        }
        else
        {
            printf("\n");
            printf(ligne, "\n%f;%ld;%ld;%ld/%ld/%ld;%ld/%ld/%ld;%ld;\n", contrat.numContrat, contrat.idVoiture, contrat.idClient, contrat.debut.jour, contrat.debut.mois, contrat.debut.annee, contrat.fin.jour, contrat.fin.mois, contrat.fin.annee, contrat.cout);
        }
    }
    else
    {
        printf("\nImpossible d'ouvrir le fichier");
    }
}

int louerVoiture()
{
    FILE *fichierLocation = NULL;
    FILE *fichierVoitures = NULL;
    FILE *fichierClients = NULL;
    FILE *temp = NULL;
    Contrat contrat;
    Voiture voiture;
    Client client;
    char nom[20], prenom[20], marque[15], nomVoiture[15];
    bool existClient, existVoiture, valid = true;

    /* 1ère étape : Demander au client de saisir son nom et son prénom, et les informations sur la voiture à louer */

    printf("\nSaisir votre nom (19 car): ");
    lire(nom, 20);

    printf("\nSaisir votre prenom (19 car): ");
    lire(prenom, 20);

    printf("\nSaisir la marque de la voiture que vous souhaitez louer (14 car): ");
    lire(marque, 15);

    printf("\nSaisir le nom de la voiture que vous souhaitez louer (14 car): ");
    lire(nomVoiture, 15);

    /* Etaler leur taille */

    temp = fopen("D:\\SMI\\S4\\Programmation 2\\Mini-Projet\\fichiers\\temp.txt", "a+");

    fprintf(temp, "%19s;%19s;\n", nom, prenom);
    fprintf(temp, "%14s;%14s;\n", marque, nomVoiture);

    rewind(temp);

    fgets(ligne, TAILLE_MAX, temp);
    sscanf(ligne, "%[^;];%[^;]", nom, prenom);

    fgets(ligne, TAILLE_MAX, temp);
    sscanf(ligne, "%[^;];%[^;]", marque, nomVoiture);

    fclose(temp);
    remove("D:\\SMI\\S4\\Programmation 2\\Mini-Projet\\fichiers\\temp.txt");

    /* 2ème étape : Les deux vérifications */

    fichierLocation = fopen("D:\\SMI\\S4\\Programmation 2\\Mini-Projet\\fichiers\\contrats.txt", "a");
    if (fichierLocation == NULL)
        return 0;
    fichierVoitures = fopen("D:\\SMI\\S4\\Programmation 2\\Mini-Projet\\fichiers\\voitures.txt", "r+");
    if (fichierVoitures == NULL)
        return 0;
    fichierClients = fopen("D:\\SMI\\S4\\Programmation 2\\Mini-Projet\\fichiers\\clients.txt", "r+");
    if (fichierClients == NULL)
        return 0;

    /* 1.1 : Vérifier d'éxistance du client */

    rewind(fichierClients);

    while (fgets(ligne, TAILLE_MAX, fichierClients) != NULL)
    {
        sscanf(ligne, "%ld;%[^;];%[^;]", &client.idClient, client.nom, client.prenom);

        if (strcmp(nom, client.nom) == 0 && strcmp(prenom, client.prenom) == 0) // On les compare avec les données saisit par l'utilisateur
        {
            existClient = true; // S'ils sont les mêmes, donc le client exist, et on sort de la boucle
            break;
        }
    }

    if (!existClient) // Si le client n'exist pas
    {
        printf("\n-Il semble que vous n'etes pas enregistrer. Veuiller s'inscrire dans le menu de gestion des clients-\n");

        fclose(fichierLocation);
        fclose(fichierVoitures);
        fclose(fichierClients);
        return 0;
    }

    /* 1.2 : Vérifier si la voiture exist */

    rewind(fichierVoitures);

    while (fgets(ligne, TAILLE_MAX, fichierVoitures) != NULL)
    {
        sscanf(ligne, "%ld;%[^;];%[^;];%[^;];%ld;%ld;%[^;];", &voiture.idVoiture, voiture.marque, voiture.nomVoiture, voiture.couleur, &voiture.nombrePlaces, &voiture.prixJour, voiture.enLocation); // On lit toute la ligne pour qu'on puisse avoire aussi l'aattribut <<enLocation>>

        if (strcmp(marque, voiture.marque) == 0 && strcmp(nomVoiture, voiture.nomVoiture) == 0) // On les compare avec les données saisit par l'utilisateur
        {
            existVoiture = true; // S'ils sont les mêmes, donc la voiture exist, et on sort de la boucle
            break;
        }
    }

    if (!existVoiture)
    {
        printf("\n-La voiture demandee n'existe pas. Veuillez voir les voitures disponibles dans le menu des voitures-\n");

        fclose(fichierLocation);
        fclose(fichierVoitures);
        fclose(fichierClients);
        return 0;
    }
    /* 2 : Disponibilté de la voiture */
    else // existVoiture == true
    {
        // J'ai déjà l'attribut <<enLocation>> de la voiture souhaitée
        if (strcmp(voiture.enLocation, "oui") == 0) // Si la voiture est déjà louée
        {
            printf("\n--Desole. La voiture est deja louee--\n");

            fclose(fichierLocation);
            fclose(fichierVoitures);
            fclose(fichierClients);
            return 0;
        }
        else
        {
            fseek(fichierVoitures, -6, SEEK_CUR);

            fprintf(fichierVoitures, "oui"); // Changer l'attribut <<EnLocation>>

            printf("\n----- Saisir les informations du contrat -----\n");

            /* Je connais déjà l'ID du client et l'ID de la voiture */

            printf("\n-Saisir le numero du contrat (8 chiffres): ");
            contrat.numContrat = lireDouble();

            do
            {
                printf("\n--Saisir la date d'aujourd'hui--\n");
                printf("\n-Saisir le jour : ");
                contrat.debut.jour = lireLong();
                printf("\n-Saisir le mois : ");
                contrat.debut.mois = lireLong();
                printf("\n-Saisir l'annee : ");
                contrat.debut.annee = lireLong();

                if (!valid_date(contrat.debut.jour, contrat.debut.mois, contrat.debut.annee))
                {
                    valid = false;
                    printf("Date non valide.\n");
                }
            } while (!valid);

            do
            {
                printf("\n\n--Saisir la date de fin du contrat--\n");
                printf("-\nSaisir le jour : ");
                contrat.fin.jour = lireLong();
                printf("\n-Saisir le mois : ");
                contrat.fin.mois = lireLong();
                printf("\n-Saisir l'annee : ");
                contrat.fin.annee = lireLong();

                if (!valid_date(contrat.fin.jour, contrat.fin.mois, contrat.fin.annee))
                {
                    valid = false;
                    printf("Date non valide.\n");
                }
            } while (!valid);

            contrat.cout = voiture.prixJour * difference(contrat.debut.jour, contrat.debut.mois, contrat.debut.annee, contrat.fin.jour, contrat.fin.mois, contrat.fin.annee);

            fprintf(fichierLocation, "%8f;%8ld;%8ld;%2ld/%2ld/%4ld;%2ld/%2ld/%4ld;%6ld;", contrat.numContrat, voiture.idVoiture, client.idClient, contrat.debut.jour, contrat.debut.mois, contrat.debut.annee, contrat.fin.jour, contrat.fin.mois, contrat.fin.annee, contrat.cout);

            fprintf(fichierLocation, "\n");

            fclose(fichierLocation);
            fclose(fichierVoitures);
            fclose(fichierClients);

            return 1;
        }
    }
}

int retournerVoiture()
{
    FILE *fichierLocation = NULL;
    FILE *fichierVoiture = NULL;
    Voiture voiture;
    Contrat contrat;
    long id;
    bool exist = false;

    fichierVoiture = fopen("D:\\SMI\\S4\\Programmation 2\\Mini-Projet\\fichiers\\voitures.txt", "r+");
    fichierLocation = fopen("D:\\SMI\\S4\\Programmation 2\\Mini-Projet\\fichiers\\contrats.txt", "r");

    if (fichierLocation != NULL && fichierVoiture != NULL)
    {
        printf("\n--Saisir l'ID de la voiture a retourner : ");
        id = lireLong();

        /* Etape 1 : Changer l'attribut <<enLocation>> de "oui" à "non" */

        // Vérifier si la voiture existe

        while (fgets(ligne, TAILLE_MAX, fichierVoiture) != NULL)
        {
            sscanf(ligne, "%ld;%[^;];%[^;];%[^;];%ld;%ld;%[^;];", &voiture.idVoiture, voiture.marque, voiture.nomVoiture, voiture.couleur, &voiture.nombrePlaces, &voiture.prixJour, voiture.enLocation);

            if (id == voiture.idVoiture)
            {
                exist = true;
                break;
            }
        }

        if (!exist) // Si l'ID n'existe pas
        {
            printf("\nAucune voiture de cette ID exist. Veuillez s'assurer de l'ID\n");

            fclose(fichierLocation);
            fclose(fichierVoiture);
            return 0;
        }
        else // Si l'ID existe
        {

            if (strcmp(voiture.enLocation, "non") == 0)
            {
                printf("\n-Cette voiture n'est pas louee. Veuillez s'assurer de l'ID\n");

                fclose(fichierLocation);
                fclose(fichierVoiture);
                return 0;
            }
            else
            {
                fseek(fichierVoiture, -6, SEEK_CUR);
                fprintf(fichierVoiture, "non");

                /* Etape 2 : Supprimer le contrat */

                fclose(fichierLocation);
                fclose(fichierVoiture);

                supprimerContrat(id);
            }
        }

        return 1;
    }
    else
    {
        printf("\nImpossible d'ouvrir l'un des fichier\n");
        return 0;
    }
}

int modifierContrat()
{
    FILE *fichierLocation = NULL;
    FILE *fichierVoitures = NULL;
    Contrat contrat;
    Voiture voiture;
    double numContrat;
    bool exist = false, valid = true;

    printf("\n");
    fichierLocation = fopen("D:\\SMI\\S4\\Programmation 2\\Mini-Projet\\fichiers\\contrats.txt", "r+");
    if (fichierLocation == NULL)
        return 0;
    fichierVoitures = fopen("D:\\SMI\\S4\\Programmation 2\\Mini-Projet\\fichiers\\voitures.txt", "r+");
    if (fichierVoitures == NULL)
        return 0;

    printf("\n-Saisir le numero du contrat de la voiture (8 chiffres): ");
    numContrat = lireDouble();

    while (fgets(ligne, TAILLE_MAX, fichierLocation) != NULL)
    {
        sscanf(ligne, "%lf;%ld;%ld;%ld/%ld/%ld;%ld/%ld/%ld;%ld;", &contrat.numContrat, &contrat.idVoiture, &contrat.idClient, &contrat.debut.jour, &contrat.debut.mois, &contrat.debut.annee, &contrat.fin.jour, &contrat.fin.mois, &contrat.fin.annee, &contrat.cout);

        if (numContrat == contrat.numContrat)
        {
            exist = true;
            break;
        }
    }

    if (!exist)
    {
        printf("\nLe numero de contrat saisi n'exist pas.");
        fclose(fichierLocation);
        fclose(fichierVoitures);

        return 0;
    }
    else
    {
        while (fgets(ligne, TAILLE_MAX, fichierVoitures) != NULL)
        {
            sscanf(ligne, "%ld;%[^;];%[^;];%[^;];%ld;%ld;%[^;];", &voiture.idVoiture, voiture.marque, voiture.nomVoiture, voiture.couleur, &voiture.nombrePlaces, &voiture.prixJour, voiture.enLocation); // On lit toute la ligne pour qu'on puisse avoire aussi l'aattribut <<enLocation>>

            if (contrat.idVoiture == voiture.idVoiture)
            {
                break;
            }
        }

        do
        {
            printf("\n\n--Saisir la nouvelle date de fin du contrat--\n");
            printf("-\nSaisir le jour : ");
            contrat.fin.jour = lireLong();
            printf("\n-Saisir le mois : ");
            contrat.fin.mois = lireLong();
            printf("\n-Saisir l'annee : ");
            contrat.fin.annee = lireLong();

            if (!valid_date(contrat.fin.jour, contrat.fin.mois, contrat.fin.annee))
            {
                valid = false;
                printf("Date non valide.\n");
            }
        } while (!valid);

        fseek(fichierLocation, -20, SEEK_CUR);

        printf("\n%d\n", difference(contrat.debut.jour, contrat.debut.mois, contrat.debut.annee, contrat.fin.jour, contrat.fin.mois, contrat.fin.annee));

        contrat.cout = voiture.prixJour * difference(contrat.debut.jour, contrat.debut.mois, contrat.debut.annee, contrat.fin.jour, contrat.fin.mois, contrat.fin.annee);

        fprintf(fichierLocation, "%2ld/%2ld/%4ld;%6ld;", contrat.fin.jour, contrat.fin.mois, contrat.fin.annee, contrat.cout);

        fclose(fichierLocation);
        fclose(fichierVoitures);

        return 1;
    }
}

/* La fonction suivante supprime un contrat, soit par l'appel de la fonction à partir de la fonction retournerVoiture, dans ce cas on supprime le contrat sans aucun problème,  ou bien directement du main. Dans ce cas on ne peut pas supprimer le contrat, car si l'attribut <<enLoaction>> contient "non" ça veut dire qu'il n'existe aucun contrat à supprimer, et si l'attribut contient "oui" alors la voiture n'est pas encore retournée, or on ne peut pas le supprimer */

int supprimerContrat(long id)
{
    FILE *fichierLocation = NULL;
    FILE *fichierVoiture = NULL;
    FILE *fichierTemp = NULL;
    Voiture voiture;
    Contrat contrat;
    double numContrat;
    bool existContrat = false;

    fichierVoiture = fopen("D:\\SMI\\S4\\Programmation 2\\Mini-Projet\\fichiers\\voitures.txt", "r");
    fichierLocation = fopen("D:\\SMI\\S4\\Programmation 2\\Mini-Projet\\fichiers\\contrats.txt", "r+");
    fichierTemp = fopen("D:\\SMI\\S4\\Programmation 2\\Mini-Projet\\fichiers\\temp.txt", "a");

    if (fichierLocation != NULL && fichierVoiture != NULL && fichierTemp != NULL)
    {
        if (id != 0) // Si l'appel de supp est fait dans la fonction retourner
        {
            while (fgets(ligne, TAILLE_MAX, fichierLocation) != NULL) // On chercher le contrat à supprimer
            {
                sscanf(ligne, "%lf;%ld;%ld;%ld/%ld/%ld;%ld/%ld/%ld;%ld;", &contrat.numContrat, &contrat.idVoiture, &contrat.idClient, &contrat.debut.jour, &contrat.debut.mois, &contrat.debut.annee, &contrat.fin.jour, &contrat.fin.mois, &contrat.fin.annee, &contrat.cout);

                if (id != contrat.idVoiture)
                {
                    fprintf(fichierTemp, ligne);
                }
            }

            fclose(fichierTemp);
            fclose(fichierLocation);
            fclose(fichierVoiture);

            remove("D:\\SMI\\S4\\Programmation 2\\Mini-Projet\\fichiers\\contrats.txt");
            rename("D:\\SMI\\S4\\Programmation 2\\Mini-Projet\\fichiers\\temp.txt", "D:\\SMI\\S4\\Programmation 2\\Mini-Projet\\fichiers\\contrats.txt");

            return 1;
        }
        else // Si l'appel de la fonction est fait dans le main
        {
            printf("\n--Saisir le numero du contrat a supprimer : ");
            numContrat = lireDouble();

            while (fgets(ligne, TAILLE_MAX, fichierLocation) != NULL)
            {
                sscanf(ligne, "%lf;%ld;%ld;%ld/%ld/%ld;%ld/%ld/%ld;%ld;", &contrat.numContrat, &contrat.idVoiture, &contrat.idClient, &contrat.debut.jour, &contrat.debut.mois, &contrat.debut.annee, &contrat.fin.jour, &contrat.fin.mois, &contrat.fin.annee, &contrat.cout);

                if (numContrat == contrat.numContrat)
                {
                    existContrat = true;
                }
            }

            if (!existContrat)
            {
                printf("\n-Ce numero de contrat n'exist pas.");

                fclose(fichierLocation);
                fclose(fichierVoiture);
                fclose(fichierTemp);

                remove("D:\\SMI\\S4\\Programmation 2\\Mini-Projet\\fichiers\\temp.txt");

                return 0;
            }
            else
            {
                // On cherche l'attribut <<enLoaction>> de la voiture convenable
                while (fgets(ligne, TAILLE_MAX, fichierVoiture) != NULL)
                {
                    sscanf(ligne, "%ld;%[^;];%[^;];%[^;];%ld;%ld;%[^;];", &voiture.idVoiture, voiture.marque, voiture.nomVoiture, voiture.couleur, &voiture.nombrePlaces, &voiture.prixJour, voiture.enLocation);

                    if (contrat.idVoiture == voiture.idVoiture)
                    {
                        break;
                    }
                }

                if (strcmp(voiture.enLocation, "oui") == 0)
                {
                    printf("\n-La voiture louee n'est pas encore retournee. Veuilllez la retourner pour la supprimer-\n");

                    fclose(fichierLocation);
                    fclose(fichierVoiture);
                    fclose(fichierTemp);

                    remove("D:\\SMI\\S4\\Programmation 2\\Mini-Projet\\fichiers\\temp.txt");

                    return 0;
                }
            }
        }
    }
}

// la focntion vérifie si la date est valide ou non

int valid_date(int jour, int mois, int annee)
{
    int is_valid = 1, is_leap = 0;

    if (annee >= 1800 && annee <= 9999)
    {

        //  Vérifier si l'année est bissextiles
        if ((annee % 4 == 0 && annee % 100 != 0) || (annee % 400 == 0))
        {
            is_leap = 1;
        }

        // Vérifier si le mois est entre 1 et 12
        if (mois >= 1 && mois <= 12)
        {
            // Vérifier si le mois est février
            if (mois == 2)
            {
                if (is_leap && jour == 29)
                {
                    is_valid = 1;
                }
                else if (jour > 28)
                {
                    is_valid = 0;
                }
            }

            // Vérifier les jour du mois Avril, Juin, Septembre et Novembre
            else if (mois == 4 || mois == 6 || mois == 9 || mois == 11)
            {
                if (jour > 30)
                {
                    is_valid = 0;
                }
            }

            // Vérifier les jours des mois restant
            // i.e Janvier, Mars, Mai, Juillet, Août, Octobre, Decembre
            else if (jour > 31)
            {
                is_valid = 0;
            }
        }

        else
        {
            is_valid = 0;
        }
    }
    else
    {
        is_valid = 0;
    }

    return is_valid;
}

/* La fonction retourne le nombre d'années bissextiles avant la date donnée */

int countLeapYear(long jour, long mois, long annee)
{
    if (mois <= 2) // Vérifier si l'annee actuelle doit être considérer comme une année bissextile
    {
        annee--;
    }

    // une année est considérée bissextile si elle est (un multiple de 4 et pas un multiple de 100)
    // ou bien un multiple de 400

    return ((annee / 4) - (annee / 100) + (annee / 400));
}

int difference(long jour1, long mois1, long annee1, long jour2, long mois2, long annee2)
{
    int jourMois[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int n1, n2;
    int i;

    n1 = annee1 * 365 + jour1;

    for (i = 0; i < mois1 - 1; i++)
    {
        n1 += jourMois[i];
    }

    n1 += countLeapYear(jour1, mois1, annee1);

    n2 = annee2 * 365 + jour2;

    for (i = 0; i < mois2 - 1; i++)
    {
        n2 += jourMois[i];
    }

    n2 += countLeapYear(jour2, mois2, annee2);

    return n2 - n1;
}
