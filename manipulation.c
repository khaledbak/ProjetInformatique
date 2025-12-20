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

int detecter_suite(char tab[NBLIGNES][NBCOLONNES], int min_longueur, int objectifs[5])
{
    int i, j, k;
    int nb_sup = 0;

    // Vérification horizontale
    for(i = 0; i < NBLIGNES; i++)
    {
        for(j = 0; j <= NBCOLONNES - min_longueur; j++)
        {
            char x = tab[i][j];
            if(x == ' ' || x == '#')
                continue;

            // Vérifier que TOUS les éléments consécutifs sont identiques
            int compteur = 1;
            for(k = 1; k < NBCOLONNES - j && tab[i][j+k] == x; k++)
                compteur++;

            if(compteur >= min_longueur)
            {
                switch(x)  // Utiliser x directement
                {
                case 'F':
                    objectifs[0]+= compteur;
                    break;
                case 'P':
                    objectifs[1]+= compteur;
                    break;
                case 'O':
                    objectifs[2]+= compteur;
                    break;
                case 'A':
                    objectifs[3]+= compteur;
                    break;
                case 'C':
                    objectifs[4]+= compteur;
                    break;
                }
                nb_sup++;
                if(compteur >= 6) supprimer_type(tab, x);  // Si 6 ou plus
                else
                {
                    for(k = 0; k < compteur; k++)  // Supprimer seulement la suite trouvée
                        tab[i][j+k] = ' ';
                }
                j += compteur - 1;  // Sauter les éléments déjà traités
            }
        }
    }

    // Vérification verticale
    for(j = 0; j < NBCOLONNES; j++)
    {
        for(i = 0; i <= NBLIGNES - min_longueur; i++)
        {
            char x = tab[i][j];
            if(x == ' ' || x == '#')
                continue;

            int compteur = 1;
            for(k = 1; k < NBLIGNES - i && tab[i+k][j] == x; k++)
                compteur++;

            if(compteur >= min_longueur)
            {
                switch(x)
                {
                case 'F':
                    objectifs[0]+= compteur;
                    break;
                case 'P':
                    objectifs[1]+= compteur;
                    break;
                case 'O':
                    objectifs[2]+= compteur;
                    break;
                case 'A':
                    objectifs[3]+= compteur;
                    break;
                case 'C':
                    objectifs[4]+= compteur;
                    break;
                }
                nb_sup++;
                if(compteur >= 6) supprimer_type(tab, x);
                else
                {
                    for(k = 0; k < compteur; k++)
                        tab[i+k][j] = ' ';
                }
                i += compteur - 1;  // Sauter les éléments déjà traités
            }
        }
    }
    return nb_sup;
}

void traiter_combi(char plateau[NBLIGNES][NBCOLONNES], int objectifs[5])
{
    int combi;

    do
    {
        combi = verifier_plateau(plateau,objectifs);
        if(combi>0)
        {
            gravite(plateau);
        }
    }
    while(combi>0);
}


int verifier_plateau(char tab[NBLIGNES][NBCOLONNES], int objectifs[5])
{
    int trouve = 0;
    trouve += detecter_croix(tab,objectifs);
    trouve += detecter_carre(tab,objectifs);
    trouve +=detecter_suite(tab, 6, objectifs);  // suite de 6 → supprime tout le type
    //trouve +=detecter_suite(tab, 5, objectifs);  // suite de 4 → supprime seulement la suite
    return trouve;
}

