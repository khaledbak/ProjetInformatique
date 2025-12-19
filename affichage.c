#include "affichage.h"

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
