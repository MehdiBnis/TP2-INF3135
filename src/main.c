#include "jeu.h"
#include "util.h"

/**
 * Fonction main
 */

int main(int argc, char **argv) {
   char *fichier_stats = NULL;
   int avec_sauvegarde = 0;

   // Vérifie si les arguments supplémentaires sont valides
   if (argc != 1) {
      if (!verifier_arguments(argc, argv, &fichier_stats)) return 1;
      avec_sauvegarde = 1;
   }

   // Lance le jeu
   lancer_jeu(avec_sauvegarde, fichier_stats);
   // Mets fin au programme
   return 0;
}
