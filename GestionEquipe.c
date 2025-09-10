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

// Supprimer le '\n'
void suppRetour(char *c)
{
    int n = strlen(c);
    if (n > 0 && c[n - 1] == '\n')
    {
        c[n - 1] = '\0';
    }
}

void AjouterDate(Date *dt)
{
    printf("Entrez le jour: ");
    scanf("%d", &dt->jour);
    printf("Entrez le mois: ");
    scanf("%d", &dt->mois);
    printf("Entrez l'annee: ");
    scanf("%d", &dt->annee);
}

int nextId(void)
{
    static int id = 1;
    return id++;
}

void TestePoste(Joueur *j, char *buf)
{
    int t = strlen(buf);
    if (strcmp(buf, "GARDIEN") == 0)
    {
        j->poste = GARDIEN;
    }
    else if (strcmp(buf, "DEFENSEUR") == 0)
    {
        j->poste = DEFENSEUR;
    }
    else if (strcmp(buf, "MILIEU") == 0)
    {
        j->poste = MILIEU;
    }
    else if (strcmp(buf, "ATTAQUANT") == 0)
    {
        j->poste = ATTAQUANT;
    }
    else
    {
        printf("Erreur poste !!!\n");
    }
}

void TesteStatut(Joueur *j, char *buf)
{
    int t = strlen(buf);
    if (strcmp(buf, "TITULAIRE") == 0)
    {
        j->statut = TITULAIRE;
    }
    else if (strcmp(buf, "REMPLACANT") == 0)
    {
        j->statut = REMPLACANT;
    }
    else
    {
        printf("Erreur statut !!!\n");
    }
}

void AjouterJou(Joueur *j)
{
    int m, n, t, ts;
    char *p, *s;

    printf("Entrez le nombre des caractere d'un nom: ");
    scanf("%d", &m);
    printf("Entrez le nombre des caractere d'un prenom: ");
    scanf("%d", &n);
    getchar();

    j->nom = malloc((m + 1) * sizeof(char));
    j->prenom = malloc((n + 1) * sizeof(char));
    j->id = nextId();

    printf("Entrez le nom: ");
    fgets(j->nom, m + 1, stdin);
    suppRetour(j->nom);

    printf("Entrez le prenom: ");
    fgets(j->prenom, n + 1, stdin);
    suppRetour(j->prenom);

    printf("Entrez le numero Maillot : ");
    scanf("%d", &j->numeroMaillot);
    // getchar();

    printf("Entrez le nombre des caractere d'un poste: ");
    scanf("%d", &t);
    getchar();

    p = malloc((t + 1) * sizeof(char));
    printf("Entrez le poste (GARDIEN, DEFENSEUR, MILIEU, ATTAQUANT): ");
    fgets(p, t + 1, stdin);
    suppRetour(p);
    TestePoste(j, p);

    printf("Entrez l'age: ");
    scanf("%d", &j->age);

    printf("Entrez le nombre de buts marqués par le joueur:");
    scanf("%d", &j->buts);

    AjouterDate(&j->dateInscription);

    printf("Entrez le nombre des caractere d'un statut: ");
    scanf("%d", &ts);
    getchar();

    s = malloc((ts + 1) * sizeof(char));
    printf("Entrez le statut d'un joueur (TITULAIRE, REMPLACANT): ");
    fgets(s, ts + 1, stdin);
    suppRetour(s);
    TesteStatut(j, s);

    free(p);
    free(s);
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

void Echange(Joueur *a, Joueur *b)
{
    Joueur tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

// trie bulle
void TrieAlphabet(Joueur *j, int n)
{
    int i, test = 0;
    do
    {
        test = 0;
        for (i = 0; i < n - 1; i++)
        {
            if (strcmp(j[i].nom, j[i + 1].nom) > 0)
            {
                Echange(&j[i], &j[i + 1]);
                test = 1;
            }
        }
    } while (test == 1);
}

void TrieAge(Joueur *j, int n)
{
    int i, test = 0;
    do
    {
        test = 0;
        for (i = 0; i < n - 1; i++)
        {
            if (j[i].age > j[i + 1].age)
            {
                Echange(&j[i], &j[i + 1]);
                test = 1;
            }
        }
    } while (test == 1);
}

// Conversion d'un poste
const char *ConvPoste(Poste p)
{
    switch (p)
    {
    case GARDIEN:
        return "GARDIEN";
    case DEFENSEUR:
        return "DEFENSEUR";
    case MILIEU:
        return "MILIEU";
    case ATTAQUANT:
        return "ATTAQUANT";
    default:
        return "INCONNU";
    }
}

// Conversion d'un statut
const char *ConvStatut(Statut s)
{
    switch (s)
    {
    case TITULAIRE:
        return "TITULAIRE";
    case REMPLACANT:
        return "REMPLACANT";
    default:
        return "INCONNU";
    }
}

// Afficher un joueur
void AfficherJoueur(Joueur *j)
{
    printf("Nom: %s\n", j->nom);
    printf("Prenom: %s\n", j->prenom);
    printf("Numero Maillot: %d\n", j->numeroMaillot);
    printf("Poste: %s\n", ConvPoste(j->poste));
    printf("Age: %d\n", j->age);
    printf("Buts: %d\n", j->buts);
    printf("Date Inscription: %d-%d-%d\n", j->dateInscription.jour, j->dateInscription.mois, j->dateInscription.annee);
    printf("Statut: %s\n", ConvStatut(j->statut));

    if (j->buts >= 10)
    {
        printf("Star de l'equipe!\n");
    }
}

// Afficher les joueurs par poste
void AfficherPoste(Joueur *j, int n, Poste p)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (j[i].poste == p)
        {
            printf("Joueur[%d]: \n", i + 1);
            AfficherJoueur(&j[i]);
        }
    }
}

