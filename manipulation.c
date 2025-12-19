#include "affichage.h"
#include "manipulation.h"

void supprimer_type(char tab[NBLIGNES][NBCOLONNES], char type)
{
    for(int i = 0; i < NBLIGNES; i++)
    {
        for(int j = 0; j < NBCOLONNES; j++)
        {
            if(tab[i][j] == type)
                tab[i][j] = ' ';
        }
    }
}

int detecter_suite(char tab[NBLIGNES][NBCOLONNES], int min_longueur)
{
    int i, j, k;


    for(i = 0; i < NBLIGNES; i++)
    {
        for(j = 0; j <= NBCOLONNES - min_longueur; j++)
        {
            char x = tab[i][j];
            if(x == ' ')
                continue;

            int compteur = 1;
            for(k = 1; k < min_longueur; k++)
                if(tab[i][j+k] == x) compteur++;
            if(compteur == min_longueur)
            {
                if(min_longueur == 6) supprimer_type(tab, x);
                else
                {
                    for(k = 0; k < min_longueur; k++)
                        tab[i][j+k] = ' ';
                }
            }
        }
    }


    for(j = 0; j < NBCOLONNES; j++)
    {
        for(i = 0; i <= NBLIGNES - min_longueur; i++)
        {
            char x = tab[i][j];
            if(x == ' ')
                continue;

            int compteur = 1;
            for(k = 1; k < min_longueur; k++)
                if(tab[i+k][j] == x) compteur++;
            if(compteur == min_longueur)
            {
                if(min_longueur == 6) supprimer_type(tab, x);
                else
                {
                    for(k = 0; k < min_longueur; k++)
                        tab[i+k][j] = ' ';
                }
            }
        }
    }
    return 0;
}



int verif_adjacent(int x1, int y1, int x2, int y2)
{
    return (abs(x1 - x2) == 1 && y1 == y2) || (abs(y1 - y2) == 1 && x1 == x2);
}

void permutation(char tab[NBLIGNES][NBCOLONNES], int x1, int y1, int x2, int y2)
{
    char temp = tab[x1][y1];
    tab[x1][y1] = tab[x2][y2];
    tab[x2][y2] = temp;
}

int boucle_jeu(char plateau[NBLIGNES][NBCOLONNES])
{
    int x = NBCOLONNES/2;
    int y = NBLIGNES /2;
    int touche;
    int selected = 0;
    int selected_x= 0, selected_y =0;

    while(1)
    {
        system("cls");

        affichage_plateau(plateau,x,y);
        printf(("\nposition %d %d"),x,y);
        printf(("\nchosen %d %d"), selected_x, selected_y);
        touche = getch();
        switch (touche)
        {
        case HAUT:
            if (y > 0) y--;
            break;
        case BAS:
            if (y < NBCOLONNES-1) y++;
            break;
        case GAUCHE:
            if (x > 0) x--;
            break;
        case DROITE:
            if (x < NBLIGNES-1) x++;
            break;
        case ESPACE:
            if(!selected)
            {
                selected = 1;
                selected_x = x;
                selected_y = y;
            }
            else
            {
                if(verif_adjacent(selected_x, selected_y, x, y))
                {
                    permutation(plateau, selected_x, selected_y, x, y);
                    detecter_suite(plateau, 4);

                }
                selected = 0;
                selected_x = -1;
                selected_y = -1;
            }
            break;
        case ECHAP:
            return 0;
        }
    }
}
