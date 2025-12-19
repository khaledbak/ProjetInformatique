#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "manipulation.h"
#include "affichage.h"


int main()
{
    srand(time(NULL));
    char pseudo[20]="Saad";
    char plateau[NBLIGNES][NBCOLONNES];
    boucle_jeu(1,plateau,pseudo);
}
