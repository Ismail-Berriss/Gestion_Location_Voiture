/* Structures */

typedef struct Client
{
    long idClient;
    char nom[20];
    char prenom[20];
    long cin;
    char adresse[15];
    long telephone;
} Client;

/* End Structures */

/* Prototypes */

void listeClients();

int ajouterClient();

int modifierClient();
void changeIDClient(FILE *fileV, long id);
void changeNomClient(FILE *fileV, char *nom);
void changePrenom(FILE *fileV, char *prenom);
void changeCIN(FILE *fileV, long cin);
void changeAdresse(FILE *fileV, char *adresse);
void changeTelephone(FILE *fileV, long telephone);

int supprimerClient();

/* End Prototypes */

