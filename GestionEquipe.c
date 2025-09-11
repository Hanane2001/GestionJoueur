#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int RechercherNom(Joueur *j, int n, char *nom, int *ind);
int RechercherId(Joueur *j, int n, int id, int *ind);

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

void initNextId(int maxId)
{
    static int id = 0;
    id = maxId;
}

int nextId()
{
    static int id = 0;
    return ++id;
}

Poste TestePoste(char *buf)
{
    if (strcmp(buf, "GARDIEN") == 0)
    {
        return GARDIEN;
    }
    else if (strcmp(buf, "DEFENSEUR") == 0)
    {
        return DEFENSEUR;
    }
    else if (strcmp(buf, "MILIEU") == 0)
    {
        return MILIEU;
    }
    else if (strcmp(buf, "ATTAQUANT") == 0)
    {
        return ATTAQUANT;
    }
    else
    {
        return POSTE_INCONNU;
    }
}

Statut TesteStatut(char *buf)
{
    if (strcmp(buf, "TITULAIRE") == 0)
    {
        return TITULAIRE;
    }
    else if (strcmp(buf, "REMPLACANT") == 0)
    {
        return REMPLACANT;
    }
    else
    {
        return STATUT_INCONNU;
    }
}

// max id
int MaxId(Joueur *j, int n)
{
    int max = 0;
    for (int i = 0; i < n; i++)
    {
        if (j[i].id > max)
            max = j[i].id;
    }
    return max;
}

// Ajouter un seul joueur
void AjouterJou(Joueur *j)
{
    char p[15], s[15];
    j->id = nextId();
    printf("Entrez le nom: ");
    fgets(j->nom, 50, stdin);
    suppRetour(j->nom);
    getchar();

    printf("Entrez le prenom: ");
    fgets(j->prenom, 50, stdin);
    suppRetour(j->prenom);
    getchar();

    printf("Entrez le numero Maillot : ");
    scanf(" %d", &j->numeroMaillot);
    //getchar();

    printf("Entrez le poste (GARDIEN, DEFENSEUR, MILIEU, ATTAQUANT): ");
    fgets(p, 15, stdin);
    suppRetour(p);
    j->poste = TestePoste(p);
    getchar();
    printf("Entrez l'age: ");
    scanf("%d", &j->age);

    printf("Entrez le nombre de buts marques par le joueur:");
    scanf("%d", &j->buts);

    AjouterDate(&j->dateInscription);
    getchar();

    printf("Entrez le statut d'un joueur (TITULAIRE, REMPLACANT): ");
    fgets(s, 15, stdin);
    suppRetour(s);
    j->statut = TesteStatut(s);
}

// ajouter pleusieur joueur
void Ajouter(Joueur *J, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("Joueur[%d]= ", i + 1);
        AjouterJou(&J[i]);
    }
}

// Ajouter dans tableau
void AjouteTabJ(Joueur **j, int *n)
{
    int i;
    Joueur *tmp = realloc(*j, (*n + 1) * sizeof(Joueur));
    if (tmp == NULL)
    {
        printf("Erreur allocation!\n");
        return;
    }
    else
    {
        *j = tmp;
        AjouterJou(&(*j)[(*n)++]);
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
        return "POSTE_INCONNU";
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
        return "STATUT_INCONNU";
    }
}

