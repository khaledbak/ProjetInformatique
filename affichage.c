#include "affichage.h"
#include "manipulation.h"

int combinaison_interdite(char tab[NBLIGNES][NBCOLONNES], int i, int j)
{
    char x = tab[i][j];
    // vérification de la génération à l'horizontale, pas plus de 4 lettre similaire qui s'enchainent
    if (j >= 3 && tab[i][j-1] == x && tab[i][j-2] == x && tab[i][j-3] == x)
        return 1;

    //vérification horizontal pas plus de 4 lettres qui s'enchainent sur la même colonne
    if (i >= 3 && tab[i-1][j] == x && tab[i-2][j] == x && tab[i-3][j] == x)
        return 1;

    return 0;
}


void initialisation_plateau(char tab[NBLIGNES][NBCOLONNES], int niveau)
{
    char fl_types[5]= {'F','P','O','A','C'};
    int index = 0;
    int taille_bloc = 3;
    for(int i = 0; i < NBLIGNES; i ++)
    {
        for(int j = 0; j< NBCOLONNES; j++)
        {
            do
            {
                index = rand()%5;
                tab[i][j]= fl_types[index];
            }
            while(combinaison_interdite(tab, i,j));
        }
    }
    switch (niveau)
    {
    case 1:

        break;
    case 2:
        for (int dy = 0; dy < taille_bloc; dy++)  // parcours les lignes du bloc
        {
            for (int dx = 0; dx < taille_bloc; dx++)  // parcours les colonnes du bloc
            {
                tab[10 + dy][10 + dx] = '#';
            }
        }
        for (int dy = 0; dy < taille_bloc; dy++)  // parcours les lignes du bloc
        {
            for (int dx = 0; dx < taille_bloc; dx++)  // parcours les colonnes du bloc
            {
                tab[15 + dy][15 + dx] = '#';
            }
        }
        for (int dy = 0; dy < taille_bloc; dy++)  // parcours les lignes du bloc
        {
            for (int dx = 0; dx < taille_bloc; dx++)  // parcours les colonnes du bloc
            {
                tab[20 + dy][20 + dx] = '#';
            }
        }
        for (int dy = 0; dy < taille_bloc; dy++)  // parcours les lignes du bloc
        {
            for (int dx = 0; dx < taille_bloc; dx++)  // parcours les colonnes du bloc
            {
                tab[10 + dy][30 + dx] = '#';
            }
        }
        for (int dy = 0; dy < taille_bloc; dy++)  // parcours les lignes du bloc
        {
            for (int dx = 0; dx < taille_bloc; dx++)  // parcours les colonnes du bloc
            {
                tab[15 + dy][25 + dx] = '#';
            }
        }

        break;
    case 3:
        for (int dy = 0; dy < taille_bloc; dy++)  // parcours les lignes du bloc
        {
            for (int dx = 0; dx < taille_bloc; dx++)  // parcours les colonnes du bloc
            {
                tab[10 + dy][10 + dx] = '#';
            }
        }
        for (int dy = 0; dy < taille_bloc; dy++)  // parcours les lignes du bloc
        {
            for (int dx = 0; dx < taille_bloc; dx++)  // parcours les colonnes du bloc
            {
                tab[15 + dy][15 + dx] = '#';
            }
        }
        for (int dy = 0; dy < taille_bloc; dy++)  // parcours les lignes du bloc
        {
            for (int dx = 0; dx < taille_bloc; dx++)  // parcours les colonnes du bloc
            {
                tab[20 + dy][20 + dx] = '#';
            }
        }
        for (int dy = 0; dy < taille_bloc; dy++)  // parcours les lignes du bloc
        {
            for (int dx = 0; dx < taille_bloc; dx++)  // parcours les colonnes du bloc
            {
                tab[10 + dy][30 + dx] = '#';
            }
        }
        for (int dy = 0; dy < taille_bloc; dy++)  // parcours les lignes du bloc
        {
            for (int dx = 0; dx < taille_bloc; dx++)  // parcours les colonnes du bloc
            {
                tab[15 + dy][25 + dx] = '#';
            }
        }
        for (int dy = 0; dy < taille_bloc; dy++)  // parcours les lignes du bloc
        {
            for (int dx = 0; dx < taille_bloc; dx++)  // parcours les colonnes du bloc
            {
                tab[10 + dy][20 + dx] = '#';
            }
        }

        break;
    }
}

