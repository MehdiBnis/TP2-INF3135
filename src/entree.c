#include "entree.h"

/**
 * Fonction: 'entree_taille_plateau'
 *
 * Demande à l'utilisateur d'entrer la taille du plateau du jeu et la retourne.
 *
 * @return taille_plateau   Taille du plateau
 */

int entree_taille_plateau() {
   int taille_plateau = 0;
   int taille_valide = 0;

   // Entrer la taille du plateau
   while (!taille_valide) {
      char entree[100] = "";

      while (!est_nombre(entree)) {
         printf("Veuillez entrer la taille du plateau (entre 6 et 100): ");
         fgets(entree, sizeof(entree), stdin);
         if (!est_nombre(entree)) printf("Format invalide, veuillez entrer une valeur numérique.\n\n");
      }

      entree[sizeof(entree) - 1] = '\0';
      taille_plateau = atoi(entree);

      taille_valide = ((taille_plateau >= MIN_TAILLE_PLATEAU) && (taille_plateau <= MAX_TAILLE_PLATEAU));

      // Redemander l'entrée tant que la taille n'est pas valide
      if (!taille_valide) {
         printf("Taille invalide.\n\n");
      }
   }
   printf("\n");
   return taille_plateau;
}

/**
 * Fonction: 'verifier_position'
 *
 * Vérifie que la position d'un tir est dans les limites du plateau.
 *
 * @param x                Abscisse du tir
 * @param y                Ordonnée du tir
 * @param taille_plateau   Taille du plateau
 * @return                 0 si le tir est hors du plateau, 1 sinon
 */

int verifier_position(int x, int y, int taille_plateau) {
   int x_valide = ((x - 1) >= 0 && (x - 1) < taille_plateau);
   int y_valide = ((y - 1) >= 0 && (y - 1) < taille_plateau);
   int valide = (x_valide && y_valide);

   if (!valide) {
      printf("Position invalide.\n\n");
   }

   return valide;
}

/**
 * Fonction: 'entree_tir'
 *
 * Demande à l'utilisateur d'entrer les coordonnées du tir et les retourne.
 *
 * @param taille_plateau   Taille du plateau
 * @return position_tir    Tableau contenant les coordonnées du tir ({x, y})
 */

int *entree_tir(int taille_plateau) {
   // Allouer de l'espace pour un tableau contenant deux entiers
   int *position_tir;
   position_tir = malloc(2 * sizeof(int));

   int position_valide = 0;

   while (!position_valide) {
      char entree_x[100] = "";
      char entree_y[100] = "";
      // Entrer et définir l'abscisse du tir
      while (!est_nombre(entree_x)) {
         printf("Veuillez entrer l'abscisse (x) du tir: ");
         fgets(entree_x, sizeof(entree_x), stdin);
         if (!est_nombre(entree_x)) printf("Abscisse invalide, veuillez entrer une valeur numérique.\n\n");
      }

      entree_x[sizeof(entree_x) - 1] = '\0';
      position_tir[0] = atoi(entree_x);

      while (!est_nombre(entree_y)) {
         printf("Veuillez entrer l'ordonnée (y) du tir: ");
         fgets(entree_y, sizeof(entree_y), stdin);
         if (!est_nombre(entree_y)) printf("Ordonnée invalide, veuillez entrer une valeur numérique.\n\n");
      }

      entree_y[sizeof(entree_y) - 1] = '\0';
      position_tir[1] = atoi(entree_y);

      position_valide = ((verifier_position(position_tir[0], position_tir[1], taille_plateau)));
   }
   printf("\n");
   return position_tir;
}


