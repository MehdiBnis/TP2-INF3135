#ifndef UTIL_H
#define UTIL_H

/* Bibliothèques standards */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

/* Prototypes des fonctions */

void init_nb_aleatoire();

int nb_aleatoire(int max);

int compte_lettres_uniques(const char *chaine);

int verifier_arguments (int nb_args, char **args, char **fichier_stats);

int est_nombre(char *chaine);

#endif
