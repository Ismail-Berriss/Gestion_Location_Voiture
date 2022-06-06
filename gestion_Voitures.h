/* Structures */

typedef struct Voiture
{
    long idVoiture;
    char marque[15];
    char nomVoiture[15];
    char couleur[8];
    long nombrePlaces;
    long prixJour;
    char enLocation[4];
} Voiture;

/* End Structures */

/* Prototypes */

void listeVoitures();

int ajouterVoiture();

int modifierVoiture();
void changeIDCar(FILE *fileV, long id);
void changeMarque(FILE *fileV, char *marque);
void changeNomCar(FILE *fileV, char *nom);
void changeCouleur(FILE *fileV, char *couleur);
void changeNbPlaces(FILE *fileV, long nbPlaces);
void changePrixJour(FILE *fileV, long prixJour);
void changeEnLocation(FILE *fileV, char *EnLocation);

int supprimerVoiture();

/* End Prototypes */
