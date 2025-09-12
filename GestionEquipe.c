#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum
{
    GARDIEN,
    DEFENSEUR,
    MILIEU,
    ATTAQUANT,
    POSTE_INCONNU
} Poste;

typedef enum
{
    TITULAIRE,
    REMPLACANT,
    STATUT_INCONNU
} Statut;

typedef struct
{
    int jour, mois, annee;
} Date;

typedef struct
{
    int id;
    char nom[50];
    char prenom[50];
    int numeroMaillot;
    Poste poste;
    int age;
    int buts;
    Date dateInscription;
    Statut statut;
} Joueur;

static int ID = 0;
void initNextId(int maxId)
{
    ID = maxId;
}

int nextId(void)
{
    return ++ID;
}

void suppRetour(char *c)
{
    int n = strlen(c);
    if (n > 0 && c[n - 1] == '\n')
    {
        c[n - 1] = '\0';
    }
}

Poste TestePoste(char *buf)
{
    if (strcmp(buf, "GARDIEN") == 0)
    {
        return GARDIEN;
    }
    if (strcmp(buf, "DEFENSEUR") == 0)
    {
        return DEFENSEUR;
    }
    if (strcmp(buf, "MILIEU") == 0)
    {
        return MILIEU;
    }
    if (strcmp(buf, "ATTAQUANT") == 0)
    {
        return ATTAQUANT;
    }
    return POSTE_INCONNU;
}

Statut TesteStatut(char *buf)
{
    if (strcmp(buf, "TITULAIRE") == 0)
    {
        return TITULAIRE;
    }
    if (strcmp(buf, "REMPLACANT") == 0)
    {
        return REMPLACANT;
    }
    return STATUT_INCONNU;
}

// Date inscription automatique
void AjouterDate(Date *dt)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    dt->jour = tm.tm_mday;
    dt->mois = tm.tm_mon + 1;
    dt->annee = tm.tm_year + 1900;
}

// Ajouter un seul joueur
void AjouterJou(Joueur *j)
{
    char p[15], s[15];
    j->id = nextId();

    printf("Entrez le nom: ");
    fgets(j->nom, 50, stdin);
    suppRetour(j->nom);

    printf("Entrez le prenom: ");
    fgets(j->prenom, 50, stdin);
    suppRetour(j->prenom);

    printf("Entrez le numero Maillot: ");
    scanf("%d", &j->numeroMaillot);
    getchar();

    printf("Entrez le poste (GARDIEN, DEFENSEUR, MILIEU, ATTAQUANT): ");
    fgets(p, 15, stdin);
    suppRetour(p);
    j->poste = TestePoste(p);

    printf("Entrez l'age: ");
    scanf("%d", &j->age);
    getchar();

    printf("Entrez le nombre de buts marques par le joueur: ");
    scanf("%d", &j->buts);
    getchar();

    AjouterDate(&j->dateInscription);

    printf("Entrez le statut d'un joueur (TITULAIRE, REMPLACANT): ");
    fgets(s, 15, stdin);
    suppRetour(s);
    j->statut = TesteStatut(s);
}

// Ajouter dans tableau dynamique
void AjouteTabJ(Joueur **j, int *n)
{
    Joueur *tmp = realloc(*j, (*n + 1) * sizeof(Joueur));
    if (!tmp)
    {
        printf("Erreur allocation!\n");
        return;
    }
    *j = tmp;
    AjouterJou(&(*j)[(*n)]);
    (*n)++;
}

void Echange(Joueur *a, Joueur *b)
{
    Joueur tmp = *a;
    *a = *b;
    *b = tmp;
}

void TrieAlphabet(Joueur *j, int n)
{
    int i, test;
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
    } while (test);
}

void TrieAge(Joueur *j, int n)
{
    int i, test;
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
    } while (test);
}

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
        return "POSTE_INCONNU";
    }
}

const char *ConvStatut(Statut s)
{
    switch (s)
    {
    case TITULAIRE:
        return "TITULAIRE";
    case REMPLACANT:
        return "REMPLACANT";
    default:
        return "STATUT_INCONNU";
    }
}

