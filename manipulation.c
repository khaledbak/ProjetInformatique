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
    int nb_sup = 0;

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
            {   nb_sup ++;
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
                nb_sup++;
                if(min_longueur == 6) supprimer_type(tab, x);
                else
                {
                    for(k = 0; k < min_longueur; k++)
                        tab[i+k][j] = ' ';
                }
            }
        }
    }
    return nb_sup;
}

void traiter_combi(char plateau[NBLIGNES][NBCOLONNES])
{
    int combi;

    do{
        combi = verifier_plateau(plateau);
        if(combi>0)
        {
            gravite(plateau);
        }
    }while(combi>0);
}


int verifier_plateau(char tab[NBLIGNES][NBCOLONNES])
{   int trouve = 0;
    trouve +=detecter_suite(tab, 6);  // suite de 6 → supprime tout le type
    trouve+=detecter_suite(tab, 5);  // suite de 4 → supprime seulement la suite
    return trouve;
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

void gravite(char plateau[NBLIGNES][NBCOLONNES])
{
    char fl_types[5] = {'F','P','O','A','C'};
    int index;


    for (int j = 0; j < NBCOLONNES; j++)
    {
        int write_pos = NBLIGNES - 1;


        for (int i = NBLIGNES - 1; i >= 0; i--)
        {
            if (plateau[i][j] != ' ')
            {
                plateau[write_pos][j] = plateau[i][j];
                if (write_pos != i)
                    plateau[i][j] = ' ';
                write_pos--;
            }
        }


        for (int i = write_pos; i >= 0; i--)
        {
            do
            {
                index = rand() % 5;
                plateau[i][j] = fl_types[index];
            }
            while (combinaison_interdite(plateau, i, j));
        }
    }
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
                    traiter_combi(plateau);

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
