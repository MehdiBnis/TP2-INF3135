#include "statistiques.h"

/**
 * Fonction: 'initialisation_plateau'
 *
 * Initialise les valeurs des statistiques de la partie
 *
 * @param stats
 */

void initialisation_stats(Statistiques *stats) {
   stats->total_coups = 0;
   stats->nb_lettres_premier_navire = 0;
   stats->total_coups_a_leau = 0;
   stats->total_coups_deja_joue = 0;
   stats->total_coups_touche = 0;
   strcpy(stats->dernier_navire_coule, " ");
}

/**
 * Fonction: 'mise_a_jour_stats'
 *
 * Mets à jour les statistiques de la partie.
 *
 * @param stats
 * @param navire_coule
 * @param nb_joue
 * @param nb_touche
 * @param nb_deja_joue
 * @param nom_navire
 */

void mise_a_jour_stats(Statistiques *stats, int navire_coule, int nb_joue, int nb_touche, int nb_deja_joue,
                       char *nom_navire) {
   stats->total_coups = nb_joue;
   if (nb_touche == 1) stats->nb_lettres_premier_navire = compte_lettres_uniques(nom_navire);
   stats->total_coups_a_leau = nb_joue - nb_touche - nb_deja_joue;
   stats->total_coups_deja_joue = nb_deja_joue;
   stats->total_coups_touche = nb_touche;
   if (navire_coule) strcpy(stats->dernier_navire_coule, nom_navire);
}

/**
 * Fonction: 'sauvegarde_stats'
 *
 * Sauvegarde dans un fichier texte les statistiques de la partie quand l'option '-S (fichier)' est utilisée à l'exécution.
 *
 * @param stats
 * @param nom_fichier
 */

void sauvegarde_stats(Statistiques *stats, const char *nom_fichier) {
   FILE *fichier_sortie = fopen(nom_fichier, "w");

   fprintf(fichier_sortie, "Total des coups: %d\n", stats->total_coups);
   fprintf(fichier_sortie, "Nombre de lettres sans doublon du nom du premier navire touché: %d\n",
           stats->nb_lettres_premier_navire);
   fprintf(fichier_sortie, "Total de coups à l'eau: %d\n", stats->total_coups_a_leau);
   fprintf(fichier_sortie, "Total de coups déja joués: %d\n", stats->total_coups_deja_joue);
   fprintf(fichier_sortie, "Total de coups touchés: %d\n", stats->total_coups_touche);
   fprintf(fichier_sortie, "Nom du dernier navire coulé: %s\n", stats->dernier_navire_coule);
}