void AfficherJoueur(Joueur *j)
{
    printf("\nID: %d\nNom: %s\nPrenom: %s\nNumero Maillot: %d\nPoste: %s\nAge: %d\nButs: %d\nDate Inscription: %02d-%02d-%04d\nStatut: %s\n",
           j->id, j->nom, j->prenom, j->numeroMaillot, ConvPoste(j->poste), j->age, j->buts,
           j->dateInscription.jour, j->dateInscription.mois, j->dateInscription.annee, ConvStatut(j->statut));

    if (j->buts >= 10)
    {
        printf("Star de l'equipe!\n");
    }
}

void Afficher(Joueur *j, int n)
{
    for (int i = 0; i < n; i++)
    {
        AfficherJoueur(&j[i]);
    }
}

void AfficherPoste(Joueur *j, int n, Poste p)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (j[i].poste == p)
        {
            AfficherJoueur(&j[i]);
            count++;
        }
    }
    if (count == 0)
    {
        printf("Aucun joueur pour ce poste.\n");
    }
}

int RechercherId(Joueur *j, int n, int id, int *ind)
{
    for (int i = 0; i < n; i++)
    {
        if (j[i].id == id)
        {
            *ind = i;
            return 1;
        }
    }
    return 0;
}

int RechercherNom(Joueur *j, int n, char *nom, int *ind)
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(j[i].nom, nom) == 0)
        {
            *ind = i;
            return 1;
        }
    }
    return 0;
}

// Modifier
void ModifierPoste(Joueur *j, int n, char *nom, Poste p)
{
    int i;
    if (RechercherNom(j, n, nom, &i))
    {
        j[i].poste = p;
        AfficherJoueur(&j[i]);
    }
    else
    {
        printf("Aucun Joueur avec ce nom\n");
    }
}

void ModifierAge(Joueur *j, int n, char *nom, int age)
{
    int i;
    if (RechercherNom(j, n, nom, &i))
    {
        j[i].age = age;
        AfficherJoueur(&j[i]);
    }
    else
    {
        printf("Aucun Joueur avec ce nom\n");
    }
}

void ModifierButsMarque(Joueur *j, int n, char *nom, int butsM)
{
    int i;
    if (RechercherNom(j, n, nom, &i))
    {
        j[i].buts = butsM;
        AfficherJoueur(&j[i]);
    }
    else
    {
        printf("Aucun Joueur avec ce nom\n");
    }
}

// Supprimer un joueur
void suppId(Joueur **j, int *n, int id)
{
    int indice;
    if (RechercherId(*j, *n, id, &indice))
    {
        for (int i = indice; i < *n - 1; i++)
        {
            (*j)[i] = (*j)[i + 1];
        }
        (*n)--;
        if (*n == 0)
        {
            *j = NULL;
        }
        else
        {
            *j = realloc(*j, (*n) * sizeof(Joueur));
        }
        printf("Joueur supprime!\n");
    }
    else
    {
        printf("ID non trouve!\n");
    }
}

// Sauvegarde dans un fichier
void SauvgardeFichier(Joueur *j, int n)
{
    FILE *f = fopen("Data.txt", "w");
    if (!f)
    {
        printf("Erreur ouverture fichier!\n");
        return;
    }
    for (int i = 0; i < n; i++)
    {
        fprintf(f, "%d;%s;%s;%d;%s;%d;%d;%02d-%02d-%04d;%s\n", j[i].id, j[i].nom, j[i].prenom, j[i].numeroMaillot, ConvPoste(j[i].poste), j[i].age, j[i].buts, j[i].dateInscription.jour, j[i].dateInscription.mois, j[i].dateInscription.annee, ConvStatut(j[i].statut));
    }
    fclose(f);
}

