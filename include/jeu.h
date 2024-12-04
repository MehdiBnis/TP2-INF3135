#ifndef JEU_H
#define JEU_H

/* Bibliothèques locales */

#include "plateau.h"
#include "entree.h"
#include "navire.h"
#include "statistiques.h"

/* Bibliothèques standards */

#include <stdlib.h>

/* Prototypes des fonctions */

void affichage_resultat(int case_prop);

void modifier_valeurs(int **prop, char **grille, int *navire_coule, int case_prop, int case_plateau, int *nb_touche, int *nb_joue, int *nb_deja_joue, int x_case, int y_case, char *nom_navire, TypeNavire *types_navire);

int verifier_victoire(TypeNavire *types_navire);

void proposition_joueur(int **plateau, int **prop, char **grille, int *nb_touche, int *nb_joue, int *nb_deja_joue, TypeNavire *types_navire, Statistiques *stats, int taille_plateau);

void initialiser_jeu(int ***plateau, int ***prop, char ***grille, TypeNavire **types_navire, Statistiques **stats, int *taille_plateau);

void liberer_jeu(int **plateau, int **prop, char **grille, TypeNavire *types_navire, Statistiques *stats, int taille_plateau);

void lancer_jeu(int avec_sauvegarde, char *fichier_stats);

#endif