int detecter_carre(char tab[NBLIGNES][NBCOLONNES], int objectifs[5])
{
    int nb_sup=0;

    for(int i = 0; i<=NBLIGNES-4; i++)
    {
        for(int j=0; j<=NBCOLONNES-4; j++)
        {
            char x = tab[i][j];
            if(x==' '|| x=='#')
                continue;
            int contour = 1;

            for(int k =0; k<4; k++)
            {
                if(tab[i][j+k]!=x)
                {
                    contour = 0;
                    break;
                }
            }

            if(contour)
            {
                for(int k = 0; k<4; k++)
                {
                    if(tab[i+3][j+k]!=x)
                    {
                        contour = 0;
                        break;
                    }
                }
            }
            if(contour)
            {
                for(int k =1; k<3; k++)
                {
                    if(tab[i+k][j]!=x)
                    {
                        contour =0;
                        break;
                    }
                }
            }
            if(contour)
            {
                for(int k=1; k<3; k++)
                {
                    if(tab[i+k][j+3]!=x)
                    {
                        contour = 0;
                        break;
                    }
                }
            }

            if(contour)
            {

                int compteur = 0;

                for(int di = 0; di < 4; di++)
                {
                    for(int dj = 0; dj < 4; dj++)
                    {
                        if(tab[i+di][j+dj] == x)
                        {
                            tab[i+di][j+dj] = ' ';
                            compteur++;
                        }
                    }
                }

                switch(x)
                {
                case 'F':
                    objectifs[0] += compteur;
                    break;
                case 'P':
                    objectifs[1] += compteur;
                    break;
                case 'O':
                    objectifs[2] += compteur;
                    break;
                case 'A':
                    objectifs[3] += compteur;
                    break;
                case 'C':
                    objectifs[4] += compteur;
                    break;
                }

                nb_sup++;
                j += 3;
            }

        }
    }
    return nb_sup;
}



int verif_adjacent(int x1, int y1, int x2, int y2)
{
    return (abs(x1 - x2) == 1 && y1 == y2) || (abs(y1 - y2) == 1 && x1 == x2);
}

int permutation(char tab[NBLIGNES][NBCOLONNES], int x1, int y1, int x2, int y2)
{
    if(tab[x1][y1] != '#' && tab[x2][y2] != '#')
    {
        char temp = tab[x1][y1];
        tab[x1][y1] = tab[x2][y2];
        tab[x2][y2] = temp;
        return 1;
    }
    else
        return 0;
}

int detecter_croix(char tab[NBLIGNES][NBCOLONNES], int objectifs[5])
{
    int nb_sup=0;

    for(int i = 2; i<NBLIGNES-2; i++)
    {
        for(int j = 2; j< NBCOLONNES-2; j++)
        {
            char x = tab[i][j];
            if(x == ' '||x=='#')
                continue;

            int croix_valide =1;

            for(int k =-2; k<=2; k++)
            {
                if(tab[i][j+k]!=x)
                {
                    croix_valide =0;
                    break;
                }
            }

            if(croix_valide)
            {
                for(int k =-2; k<=2; k++)
                {
                    if(tab[i+k][j]!=x)
                    {
                        croix_valide = 0;
                        break;
                    }
                }
            }

            if(croix_valide)
            {
                int compteur = 0;

                for(int l = 0; l<NBCOLONNES; l++)
                {
                    if(tab[i][l]== x)
                    {
                        tab[i][l]= ' ';
                        compteur++;
                    }
                }

                for(int m = 0; m <NBLIGNES; m++)
                {
                    if(tab[m][j]== x)
                    {
                        tab[m][j]= ' ';
                        compteur++;
                    }
                }

                switch(x)
                {
                case 'F':
                    objectifs[0] += compteur;
                    break;
                case 'P':
                    objectifs[1] += compteur;
                    break;
                case 'O':
                    objectifs[2] += compteur;
                    break;
                case 'A':
                    objectifs[3] += compteur;
                    break;
                case 'C':
                    objectifs[4] += compteur;
                    break;
                }

                nb_sup++;

            }


        }
    }

    return nb_sup;
}