void AfficherMenu(Joueur *j, int n)
{
    char *p;
    int t;
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
            TrieAlphabet(j, n);
            break;
        case 2:
            TrieAge(j, n);
            break;
        case 3:
            printf("Entrez le nombre des caractere d'un poste: ");
            scanf("%d", &t);
            getchar();

            p = malloc((t + 1) * sizeof(char));
            printf("Entrez le poste a rechercher: ");
            fgets(p, t + 1, stdin);
            suppRetour(p);
            TestePoste(j, p);
            // ERREUR ICI !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            AfficherPoste(j, n, p);
            break;
        default:
            printf("choix invalide");
        }
    } while (choix != 0);
}

// Modifier le poste d'un joueur.
void ModifierPoste(Joueur *j, int n, char *nom, Poste p)
{
    int i;
    if (RechercherNom(j, n, nom, &i) == 1)
    {
        j[i].poste = p;
    }
    else
    {
        printf("Aucun Joueur avec cette nom");
    }
}

// Modifier l'âge d'un joueur.
void ModifierAge(Joueur *j, int n, char *nom, int age)
{
    int i;
    if (RechercherNom(j, n, nom, &i) == 1)
    {
        j[i].age = age;
    }
    else
    {
        printf("Aucun Joueur avec cette nom");
    }
}

// Modifier le nombre de buts marqués par un joueur.
void ModifierButsMarque(Joueur *j, int n, char *nom, int butsM)
{
    int i;
    if (RechercherNom(j, n, nom, &i) == 1)
    {
        j[i].buts = butsM;
    }
    else
    {
        printf("Aucun Joueur avec cette nom");
    }
}

