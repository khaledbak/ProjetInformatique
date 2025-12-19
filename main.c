#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define NBLIGNES 25
#define NBCOLONNES 45

// ici on définit les couleurs qu'on pourra utiliser pour notre plateau
#define RESET   "\033[0m"

#define ROUGE   "\033[31m"
#define VERT    "\033[32m"
#define JAUNE   "\033[33m"
#define BLEU    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BLANC   "\033[37m"
#define BG_BLANC    "\033[47m"

//code fleches
#define HAUT    75
#define BAS     77
#define GAUCHE  72
#define DROITE  80
#define ESPACE 32
#define ECHAP 27


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


int main()
{
    srand(time(NULL));
    char plateau[NBLIGNES][NBCOLONNES];
    initialisation_plateau(plateau);
    boucle_jeu(plateau);
}