// Lire fichier
Joueur *lireFichier(FILE *f, int *n)
{
    if (!f)
    {
        *n = 0;
        return NULL;
    }
    Joueur *tab = NULL;
    char lignne[200];
    *n = 0;

    while (fgets(lignne, sizeof(lignne), f))
    {
        Joueur tmp;
        char posteStr[15], statutStr[15];
        sscanf(lignne, "%d;%49[^;];%49[^;];%d;%14[^;];%d;%d;%d-%d-%d;%14s", &tmp.id, tmp.nom, tmp.prenom, &tmp.numeroMaillot, posteStr, &tmp.age, &tmp.buts, &tmp.dateInscription.jour, &tmp.dateInscription.mois, &tmp.dateInscription.annee, statutStr);
        tmp.poste = TestePoste(posteStr);
        tmp.statut = TesteStatut(statutStr);

        Joueur *tmpTab = realloc(tab, (*n + 1) * sizeof(Joueur));
        if (!tmpTab)
        {
            free(tab);
            *n = 0;
            return NULL;
        }
        tab = tmpTab;
        tab[*n] = tmp;
        (*n)++;
    }
    return tab;
}

// Fonctions statistiques
float MoyenAge(Joueur *j, int n)
{
    int i;
    if (n == 0)
    {
        return 0;
    }
    int sum = 0;
    for (i = 0; i < n; i++)
    {
        sum += j[i].age;
    }
    return (float)sum / n;
}

void AfficheAgeMoyenne(Joueur *j, int n)
{
    printf("L'age moyen des joueurs est: %.2f\n", MoyenAge(j, n));
}

void AfficheJoueurMarqueX(Joueur *j, int n)
{
    int x;
    printf("Entrez le nombre de buts: ");
    scanf("%d", &x);
    getchar();
    for (int i = 0; i < n; i++)
    {
        if (j[i].buts > x)
        {
            AfficherJoueur(&j[i]);
        }
    }
}

void AfficheMaxButeur(Joueur *j, int n)
{
    if (n == 0)
    {
        return;
    }
    int max = j[0].buts, ind = 0;
    for (int i = 1; i < n; i++)
    {
        if (j[i].buts > max)
        {
            max = j[i].buts;
            ind = i;
        }
    }
    printf("Le meilleur buteur est:\n");
    AfficherJoueur(&j[ind]);
}

void AfficherPlusJeunePlusAge(Joueur *j, int n)
{
    if (n == 0)
    {
        printf("Aucun joueur\n");
        return;
    }
    Joueur *tmp = malloc(n * sizeof(Joueur));
    for (int i = 0; i < n; i++)
    {
        tmp[i] = j[i];
    }
    TrieAge(tmp, n);
    printf("Plus jeune:\n");
    AfficherJoueur(&tmp[0]);
    printf("Plus age:\n");
    AfficherJoueur(&tmp[n - 1]);
    free(tmp);
}

// Menus
void AfficherMenu(Joueur *j, int n)
{
    char p[15];
    Poste t;
    int choix;
    do
    {
        printf("\n===========Menu=============\n1. Trier les joueurs par ordre alphabetique\n2. Trier les joueurs par age\n3. Afficher les joueurs par poste\n4. Retour\nvotre choix: ");
        scanf("%d", &choix);
        getchar();
        switch (choix)
        {
        case 1:
            TrieAlphabet(j, n);
            Afficher(j, n);
            break;
        case 2:
            TrieAge(j, n);
            Afficher(j, n);
            break;
        case 3:
            printf("Entrez le poste: ");
            fgets(p, 15, stdin);
            suppRetour(p);
            t = TestePoste(p);
            AfficherPoste(j, n, t);
            break;
        case 4:
            return;
        default:
            printf("Choix invalide\n");
        }
    } while (choix != 4);
}