void ModifierMenu(Joueur *j, int n)
{
    Poste p;
    char *nom;
    int size;
    int age;
    int butsM;
    int choix;
    do
    {
        printf("\n===========Menu=============");
        printf("\n1. Modifier le poste d'un joueur");
        printf("\n2. Modifier l'âge d'un joueur");
        printf("\n3. Modifier le nombre de buts marqués par un joueur");
        printf("votre choix (0 pour arrete):");
        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            printf("Entrez le nombre des caractere de nom a rechercher:");
            scanf("%d", &size);
            getchar();

            nom = malloc((size + 1) * sizeof(char));

            printf("Entrez le nom a rechercher:");
            fgets(nom, (size + 1), stdin);
            getchar();
            // ERREUR ICI !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            printf("Entrez la nouvelle poste:");
            fgets(p, sizeof(p), stdin);
            ModifierPoste(j, n, nom, p);
            break;
        case 2:
            printf("Entrez le nombre des caractere de nom a rechercher:");
            scanf("%d", &size);
            getchar();
            nom = malloc((size + 1) * sizeof(char));
            printf("Entrez le nom a rechercher:");
            fgets(nom, (size + 1), stdin);
            // getchar();
            printf("Entrez la nouvelle age:");
            scanf("%d", &age);
            ModifierAge(j, n, nom, age);
            break;
        case 3:
            printf("Entrez le nombre des caractere de nom a rechercher:");
            scanf("%d", &size);
            getchar();
            nom = malloc((size + 1) * sizeof(char));
            printf("Entrez le nom a rechercher:");
            fgets(nom, (size + 1), stdin);
            // getchar();
            printf("Entrez la nouvelle buts marque:");
            scanf("%d", &butsM);
            ModifierButsMarque(j, n, nom, butsM);
            break;
        default:
            printf("choix invalide");
        }
    } while (choix != 0);
}

// Rechercher un joueur par Identifiant
int RechercherId(Joueur *j, int n, int id, int *ind)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (j[i].id == id)
        {
            *ind = i;
            return 1;
        }
    }
    return 0;
}

// Rechercher un joueur par Nom
int RechercherNom(Joueur *j, int n, char *nom, int *ind)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (strcmp(j[i].nom, nom) == 0)
        {
            *ind = i;
            return 1;
        }
    }
    return 0;
}

void RechercherMenu(Joueur *j, int n)
{
    int indice;
    int choix;
    do
    {
        printf("\n===========Menu=============");
        printf("\n1. Rechercher un joueur par Identifiant");
        printf("\n2. Rechercher un joueur par Nom");
        printf("votre choix (0 pour arrete):");
        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            // RechercherId();
            break;
        case 2:
            // RechercherNom();
            break;
        default:
            printf("choix invalide");
        }
    } while (choix != 0);
}

void SauvgardeInfoJoueur(FILE *f, Joueur *j)
{
    fprintf(f, "ID: %d\n", j->id);
    fprintf(f, "Nom: %s\n", j->nom);
    fprintf(f, "Prenom: %s\n", j->prenom);
    fprintf(f, "Numero Maillot: %d\n", j->numeroMaillot);
    fprintf(f, "Statut: %s\n", ConvStatut(j->statut));
    fprintf(f, "Poste: %s\n", ConvPoste(j->poste));
    fprintf(f, "Age: %d\n", j->age);
    fprintf(f, "Nombre De Buts Marqués: %d\n", j->buts);
    fprintf(f, "Date Inscription: %d-%d-%d\n", j->dateInscription.jour, j->dateInscription.mois, j->dateInscription.annee);
    fprintf(f, "Statut: %s\n", ConvStatut(j->statut));
}

void SauvgardeFichier(FILE *f, Joueur *j, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        fprintf(f, "Joueur[%d]=\n", i + 1);
        SauvgardeInfoJoueur(f, &j[i]);
    }
}

// Supprimer un joueur par identifiant
void suppId(Joueur **j, int *n, int id)
{ // ERREUR ICI!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    int i;
    int indice;
    if (RechercherId(*j, *n, id, &indice) == 1)
    {
        free((*j)[indice].nom);
        free((*j)[indice].prenom);
        for (i = indice; i < *n - 1; i++)
        {
            (*j)[i] = (*j)[i + 1];
        }
        (*n)--;
        *j = realloc(*j, (*n) * sizeof(Joueur));
        printf("Joueur supprimé!\n");
    }
    else
    {
        printf("ID non trouvé!\n");
    }
}