void gravite(char plateau[NBLIGNES][NBCOLONNES])
{
    char fl_types[5] = {'F','P','O','A','C'};
    int index;

    for (int j = 0; j < NBCOLONNES; j++)
    {
        // Pour chaque colonne, faire tomber les bonbons entre les blocs de #
        for (int segment_bas = NBLIGNES - 1; segment_bas >= 0; segment_bas--)
        {
            // Trouver le bas d'un segment (soit le bas du plateau, soit juste au-dessus d'un #)
            if (plateau[segment_bas][j] == '#')
                continue;

            // Trouver le haut de ce segment
            int segment_haut = segment_bas;
            while (segment_haut > 0 && plateau[segment_haut - 1][j] != '#')
                segment_haut--;

            // Faire tomber les bonbons dans ce segment uniquement
            int write_pos = segment_bas;
            for (int i = segment_bas; i >= segment_haut; i--)
            {
                if (plateau[i][j] != ' ' && plateau[i][j] != '#')
                {
                    plateau[write_pos][j] = plateau[i][j];
                    if (write_pos != i)
                        plateau[i][j] = ' ';
                    write_pos--;
                }
            }

            // Remplir les cases vides dans ce segment
            for (int i = write_pos; i >= segment_haut; i--)
            {
                if (plateau[i][j] == ' ')
                {
                    do
                    {
                        index = rand() % 5;
                        plateau[i][j] = fl_types[index];
                    }
                    while (combinaison_interdite(plateau, i, j));
                }
            }

            // Passer au segment suivant (au-dessus du segment_haut)
            segment_bas = segment_haut - 1;
        }
    }
}

int check_objectif(int niveau, int objectifs[5])
{
    if(niveau==1 && objectifs[0]>=10 && objectifs[1] >=10 && objectifs[2] >= 10 && objectifs[3]>=10 && objectifs[4] >=10)
    {
        return 1;
    }
    else if(niveau==2 && objectifs[0]>=25 && objectifs[1] >=25 && objectifs[2] >= 25 && objectifs[3]>=25 && objectifs[4] >=25)
    {
        return 2;
    }
    else if(niveau==3 && objectifs[0]>=25 && objectifs[1] >=25 && objectifs[2] >= 25 && objectifs[3]>=25 && objectifs[4] >=25)
    {
        return 3;
    }
    else
        return 0;
}


