/* Structures */

typedef struct Date
{
    long jour;
    long mois;
    long annee;
} Date;

typedef struct ContratLocation
{
    double numContrat;
    long idVoiture;
    long idClient;
    Date debut;
    Date fin;
    long cout;
} Contrat;

/* End Structures */

/* Prototypes */

int louerVoiture();
void visualiserContrat();
int retournerVoiture();
int modifierContrat();
int supprimerContrat(long id);

int countLeapYear(long jour, long mois, long annee);
int difference(long jour1, long mois1, long annee1, long jour2, long mois2, long annee2);
int valid_date(int jour, int mois, int annee);

/* End Prototypes */

