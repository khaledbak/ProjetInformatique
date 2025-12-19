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


void initialisation_plateau(char tab[NBLIGNES][NBCOLONNES])
{
    char fl_types[5]= {'F','P','O','A','C'};
    int index = 0;
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