int boucle_jeu(int niveau, char plateau[NBLIGNES][NBCOLONNES], char pseudo[20], int nb_vies)
{
    int x = NBCOLONNES/2;
    int y = NBLIGNES /2;
    int touche;
    int selected = 0;
    int selected_x= 0, selected_y =0;
    int objectifs[5]= {0,0,0,0,0};
    time_t t_debut = time(NULL);
    double temps_passe;
    int nb_coups= 0;
    int temps_max= 0;
    int choix = 0;

    system("cls");
    initialisation_plateau(plateau,niveau);


    switch(niveau)
    {
    case 1:
        nb_coups = 40;
        temps_max = 200;
        break;
    case 2:
        nb_coups = 30;
        temps_max = 120;
        break;
    case 3:
        nb_coups = 25;
        temps_max = 70;
        break;

    }

    affichage_plateau(plateau,x,y);
    printf("\033[14;60HJoueur: %s", pseudo);
    printf("\033[15;60HVies restantes: %d",nb_vies);
    switch(niveau)
    {
    case 1:
        printf("\033[16;60HNiveau 1\033[17;60HF:%d/10 P:%d/10 O:%d/10 A:%d/10 C:%d/10", objectifs[0],objectifs[1],objectifs[2],objectifs[3],objectifs[4] );
        break;
    case 2:
        printf("\033[16;60HNiveau 2\033[17;60HF:%d/25 P:%d/25 O:%d/25 A:%d/25 C:%d/25", objectifs[0],objectifs[1],objectifs[2],objectifs[3],objectifs[4] );
        break;
    case 3:
        printf("\033[16;60HNiveau 3\033[17;60HF:%d/25 P:%d/25 O:%d/25 A:%d/25 C:%d/25", objectifs[0],objectifs[1],objectifs[2],objectifs[3],objectifs[4] );
        break;
    }
    printf("\033[20;60HCoups restants:%2d",nb_coups);
    while(nb_coups>0 && temps_max-temps_passe >0 && check_objectif(niveau, objectifs) == 0)
    {

        temps_passe = difftime(time(NULL),t_debut);

        if(kbhit())
        {

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
                        if(permutation(plateau, selected_x, selected_y, x, y)== 1)
                        {
                            traiter_combi(plateau,objectifs);
                            nb_coups--;
                        }


                    }
                    selected = 0;
                    selected_x = -1;
                    selected_y = -1;
                }
                break;
            case ECHAP:

                do
                {
                    system("cls");
                    printf("Quitter\n");
                    printf("1- Oui\n2- Non\n");
                    scanf("%d", &choix);
                    if(choix >2 || choix <1)
                    {
                        printf("Mauvaise saise\n");
                        Sleep(1000);
                        system("cls");
                    }
                }
                while(choix>2 || choix <1);
                if(choix == 1)
                {
                    printf("Sauvegarde\n");
                    ecrireSauvegarde(niveau, pseudo, nb_vies);
                    return 0;
                }
                break;
            }

            affichage_plateau(plateau,x,y);

            printf(("\nposition %d %d"),x,y);
            switch(niveau)
            {
            case 1:
                printf("\033[16;60HNiveau 1\033[17;60HF:%d/10 P:%d/10 O:%d/10 A:%d/10 C:%d/10", objectifs[0],objectifs[1],objectifs[2],objectifs[3],objectifs[4] );
                break;
            case 2:
                printf("\033[16;60HNiveau 2\033[17;60HF:%d/25 P:%d/25 O:%d/25 A:%d/25 C:%d/25", objectifs[0],objectifs[1],objectifs[2],objectifs[3],objectifs[4] );
                break;
            case 3:
                printf("\033[16;60HNiveau 3\033[17;60HF:%d/25 P:%d/25 O:%d/25 A:%d/25 C:%d/25", objectifs[0],objectifs[1],objectifs[2],objectifs[3],objectifs[4] );
                break;
            }
            printf("\033[14;60HJoueur: %s", pseudo);
            printf("\033[15;60HVies restantes: %d",nb_vies);
            printf("\033[20;60HCoups restants:%2d",nb_coups);

        }
        printf("\033[25;60HTemps restant:%.1f\n",temps_max-temps_passe);
    }
    system("cls");
    if(nb_vies>0)
    {
        if(nb_coups == 0|| temps_max- temps_passe <= 0)
        {
            do
            {
                printf("Voulez vous retentez votre chance ? Il vous reste %d vie(s)\n",nb_vies);
                printf("1- Oui\n2- Non\n");
                scanf("%d", &choix);
                if(choix >2 || choix <1)
                {
                    printf("Mauvaise saise\n");
                    Sleep(1000);
                    system("cls");
                }
            }
            while(choix>2 || choix <1);
            if(choix == 1)
            {
                boucle_jeu(niveau,plateau,pseudo,nb_vies-1);
            }
            else
            {
                printf("Sauvegarde\n");
                ecrireSauvegarde(niveau, pseudo, nb_vies);
            }
        }

        if(check_objectif(niveau, objectifs) == 1)
        {
            boucle_jeu(2,plateau,pseudo,nb_vies);
        }
        else if(check_objectif(niveau, objectifs) == 2)
        {
            boucle_jeu(3,plateau,pseudo,nb_vies);
        }
        else if(check_objectif(niveau, objectifs) == 3)
        {
            system("cls");
            printf("Bravo vous avez reussi !");
            Sleep(2000);
        }
    }
    else
    {
        system("cls");
        printf("Partie terminee, vous avez perdu !\n");
        Sleep(2000);
    }


    system("cls");
    return 1;
}

int chargerSauvegarde()
{
    FILE* fichier;
    char plateau[NBLIGNES][NBCOLONNES];
    int niveau;
    char pseudo[20];
    int nb_vies;

    fichier = fopen("sauvegarde.txt","r");

    if(fichier == NULL)
    {
        printf("Fichier introuvable\n");
        return 1;
    }
    fscanf(fichier,"%d %s %d\n",&niveau, pseudo,&nb_vies);
    fclose(fichier);

    boucle_jeu(niveau,plateau,pseudo,nb_vies);
    return 0;

}

int ecrireSauvegarde(int niveau, char pseudo[20], int nb_vies)
{
    FILE* fichier;

    fichier = fopen("sauvegarde.txt","w");

    if(fichier == NULL)
    {
        printf("Erreur d'ouverture fichier");
        return 1;
    }

    fprintf(fichier, "%d %s %d\n", niveau, pseudo, nb_vies);
    fclose(fichier);
    return 0;
}
