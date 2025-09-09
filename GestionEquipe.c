#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    GARDIEN,
    DEFENSEUR,
    MILIEU,
    ATTAQUANT
} Poste;

typedef enum
{
    TITULAIRE,
    REMPLACANT
} Statut;

typedef struct
{
    int jour, mois, annee;
} Date;

typedef struct
{
    int id;
    char *nom;
    char *prenom;
    int numeroMaillot;
    Poste poste;
    int age;
    int buts;
    Date dateInscription;
    Statut statut;
} Joueur;

void AjouterDate(Date *dt)
{
    printf("Entrez le jour: ");
    scanf("%d", &dt->jour);
    printf("Entrez le mois: ");
    scanf("%d", &dt->mois);
    printf("Entrez l'annee: ");
    scanf("%d", &dt->annee);
}

void AjouterJou(Joueur *j)
{
    int m, n;
    printf("Entrez le nombre des caractere d'un nom: ");
    scanf("%d", &m);
    printf("Entrez le nombre des caractere d'un prenom: ");
    scanf("%d", &n);
    getchar();
    j->nom = malloc((m + 1) * sizeof(char));
    j->prenom = malloc((n + 1) * sizeof(char));
    printf("Entrez le nom: ");
    scanf("%s", j->nom);
    getchar();
    printf("Entrez le prenom: ");
    scanf("%s", j->prenom);
    getchar();
    printf("Entrez le numero Maillot : ");
    scanf("%d", &j->numeroMaillot);
    getchar();
    printf("Entrez le poste (GARDIEN, DEFENSEUR, MILIEU, ATTAQUANT): ");
    scanf("%s", j->poste);
    printf("Entrez l'age: ");
    scanf("%d", &j->age);
    printf("Entrez le nombre de buts marqués par le joueur:");
    scanf("%d", &j->buts);
    AjouterDate(&j->dateInscription);
    getchar();
    printf("Entrez le statutd'un joueur (TITULAIRE, REMPLACANT): ");
    scanf("%s", j->statut);
}

void Ajouter(Joueur *J, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("Joueur[%d]= ", i + 1);
        AjouterJou(&J[i]);
    }
}

void EchangeV(char **a, char **b){
    char *tmp;
    tmp=*a;
    *a=*b;
    *b=tmp;
}

void AfficherMenu()
{
    int choix;
    do
    {
        printf("\n===========Menu=============");
        printf("\n1. Trier les joueurs par ordre alphabétique (Nom)");
        printf("\n2. Trier les joueurs par âge");
        printf("\n3. Afficher les joueurs par poste");
        printf("votre choix (0 pour arrete):");
        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            TrieAlphabet();
            break;
        case 2:
            TrieAge();
            break;
        case 3:
            AfficherPoste();
            break;
        default:
            // AfficherSimple();
        }
    } while (choix != 0);
}

int main()
{
    FILE *f;
    int n;
    Joueur *j;
    f = fopen("Data.txt", "rw");
    printf("Entrez le nombre des joueur a ajouter: ");
    scanf("%d", &n);
    j = malloc((n + 1) * sizeof(Joueur));
    return 0;
}