// ici on rend une chaine statique ex : ROUGE  "\033[31m" pour définir la couleur des caractères F
const char* couleur_item(char c)
{
    switch (c)
    {
    case 'F':
        return ROUGE;
    case 'P':
        return BLEU;
    case 'O':
        return JAUNE;
    case 'A':
        return VERT;
    case 'C':
        return MAGENTA;
    default:
        return BLANC;
    }
}


void affichage_plateau(char tab[NBLIGNES][NBCOLONNES], int x, int y)
{


    for(int i = 0; i< NBLIGNES; i++)
    {
        printf("\033[%d;%dH",i, 0);
        for(int j = 0; j<NBCOLONNES; j++)
        {
            if(i == x && j == y)
            {
                printf(BG_BLANC"%s%c%s", couleur_item(tab[i][j]), tab[i][j], RESET);
            }
            else
            {
                printf("%s%c%s", couleur_item(tab[i][j]), tab[i][j], RESET);
            }
        }

        printf("\n");
    }
}




void menu()
{

    char pseudo[20];
    char plateau[NBLIGNES][NBCOLONNES];
    int choix = 0;
    while(choix !=4)
    {

        do
        {   system("cls");
            printf("Matching 3:\n");
            printf("1- Nouvelle partie\n");
            printf("2- Charger une partie\n");
            printf("3- Aide\n");
            printf("4- Quitter\n");
            scanf("%d",&choix);
            if(choix>4 || choix<1)
                printf("Mauvaise saise");
            Sleep(500);
            system("cls");
        }
        while(choix >4 || choix < 1);

        switch(choix)
        {
        case 1:
            system("cls");
            printf("Saisir un pseudo (20 caracteres maximum): ");
            do
            {
                scanf("%s", pseudo);

            }
            while(strlen(pseudo)>20);
            boucle_jeu(1,plateau,pseudo,3);
            break;
        case 2:
            chargerSauvegarde();
            break;
        case 3:
            printf(
    "===== REGLES DU MATCHING 3 =====\n\n"
    "Deroulement d'une partie :\n"
    "- Au debut d'une partie, un nombre de vies limite est attribue au joueur.\n"
    "- Une partie comporte au moins 3 niveaux de difficultes croissantes.\n"
    "- Pour gagner la partie, il faut gagner chacun des niveaux.\n"
    "- Pour gagner un niveau, il faut remplir un contrat en un temps limite.\n"
    "- Chaque fois que le joueur perd un niveau, il perd une vie.\n\n"

    "Deroulement d'un niveau :\n"
    "- Chaque niveau se presente sous la forme d'un plateau de jeu de 25 lignes x 45 colonnes.\n"

    "- Le joueur a pour objectif de remplir un contrat annonce au debut du niveau.\n"
    "- Un contrat fixe un nombre d'items a eliminer, un nombre maximum de coups et un temps limite.\n"
    "- Les contrats sont differents sur chaque niveau et de difficultes croissantes.\n\n"


    "Elimination des items :\n"
    "- Certaines suites ou groupes d'items identiques forment des figures particulieres qui font disparaitre les items.\n"
    "- Une suite horizontale ou verticale de 6 items identiques d'un type X provoque la disparition de tous les items de type X presents sur le tableau, meme isoles.\n"
    "- Une croix de 9 items d'un type X provoque la disparition de tous les items de type X sur la meme ligne ou colonne.\n"
    "- Un carre de 4x4 items identiques de type X fait disparaitre tous les items de type X contenus dans le carre.\n"
    "- Une suite horizontale ou verticale de 4 items identiques d'un type X fait disparaitre les items de la suite.\n\n"

    "Exemples d'objectifs a realiser :\n"
    "- Elimine 15 items O\n"
    "- Elimine 11 items X\n"
    "- Elimine 14 items X\n"
    "================================\n"
    );
    while(getch()!=ECHAP)
    {
        return;
    }
            break;
        case 4:
            break;

        }
    }


}
