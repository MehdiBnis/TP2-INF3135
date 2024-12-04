#include "jeu.h"

/**
 * Fonction 'affichage_resultat'
 *
 * Affiche le résultat du tir du joueur.
 *
 * @param case_prop
 */

void affichage_resultat(int case_prop) {
   switch (case_prop) {
      case (PAS_DE_NAVIRE):
         printf("Râté !\n\n");
         break;
      case (DEJA_JOUE):
         printf("Cette case a déjà été jouée.\n\n");
         break;
      case (NAVIRE):
         printf("Touché !\n\n");
         break;
      default:
         break;
   }
}

/**
 * Fonction 'modifier_valeurs'
 *
 * Modifie les valeurs de la partie après un coup.
 *
 *
 * @param prop
 * @param grille
 * @param navire_coule
 * @param case_prop
 * @param case_plateau
 * @param nb_touche
 * @param nb_joue
 * @param nb_deja_joue
 * @param x_case
 * @param y_case
 * @param nom_navire
 * @param types_navire
 */

void modifier_valeurs(int **prop, char **grille, int *navire_coule, int case_prop, int case_plateau, int *nb_touche,
                      int *nb_joue, int *nb_deja_joue, int x_case, int y_case, char *nom_navire,
                      TypeNavire *types_navire) {
   if (case_prop != DEJA_JOUE) {
      prop[x_case][y_case] = DEJA_JOUE;
      if (case_plateau == OCCUPE) {
         (*nb_touche)++;
         ajouter_coup_navire(x_case, y_case, &navire_coule, &nom_navire, types_navire);
      }
      modifier_grille(x_case, y_case, case_plateau, grille);
   } else {
      (*nb_deja_joue)++;
   }
   (*nb_joue)++;
}

/**
 * Fonction: 'verifier_victoire'
 *
 * Vérifie si tous les navires ont été coulés (victoire).
 *
 * @param    types_navire
 * @return   1 si tous les navires ont coulé, 0 sinon.
 */

int verifier_victoire(TypeNavire *types_navire) {
   for (int i = 0; i < NB_NAVIRES; i++) {
      if (!verifier_navire_coule(types_navire, i)) {
         return 0;
      }
   }
   return 1;
}

/**
 * Fonction 'proposition_joueur'
 *
 * Rassemble les données de jeu et les entrées de l'utilisateur jusqu'à la victoire.
 *
 * @param plateau
 * @param prop
 * @param grille
 * @param nb_touche
 * @param nb_joue
 * @param nb_deja_joue
 * @param types_navire
 * @param stats
 * @param taille_plateau
 */

void proposition_joueur(int **plateau, int **prop, char **grille, int *nb_touche, int *nb_joue, int *nb_deja_joue,
                        TypeNavire *types_navire, Statistiques *stats, int taille_plateau) {
   int victoire = 0;
   while (!victoire) {
      int *position_tir = entree_tir(taille_plateau);
      int x = position_tir[0] - 1, y = position_tir[1] - 1;
      free(position_tir);
      static char nom_navire[30];
      int case_prop = prop[x][y], case_plateau = plateau[x][y];
      int navire_coule = 0;

      modifier_valeurs(prop, grille, &navire_coule, case_prop, case_plateau, nb_touche, nb_joue, nb_deja_joue, x, y,
                       nom_navire, types_navire);
      affichage_navire_coule(grille, navire_coule, types_navire);
      mise_a_jour_stats(stats, navire_coule, *nb_joue, *nb_touche, *nb_deja_joue, nom_navire);

      affichage_grille(grille, taille_plateau);
      affichage_resultat(case_prop);

      victoire = verifier_victoire(types_navire);
   }
   printf("Bravo !! Vous avez gagné en %d coups.\n", *nb_joue);
}

/**
 * Fonction: 'initialiser_jeu'
 *
 * Initialise toutes les valeurs des éléments du jeu.
 *
 * @param plateau
 * @param prop
 * @param grille
 * @param types_navire
 * @param stats
 * @param taille_plateau
 */

void initialiser_jeu(int ***plateau, int ***prop, char ***grille, TypeNavire **types_navire, Statistiques **stats,
                     int *taille_plateau) {
   *types_navire = initialiser_types();
   *taille_plateau = entree_taille_plateau();

   *plateau = creer_plateau_vide(*taille_plateau);
   *prop = creer_plateau_vide(*taille_plateau);
   *grille = creer_grille_vide(*taille_plateau);

   affichage_grille(*grille, *taille_plateau);

   initialisation_stats(*stats);
   initialisation_plateau(*plateau, *taille_plateau, *types_navire);

   for (int i = 0; i < *taille_plateau; i++) {
      for (int j = 0; j < *taille_plateau; j++) {
         (*prop)[i][j] = (*plateau)[i][j];
      }
   }
}

/**
 * Fonction: 'liberer_jeu'
 *
 * Libère l'espace alloué aux éléments du programme.
 *
 * @param plateau
 * @param prop
 * @param grille
 * @param types_navire
 * @param stats
 * @param taille_plateau
 */

void liberer_jeu(int **plateau, int **prop, char **grille, TypeNavire *types_navire, Statistiques *stats,
                 int taille_plateau) {
   liberer_plateau(plateau, taille_plateau);
   liberer_plateau(prop, taille_plateau);
   liberer_grille(grille, taille_plateau);
   liberer_types(types_navire);
   free(stats);
}

/**
 * Fonction: 'lancer_jeu'
 *
 * Enregistre dans un fichier texte les statistiques de la partie si l'utilisateur l'a précisé.
 *
 * @param avec_sauvegarde
 * @param fichier_stats
 */

void lancer_jeu(int avec_sauvegarde, char *fichier_stats) {
   Statistiques *stats = malloc(sizeof(Statistiques));
   TypeNavire *types_navire;
   int taille_plateau = 0, nb_touche = 0, nb_joue = 0, nb_deja_joue = 0;
   int **plateau = NULL, **prop = NULL;
   char **grille = NULL;

   initialiser_jeu(&plateau, &prop, &grille, &types_navire, &stats, &taille_plateau);
   proposition_joueur(plateau, prop, grille, &nb_touche, &nb_joue, &nb_deja_joue, types_navire, stats, taille_plateau);
   if (avec_sauvegarde) sauvegarde_stats(stats, fichier_stats);
   liberer_jeu(plateau, prop, grille, types_navire, stats, taille_plateau);
}
