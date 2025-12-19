#include "affichage.h"
#include "manipulation.h"

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
            selected = 1;
            selected_x = x;
            selected_y = y;
            break;
        case ECHAP:
            return 0;
        }
    }
}
