#ifndef NAVIRE_H
#define NAVIRE_H

/* Bibliothèques locales */

#include "util.h"

/* Bibliothèques standards */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Nombre de navires sur un plateau (5)
#define NB_NAVIRES      5

/* Types struct */

// Structure d'une case d'un navire
typedef struct une_case {
   int x;		         // Abscisse de la case
   int y;		         // Ordonnée de la case
} Case;

// Structure pour un navire quelconque
typedef struct navire {
   int sens;		      // Sens du navire
   Case premiere_case;	// Position de la première case du navire
   int taille_navire;   // Taille du navire
} Navire;

// Structure pour un navire spécifique sur le plateau
typedef struct type_navire {
   char *nom;
   Case **positions;
   int taille;
   int coups_subis;
} TypeNavire;

/* Prototypes des fonctions */

void positionner_case(int *x_case, int *y_case, int sens_navire, int taille_navire, int taille_plateau);

void definir_noms(TypeNavire *types_navire);

void definir_tailles(TypeNavire *types_navire);

void initialiser_positions(TypeNavire *types_navire);

void initialiser_coups(TypeNavire *types_navire);

TypeNavire *initialiser_types();

void liberer_types(TypeNavire *types_navire);

void ajouter_position_navire(int x_case, int y_case, int index_navire, int index_case, TypeNavire *types_navire);

void ajouter_coup_navire(int x_case, int y_case, int **navire_coule, char **nom_navire, TypeNavire *types_navire);

int verifier_navire_coule(TypeNavire *types_navire, int index_navire);

Navire creer_navire(int taille_navire, int taille_plateau);

#endif
