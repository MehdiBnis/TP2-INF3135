#ifndef PLATEAU_H
#define PLATEAU_H

/* Bibliothèques locales */

#include "navire.h"

/* Bibliothèques standards */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Valeurs pour 'plateau'
#define VIDE                  0
#define OCCUPE                1

// Valeurs pour 'prop'
#define PAS_DE_NAVIRE         0
#define DEJA_JOUE             (-1)
#define NAVIRE                1

// Valeurs pour 'grille'
#define EAU                   '.'
#define RATE                  'o'
#define TOUCHE                'x'
#define COULE                 '/'

// Limites pour la taille des plateaux
#define MIN_TAILLE_PLATEAU    6
#define MAX_TAILLE_PLATEAU    100

/* Prototypes des fonctions */

void changer_case(int *x_case, int *y_case, int sens, int index);

int est_valide(int **plateau, int taille_plateau, Navire *nav);

int **creer_plateau_vide(int taille_plateau);

char **creer_grille_vide(int taille_plateau);

void initialisation_plateau(int **plateau, int taille_plateau, TypeNavire *types_navire);

void modifier_grille(int x, int y, int case_plateau, char **grille);

void affichage_grille(char **grille, int taille_plateau);

void liberer_plateau(int **plateau, int taille_plateau);

void liberer_grille(char **grille, int taille_plateau);

void affichage_navire_coule(char **grille, int navire_coule, TypeNavire *types_navire);

#endif