void ModifierMenu(Joueur *j, int n)
{
    char p[15], nom[50];
    Poste t;
    int age, butsM, choix;
    do
    {
        printf("\n===========Modifier=============\n1. Modifier le poste\n2. Modifier l'age\n3. Modifier les buts\n4. Retour\nvotre choix: ");
        scanf("%d", &choix);
        getchar();
        switch (choix)
        {
        case 1:
            printf("Nom du joueur: ");
            fgets(nom, 50, stdin);
            suppRetour(nom);
            printf("Nouveau poste: ");
            fgets(p, 15, stdin);
            suppRetour(p);
            t = TestePoste(p);
            ModifierPoste(j, n, nom, t);
            break;
        case 2:
            printf("Nom du joueur: ");
            fgets(nom, 50, stdin);
            suppRetour(nom);
            printf("Nouvel age: ");
            scanf("%d", &age);
            getchar();
            ModifierAge(j, n, nom, age);
            break;
        case 3:
            printf("Nom du joueur: ");
            fgets(nom, 50, stdin);
            suppRetour(nom);
            printf("Nouveau nombre de buts: ");
            scanf("%d", &butsM);
            getchar();
            ModifierButsMarque(j, n, nom, butsM);
            break;
        case 4:
            return;
        default:
            printf("Choix invalide\n");
        }
    } while (choix != 4);
}

void RechercherMenu(Joueur *j, int n)
{
    int choix, id, indice;
    char nom[50];
    do
    {
        printf("\n===========Rechercher=============\n1. Par ID\n2. Par nom\n3. Retour\nvotre choix: ");
        scanf("%d", &choix);
        getchar();
        switch (choix)
        {
        case 1:
            printf("Entrez ID: ");
            scanf("%d", &id);
            getchar();
            if (RechercherId(j, n, id, &indice))
            {
                AfficherJoueur(&j[indice]);
            }
            else
            {
                printf("ID non trouve!\n");
            }
            break;
        case 2:
            printf("Entrez nom: ");
            fgets(nom, 50, stdin);
            suppRetour(nom);
            if (RechercherNom(j, n, nom, &indice))
            {
                AfficherJoueur(&j[indice]);
            }
            else
            {
                printf("Nom non trouve!\n");
            }
            break;
        case 3:
            return;
        default:
            printf("Choix invalide\n");
        }
    } while (choix != 3);
}

void StatistiquesMenu(Joueur *j, int n)
{
    int choix, x;
    do
    {
        printf("\n=========Statistiques=========\n1. Nombre total de joueurs\n2. Age moyen des joueurs\n3. Joueurs ayant marque plus que X buts\n4. Meilleur buteur\n5. Joueur le plus jeune et le plus age\n6. Retour\nVotre choix: ");
        scanf("%d", &choix);
        getchar();

        switch (choix)
        {
        case 1:
            printf("nombre Total de joueurs: %d\n", n);
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
        case 6:
            return;
        default:
            printf("Choix invalide\n");
        }
    } while (choix != 6);
}

int main()
{
    Joueur *j = NULL;
    int n = 0, choix;
    FILE *f = fopen("Data.txt", "r+");
    if (!f)
    {
        f = fopen("Data.txt", "w+");
    }
    j = lireFichier(f, &n);
    fclose(f);

    int maxId = 0;
    for (int i = 0; i < n; i++)
    {
        if (j[i].id > maxId)
        {
            maxId = j[i].id;
        }
    }
    initNextId(maxId);
    int idSup;
    do
    {
        printf("\n=========Menu Principal=========\n1. Ajouter un joueur\n2. Afficher les joueurs\n3. Modifier un joueur\n4. Supprimer un joueur\n5. Rechercher un joueur\n6. Statistiques\n7. Quitter\nVotre choix: ");
        scanf("%d", &choix);
        getchar();
        switch (choix)
        {
        case 1:
            AjouteTabJ(&j, &n);
            SauvgardeFichier(j, n);
            break;
        case 2:
            AfficherMenu(j, n);
            break;
        case 3:
            ModifierMenu(j, n);
            SauvgardeFichier(j, n);
            break;
        case 4:
            printf("Entrez ID a supprimer: ");
            scanf("%d", &idSup);
            getchar();
            suppId(&j, &n, idSup);
            SauvgardeFichier(j, n);
            break;
        case 5:
            RechercherMenu(j, n);
            break;
        case 6:
            StatistiquesMenu(j, n);
            break;
        case 7:
            printf("merci Pour utiliser notre prog!!!\n");
            break;
        default:
            printf("Choix invalide\n");
        }
    } while (choix != 7);

    free(j);
    return 0;
}