#ifndef ENTREE_H
#define ENTREE_H

/* Bibliothèques locales */

#include "plateau.h"   // Accès aux constantes pour la taille du plateau
#include "util.h"

/* Bibliothèques standards */

#include <stdio.h>
#include <stdlib.h>

/* Prototypes des fonctions */

int entree_taille_plateau();

int verifier_position(int x, int y, int taille_plateau);

int *entree_tir(int taille_plateau);

#endif
