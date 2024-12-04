#include "util.h"

/**
 * Fonction: 'init_nb_aleatoire'
 *
 * Initie une nouvelle génération pour un nombre aléatoire.
 *
 */

void init_nb_aleatoire() {
   srand(time(NULL));
}

/**
 * Fonction: 'nb_aleatoire'
 *
 * Retourne un nombre entier aléatoire.
 *
 * @param  max   Valeur maximale du nombre entier
 * @return       Entier aléatoire
 */

int nb_aleatoire(int max) {
   return (rand() % max);
}

/**
* Fonction: 'compte_lettres_uniques'
 *
 * Compte le nombre de lettres sans doublons d'une chaîne de caractères.
 *
 * @param chaine   Chaîne de caractères
 * @return         Nombre de lettres sans doublons de la chaîne
*/

int compte_lettres_uniques(const char *chaine) {
   bool lettres[26] = {false};   // Valeur de vérité assignée à chaque lettre de l'alphabet
   int index, compte = 0;

   // Vérifier chaque caractère de la chaîne
   while (*chaine) {
      if (isalpha(*chaine)) {
         index = tolower(*chaine) - 'a';   // Index assigné à la position de la lettre dans l'alphabet
         lettres[index] = true;
      }
      chaine++;
   }

   // Compter les lettres uniques de la chaîne
   for (int i = 0; i < 26; i++) {
      if (lettres[i]) {
         compte++;
      }
   }

   return compte;
}

/**
 * Fonction: 'verifier_arguments'
 *
 * Valide les arguments si argc est supérieur à 1.
 *
 * @param nb_args
 * @param args
 * @param fichier_stats
 * @return
 */

int verifier_arguments(int nb_args, char **args, char **fichier_stats) {
   if (nb_args > 3) {
      // Retourner une erreur si l'utilisateur entre plus de deux arguments
      fprintf(stderr,
              "\nErreur:"
              "\n- Pour simplement exécuter ce logiciel, veuillez entrer \"./bataille_navale\" sur la console."
              "\n- Pour écrire les statistiques de la partie sur un fichier texte, veuillez entrer \"/.bataille_navale -S (nomdufichier.txt)\""
              "\n"
      );
      return 0;
   } else if (nb_args >= 2) {
      if (strcmp(args[1], "-S") != 0) {
         // Retourner une erreur si le premier argument n'est pas '-S'
         fprintf(stderr, "\nErreur: Argument invalide.\n");
         return 0;
      } else if (strcmp(args[1], "-S") == 0 && nb_args == 2) {
         // Retourner une erreur si l'utilisateur entre l'option -S sans préciser de fichier de sortie
         fprintf(stderr, "\nErreur: Veuillez entrer un fichier de sortie.\n");
         return 0;
      }
   }
   // Enregistrer le nom du fichier de sortie
   *fichier_stats = args[2];
   return 1;
}

/**
 * Fonction 'est_nombre'
 *
 * Vérifie que la chaîne de caractères de contient que des valeurs numériques.
 *
 * @param chaine
 * @return
 */

int est_nombre(char *chaine) {
   // Retourner une erreur si la chaîne est vide
   if (*chaine == '\n') return 0;

   // Retourner une erreur si la chaîne contient des valeurs non-numériques
   while (*chaine != '\n') {
      if (!isdigit((unsigned char) *chaine)) {
         return 0;
      }
      chaine++;
   }

   return 1;
}