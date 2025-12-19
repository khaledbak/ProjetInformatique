#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "manipulation.h"
#include "affichage.h"


int main()
{
    srand(time(NULL));
    char plateau[NBLIGNES][NBCOLONNES];
    initialisation_plateau(plateau);
    boucle_jeu(plateau);
}
