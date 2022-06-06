#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gestion_Voitures.h"
#include "location_Voiture.h"
#include "gestion_Clients.h"
#include "basic_Functions.h"

int main()
{
    int continuePrincipal = 1, continueVoiture = 1, continueLocation = 1, continueClient = 1;
    int choixPrincipal, choixVoiture, choixLocation, choixClient;

    while (continuePrincipal)
    {
        continueVoiture = continueLocation = continueClient = 1;
        do
        {

            printf("\n                               \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
            printf("\n                               \xb3  Menu Principal \xb3");
            printf("\n                               \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9");

            printf("\n\n");

            printf("\n               \xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb");
            printf("\n               \xba                                              \xba");
            printf("\n               \xba    Location..............................1   \xba");
            printf("\n               \xba    Gestion voitures......................2   \xba");
            printf("\n               \xba    Gestion clients.......................3   \xba");
            printf("\n               \xba    Quitter...............................4   \xba");
            printf("\n               \xba                                              \xba");
            printf("\n               \xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc");
            printf("\n\n                                Votre choix  :  ");

            choixPrincipal = lireLong();
        } while (choixPrincipal < 1 || choixPrincipal > 4);

        switch (choixPrincipal)
        {
        case 1:
            while (continueLocation)
            {
                do
                {
                    printf("\n                               \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
                    printf("\n                               \xb3 Location d'une voiture  \xb3");
                    printf("\n                               \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9");

                    printf("\n\n");

                    printf("\n               \xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb");
                    printf("\n               \xba                                              \xba");
                    printf("\n               \xba    Visualiser contrat....................1   \xba");
                    printf("\n               \xba    Louer voiture.........................2   \xba");
                    printf("\n               \xba    Retourner voiture.....................3   \xba");
                    printf("\n               \xba    Modifier contrat......................4   \xba");
                    printf("\n               \xba    Supprimer contrat.....................5   \xba");
                    printf("\n               \xba    Retour................................6   \xba");
                    printf("\n               \xba                                              \xba");
                    printf("\n               \xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc");
                    printf("\n\n                                Votre choix  :  ");

                    choixLocation = lireLong();
                } while (choixLocation < 1 || choixLocation > 6);

                switch (choixLocation)
                {
                case 1:
                    visualiserContrat();
                    break;

                case 2:
                    if (louerVoiture())
                    {
                        printf("\nAllocation reussite\n");
                    }
                    break;

                case 3:
                    if (retournerVoiture())
                    {
                        printf("\nRetour reussit\n");
                    }

                    break;

                case 4:
                    if (modifierContrat())
                    {
                        printf("\nModification reussite\n");
                    }

                    break;

                case 5:
                    supprimerContrat(0);
                    break;

                case 6:
                    continueLocation = 0;
                    break;
                }
            }
            break;

        case 2:
            while (continueVoiture)
            {
                do
                {

                    printf("\n                           \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
                    printf("\n                           \xb3 Gestion des Voiture \xb3");
                    printf("\n                           \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9");

                    printf("\n\n");

                    printf("\n               \xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb");
                    printf("\n               \xba                                              \xba");
                    printf("\n               \xba    Liste des voitures....................1   \xba");
                    printf("\n               \xba    Ajouter voiture.......................2   \xba");
                    printf("\n               \xba    Modifier voiture......................3   \xba");
                    printf("\n               \xba    Supprimer voiture.....................4   \xba");
                    printf("\n               \xba    Retour................................5   \xba");
                    printf("\n               \xba                                              \xba");
                    printf("\n               \xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc");
                    printf("\n\n                                Votre choix  :  ");

                    choixVoiture = lireLong();
                } while (choixVoiture < 1 || choixVoiture > 5);

                switch (choixVoiture)
                {
                case 1:
                    listeVoitures();
                    break;

                case 2:
                    if (ajouterVoiture())
                    {
                        printf("\nAjout reussit\n");
                    }
                    break;

                case 3:
                    if (modifierVoiture())
                    {
                        printf("\nModification reussite\n");
                    }
                    break;

                case 4:
                    if (supprimerVoiture())
                    {
                        printf("\nSuppression reussite\n");
                    }
                    break;

                case 5:
                    continueVoiture = 0;
                    break;
                }
            }
            break;
        case 3:
            while (continueClient)
            {
                do
                {
                    printf("\n                             \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
                    printf("\n                             \xb3 Gestion des Clients  \xb3");
                    printf("\n                             \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9");

                    printf("\n\n");

                    printf("\n               \xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb");
                    printf("\n               \xba                                              \xba");
                    printf("\n               \xba    Liste des clients.....................1   \xba");
                    printf("\n               \xba    Ajouter client........................2   \xba");
                    printf("\n               \xba    Modifier client.......................3   \xba");
                    printf("\n               \xba    Supprimer client......................4   \xba");
                    printf("\n               \xba    Retour................................5   \xba");
                    printf("\n               \xba                                              \xba");
                    printf("\n               \xba                                              \xba");
                    printf("\n               \xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc");
                    printf("\n\n                                Votre choix  :  ");
                    choixClient = lireLong();
                } while (choixClient < 1 || choixClient > 5);

                switch (choixClient)
                {
                case 1:
                    listeClients();
                    break;

                case 2:
                    if (ajouterClient())
                    {
                        printf("\nAjout reussit\n");
                    }
                    break;

                case 3:
                    if (modifierClient())
                    {
                        printf("\nModification reussite\n");
                    }
                    break;

                case 4:
                    if (supprimerClient())
                    {
                        printf("\nSuppression reussite\n");
                    }
                    break;

                case 5:
                    continueClient = 0;
                    break;
                }
            }

            break;

        case 4:
            continuePrincipal = 0;
            break;
        }
    }

    return 0;
}
