#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NBLIGNES 25
#define NBCOLONNES 45

void initialisation_plateau(char tab[NBLIGNES][NBCOLONNES])
{
    char fl_types[5]= {'F','P','O','A','C'};
    int index = 0;
    for(int i = 0; i < NBLIGNES; i ++)
    {
        for(int j = 0; j< NBCOLONNES; j++)
        {
            index = rand()%5;
            tab[i][j]= fl_types[index];
            printf("%c ", tab[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    srand(time(NULL));
    char plateau[NBLIGNES][NBCOLONNES];
    initialisation_plateau(plateau);
}
