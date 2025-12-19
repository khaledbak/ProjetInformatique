#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>


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

int combinaison_interdite(char tab[NBLIGNES][NBCOLONNES], int i, int j);
void initialisation_plateau(char tab[NBLIGNES][NBCOLONNES], int niveau);
const char* couleur_item(char c);
void affichage_plateau(char tab[NBLIGNES][NBCOLONNES], int x, int y);


#endif // AFFICHAGE_H_INCLUDED
