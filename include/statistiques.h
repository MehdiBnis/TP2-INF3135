#ifndef STATISTIQUES_H
#define STATISTIQUES_H

/* Bibliothèques locales */

#include "util.h"

/* Bibliothèques standards */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Types struct */

// Structure pour les statistiques d'une partie
typedef struct stats {
   int total_coups;
   int nb_lettres_premier_navire;
   int total_coups_a_leau;
   int total_coups_deja_joue;
   int total_coups_touche;
   char dernier_navire_coule[20];
} Statistiques;

/* Prototypes des fonctions */

void initialisation_stats(Statistiques *stats);

void mise_a_jour_stats(Statistiques *stats, int navire_coule, int nb_joue, int nb_touche, int nb_deja_joue, char *nom_navire);

void sauvegarde_stats(Statistiques *stats, const char *nom_fichier);

#endif