// Afficher le nombre total de joueurs dans l'équipe
void nombreTJoueur(Joueur *j, int n)
{
    int i;
    int count = 0;
    for (i = 0; i < n; i++)
    {
        count++;
    }
    printf("le nombre totale de joueurs dans equipe est: %d", count);
}

// Afficher l'âge moyen des joueurs
float MoyenAge(Joueur *j, int n)
{
    int i;
    int sum = 0;
    for (i = 0; i < n; i++)
    {
        sum += j[i].age;
    }
    return (float)sum / n;
}

void AfficheAgeMoyenne(Joueur *j, int n)
{
    float m = MoyenAge(j, n);
    printf("L'age moyen des joueur est: %.2lf\n", m);
}

// Afficher les joueurs ayant marqué plus de X buts (X introduit par l’utilisateur)
void AfficheJoueurMarqueX(Joueur *j, int n)
{
    int x;
    int i;
    printf("Entrez le nombre buts:");
    scanf("%d", &x);
    for (i = 0; i < n; i++)
    {
        if (j[i].buts > x)
        {
            AfficherJoueur(&j[i]);
        }
    }
}

// Afficher le meilleur buteur (joueur avec le maximum de buts)
void AfficheMaxButeur(Joueur *j, int n)
{
    int i;
    int indice = 0;
    int max = j[0].buts;
    for (i = 1; i < n; i++)
    {
        if (j[i].buts > max)
        {
            max = j[i].buts;
            indice = i;
        }
    }
    printf("le meilleur buteur est: \n");
    AfficherJoueur(&j[indice]);
}

// Afficher le joueur le plus jeune et le plus âgé
void AfficherPlusJeunePlusAge(Joueur *j, int n)
{
    int minInd = 0, maxInd = 0;
    for (int i = 1; i < n; i++)
    {
        if (j[i].age < j[minInd].age){
            minInd = i;
        }
        if (j[i].age > j[maxInd].age){
            maxInd = i;
        }
    }
    printf("Plus jeune:\n");
    AfficherJoueur(&j[minInd]);
    printf("Plus âgé:\n");
    AfficherJoueur(&j[maxInd]);
}

// Statistiques
void MenuStatistique(Joueur *j, int n)
{
    int choix;
    printf("==========Menu=============\n");
    printf("1. Afficher le nombre total de joueurs dans l'équipe\n");
    printf("2. Afficher l'âge moyen des joueurs\n");
    printf("3. Afficher les joueurs ayant marqué plus de X buts\n");
    printf("4. Afficher le meilleur buteur (joueur avec le maximum de buts)\n");
    printf("5. Afficher le joueur le plus jeune et le plus âgé\n");
    printf("votre choix: ");
    scanf("%d", &choix);
    switch (choix)
    {
    case 1:
        // nombreTJoueur(j, n);
        printf("Total joueurs: %d\n", n);
        break;
    case 2:
        AfficheAgeMoyenne(j, n);
        break;
    case 3:
        AfficheJoueurMarqueX(j, n);
        break;
    case 4:
        AfficheMaxButeur(j, n);
        break;
    case 5:
        AfficherPlusJeunePlusAge(j, n);
        break;
    default:
        printf("Choix invalide");
    }
}

int main()
{
    FILE *f;
    int n;
    Joueur *j;
    int choix;
    f = fopen("Data.txt", "w+");
    if (f == NULL)
    {
        printf("Erreur d'ouverture fichier!!! \n");
        return 1;
    }
    printf("Entrez le nombre des joueur a ajouter: ");
    scanf("%d", &n);
    j = malloc(n * sizeof(Joueur));
    Ajouter(j, n);
    do
    {
        printf("\n===== Menu Principal =====\n");
        printf("1. Ajouter un joueur\n");
        printf("2. Afficher la liste de tous les joueurs\n");
        printf("3. Modifier un joueur\n");
        printf("4. Supprimer un joueur\n");
        printf("5. Rechercher un joueur\n");
        printf("6. Statistiques\n");
        printf("0. Quitter\n");
        printf("votre choix:");
        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        default:
        }
    } while (choix != 0);

    free(j);
    fclose(f);
    return 0;
}