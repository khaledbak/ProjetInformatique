#ifndef MANIPULATION_H_INCLUDED
#define MANIPULATION_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#define NBLIGNES 25
#define NBCOLONNES 45

//code fleches
#define HAUT    75
#define BAS     77
#define GAUCHE  72
#define DROITE  80
#define ESPACE 32
#define ECHAP 27

int boucle_jeu(char plateau[NBLIGNES][NBCOLONNES]);
int verif_adjacent(int x1, int y1, int x2, int y2);
void permutation(char tab[NBLIGNES][NBCOLONNES], int x1, int y1, int x2, int y2);
int detecter_suite(char tab[NBLIGNES][NBCOLONNES], int min_longueur);
void supprimer_type(char tab[NBLIGNES][NBCOLONNES], char type);

#endif // MANIPULATION_H_INCLUDED