// Afficher un joueur
void AfficherJoueur(Joueur *j)
{
    printf("ID: %d\n", j->id);
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

// nombre des lignes dans un fichier
int compterLignes(FILE *f)
{
    int lignes = 0;
    char c;
    fseek(f, 0, SEEK_SET);
    while ((c = fgetc(f)) != EOF)
    {
        if (c == '\n')
        {
            lignes++;
        }
    }
    fseek(f, 0, SEEK_SET);
    return lignes;
}

// lire les donnez sur fichier et stock dans un tableau
Joueur *lireFichier(FILE *f, int *n)
{
    int lignes = compterLignes(f);
    *n = lignes;
    Joueur *j = malloc((*n) * sizeof(Joueur));
    char ligne[200];
    for (int i = 0; i < *n; i++)
    {
        if (fgets(ligne, sizeof(ligne), f) != NULL)
        {
            char posteStr[15], statutStr[15];
            char nomTmp[50], prenomTmp[50];
            int jJour, jMois, jAnnee;
            sscanf(ligne, "%d %s %s %d %s %d %d %d-%d-%d %s", &j[i].id, nomTmp, prenomTmp, &j[i].numeroMaillot, posteStr, &j[i].age, &j[i].buts, &jJour, &jMois, &jAnnee, statutStr);
            strcpy(j[i].nom, nomTmp);
            strcpy(j[i].prenom, prenomTmp);
            j[i].poste = TestePoste(posteStr);
            j[i].statut = TesteStatut(statutStr);
            j[i].dateInscription.jour = jJour;
            j[i].dateInscription.mois = jMois;
            j[i].dateInscription.annee = jAnnee;
        }
    }
    return j;
}

//Affiche tableau
void Afficher(Joueur *j, int n){
    int i;
    for(i=0;i<n;i++){
        AfficherJoueur(&j[i]);
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
    char p[15];
    Poste t;
    int choix;
    do
    {
        printf("\n===========Menu=============");
        printf("\n1. Trier les joueurs par ordre alphabetique (Nom)");
        printf("\n2. Trier les joueurs par age");
        printf("\n3. Afficher les joueurs par poste");
        printf("\nvotre choix (0 pour arrete):");
        scanf("%d", &choix);
        getchar();
        switch (choix)
        {
        case 1:
            TrieAlphabet(j, n);
            Afficher(j,n);
            break;
        case 2:
            TrieAge(j, n);
            Afficher(j,n);
            break;
        case 3:
            printf("Entrez le poste a rechercher: ");
            fgets(p, 15, stdin);
            suppRetour(p);
            t = TestePoste(p);
            AfficherPoste(j, n, t);
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
        AfficherJoueur(&j[i]);
    }
    else
    {
        printf("Aucun Joueur avec cette nom");
    }
}

// Modifier l'âge d'un joueur.
//Erreur ici !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void ModifierAge(Joueur *j, int n, char *nom, int age)
{
    int i;
    if (RechercherNom(j, n, nom, &i) == 1)
    {
        j[i].age = age;
        AfficherJoueur(&j[i]);
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
        AfficherJoueur(&j[i]);
    }
    else
    {
        printf("Aucun Joueur avec cette nom");
    }
}

void ModifierMenu(Joueur *j, int n)
{
    char p[15];
    char nom[50];
    Poste t;
    int age, butsM, choix;
    do
    {
        printf("\n===========Menu=============");
        printf("\n1. Modifier le poste d'un joueur");
        printf("\n2. Modifier l'age d'un joueur");
        printf("\n3. Modifier le nombre de buts marques par un joueur");
        printf("\nvotre choix (0 pour arrete):");
        scanf("%d", &choix);
        getchar();
        switch (choix)
        {
        case 1:
            printf("Entrez le nom a rechercher:");
            fgets(nom, 50, stdin);
            suppRetour(nom);

            printf("Entrez la nouvelle poste:");
            fgets(p, 15, stdin);
            suppRetour(p);
            t = TestePoste(p);
            ModifierPoste(j, n, nom, t);
            break;
        case 2:
            printf("Entrez le nom a rechercher:");
            fgets(nom, 50, stdin);
            suppRetour(nom);
            printf("Entrez la nouvelle age:");
            scanf("%d", &age);
            getchar();
            ModifierAge(j, n, nom, age);
            break;
        case 3:
            printf("Entrez le nom a rechercher:");
            fgets(nom, 50, stdin);
            suppRetour(nom);
            printf("Entrez la nouvelle buts marque:");
            scanf("%d", &butsM);
            getchar();
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
    int indice = 0;
    int id;
    char nom[50];
    int choix;
    do
    {
        printf("\n===========Menu=============");
        printf("\n1. Rechercher un joueur par Identifiant");
        printf("\n2. Rechercher un joueur par Nom");
        printf("\nvotre choix (0 pour arrete):");
        scanf("%d", &choix);
        getchar();
        switch (choix)
        {
        case 1:
            printf("Entrez l'id a rechercher:");
            scanf("%d", &id);
            if (RechercherId(j, n, id, &indice))
            {
                AfficherJoueur(&j[indice]);
            }
            else
            {
                printf("Aucun joueur!!!\n");
            }
            break;
        case 2:
            printf("Entrez le nom a rechercher:");
            fgets(nom, 50, stdin);
            suppRetour(nom);
            if (RechercherNom(j, n, nom, &indice))
            {
                AfficherJoueur(&j[indice]);
            }
            else
            {
                printf("Aucun joueur!!!\n");
            }
            break;
        default:
            printf("choix invalide");
        }
    } while (choix != 0);
}

void SauvgardeInfoJoueur(FILE *f, Joueur *j)
{
    fprintf(f, "%d %s %s %d %s %d %d %02d-%02d-%04d %s", j->id, j->nom, j->prenom, j->numeroMaillot, ConvPoste(j->poste), j->age, j->buts, j->dateInscription.jour, j->dateInscription.mois, j->dateInscription.annee, ConvStatut(j->statut));
}

void SauvgardeFichier(FILE *f, Joueur *j, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (i > 0){
            fprintf(f, "\n");
        }
        SauvgardeInfoJoueur(f, &j[i]);
    }
}

// Supprimer un joueur par identifiant
//Erreur il est supprimer sur tab mais pas le fichier
void suppId(Joueur **j, int *n, int id)
{
    int i;
    int indice;
    if (RechercherId(*j, *n, id, &indice) == 1)
    {
        for (i = indice; i < *n - 1; i++)
        {
            (*j)[i] = (*j)[i + 1];
        }
        (*n)--;
        if (*n == 0)
        {
            free(*j);
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

// Afficher l'âge moyen des joueurs
float MoyenAge(Joueur *j, int n)
{
    int i;
    int sum = 0;
    if (n == 0)
    {
        return 0;
    }
    else
    {
        for (i = 0; i < n; i++)
        {
            sum += j[i].age;
        }
        return (float)sum / n;
    }
}

void AfficheAgeMoyenne(Joueur *j, int n)
{
    float m = MoyenAge(j, n);
    printf("L'age moyen des joueur est: %.2f\n", m);
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
    Joueur *tmp = malloc(n * sizeof(Joueur));
    if (tmp == NULL)
    {
        printf("Erreur allocation!\n");
        return;
    }
    for (int i = 0; i < n; i++)
    {
        tmp[i] = j[i];
    }
    TrieAge(tmp, n);
    if (n == 0) {
        printf("Aucun joueur.\n");
        return;
    }else{
        printf("Plus jeune:\n");
        AfficherJoueur(&tmp[0]);
        printf("Plus âgé:\n");
        AfficherJoueur(&tmp[n - 1]);
    }
    free(tmp);
}

// Statistiques
void MenuStatistique(Joueur *j, int n)
{
    int choix;
    do{
    printf("==========Menu=============\n");
    printf("1. Afficher le nombre total de joueurs dans l'equipe\n");
    printf("2. Afficher l'age moyen des joueurs\n");
    printf("3. Afficher les joueurs ayant marqué plus de X buts\n");
    printf("4. Afficher le meilleur buteur (joueur avec le maximum de buts)\n");
    printf("5. Afficher le joueur le plus jeune et le plus age\n");
    printf("votre choix (0 pour arrete): ");
    scanf("%d", &choix);
    switch (choix)
    {
    case 1:
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
}while(choix!=0);
}

int main()
{
    FILE *f;
    int n;
    Joueur *j;
    int id;
    int choix;
    f = fopen("Data.txt", "r+");
    if (f == NULL)
    {
        printf("Erreur d'ouverture fichier!!! \n");
        return 1;
    }
    j = lireFichier(f, &n);
    int maxId = MaxId(j, n);
    initNextId(maxId);
    do
    {
        printf("\n===== Menu Principal =====\n");
        printf("1. Ajouter un joueur\n");
        printf("2. Afficher la liste de tous les joueurs\n");
        printf("3. Modifier un joueur\n");
        printf("4. Supprimer un joueur\n");
        printf("5. Rechercher un joueur\n");
        printf("6. Statistiques\n");
        printf("7. Quitter\n");
        printf("votre choix:");
        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            AjouteTabJ(&j, &n);
            SauvgardeFichier(f, j, n);
            break;
        case 2:
            AfficherMenu(j, n);
            break;
        case 3:
            ModifierMenu(j, n);
            SauvgardeFichier(f, j, n);
            break;
        case 4:
            printf("Entrez l'id a suppremer:");
            scanf("%d", &id);
            suppId(&j, &n, id);
            SauvgardeFichier(f, j, n);
            break;
        case 5:
            RechercherMenu(j, n);
            break;
        case 6:
            MenuStatistique(j, n);
            break;
        case 7:
            exit(0);
            break;
        default:
            printf("choix invalide");
        }
    } while (choix != 0);

    free(j);
    fclose(f);
    return 0;
}