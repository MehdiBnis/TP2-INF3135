#include "plateau.h"

/**
 * Fonction 'changer_case'
 *
 * Change de case en fonction du sens du navire et d'un index donné.
 *
 * @param x_case   Abscisse de la case
 * @param y_case   Ordonnée de la case
 * @param sens     Sens du navire
 * @param index    Index donné
 */

void changer_case(int *x_case, int *y_case, int sens, int index) {
   switch (sens % 2) {
      case 0:   // Vertical
         (sens == 0) ? (*y_case -= index) : (*y_case += index);   // 0 : haut, 2 : bas
         break;
      case 1:   // Horizontal
         (sens == 1) ? (*x_case += index) : (*x_case -= index);   // 1 : droite, 3 : gauche
         break;
   }
}

/**
 * Fonction: 'est_valide'
 *
 * Vérifie si un navire peut être placé sur un plateau.
 *
 * @param plateau          Pointeur vers le tableau actuel
 * @param taille_plateau   Taille du plateau entrée par l'utilisateur
 * @param nav              Pointeur vers le navire actuel
 * @return                 0 si le navire en chevauche un autre, 1 sinon.
 */

int est_valide(int **plateau, int taille_plateau, Navire *nav) {
   // Récupérer les coordonnées et le sens du navire  
   int x = nav->premiere_case.x;
   int y = nav->premiere_case.y;
   int taille_navire = nav->taille_navire;
   int sens = nav->sens;

   for (int i = 0; i < taille_navire; i++) {
      int temp_x = x, temp_y = y;

      // Se déplacer sur une autre case du navire
      changer_case(&x, &y, sens, i);

      // Retourner 0 si la case du navire est hors des limites du plateau
      if (x < 0 || x >= taille_plateau || y < 0 || y >= taille_plateau) {
         x = temp_x;
         y = temp_y;
         return 0;
      }

      // Retourner 0 si la case du navire en chevauche un autre
      if (plateau[x][y] == OCCUPE) {
         x = temp_x;
         y = temp_y;
         return 0;
      }
      x = temp_x;
      y = temp_y;
   }
   return 1;
}

/**
 * Fonction: 'creer_plateau_vide'
 *
 * Crée un tableau entièrement vide en prenant compte de sa taille.
 *
 * @param taille_plateau   Taille du plateau entrée par l'utilisateur
 * @return                 Le plateau vide
 */

int **creer_plateau_vide(int taille_plateau) {
   // Allouer de l'espace pour le plateau (tableau de deux dimensions) 
   int **plateau;
   plateau = malloc(sizeof(int *) * taille_plateau);

   // Allouer de l'espace pour chaque rangée (tableau)
   for (int i = 0; i < taille_plateau; i++) {
      plateau[i] = malloc(sizeof(int) * taille_plateau);
   }

   // Donner la valeur VIDE (0) à chaque élément du plateau
   for (int i = 0; i < taille_plateau; i++) {
      for (int j = 0; j < taille_plateau; j++) {
         plateau[i][j] = VIDE;
      }
   }
   return plateau;
}

/**
 * Fonction: 'creer_grille_vide'
 *
 * Crée une grille vide (le plateau affiché à l'utilisateur).
 *
 * @param taille_plateau   Taille du plateau entrée par l'utilisateur
 * @return                 Une grille vide
 */

char **creer_grille_vide(int taille_plateau) {
   // Allouer de l'espace pour la grille (tableau de deux dimensions)
   char **grille;
   grille = malloc(sizeof(char *) * taille_plateau);

   // Allouer de l'espace pour chaque rangée (tableau)
   for (int i = 0; i < taille_plateau; i++) {
      grille[i] = malloc(taille_plateau);
   }

   // Donner la valeur EAU ('.') à chaque élément de la grille
   for (int i = 0; i < taille_plateau; i++) {
      for (int j = 0; j < taille_plateau; j++) {
         grille[i][j] = EAU;
      }
   }
   return grille;
}

/**
 * Fonction: 'initialisation_plateau'
 *
 * Initialise le plateau à l'aide d'un pointeur vers ce dernier et sa taille.
 *
 * @param plateau          Pointeur vers le tableau actuel
 * @param taille_plateau   Taille du plateau entrée par l'utilisateur
 */

void initialisation_plateau(int **plateau, int taille_plateau, TypeNavire *types_navire) {
   // Parcourir les cinq navires à placer sur le plateau
   for (int i = 0; i < NB_NAVIRES; i++) {
      int taille_navire = types_navire[i].taille;
      int placement_valide = 0;

      // Trouver un emplacement valide et placer le navire sur le plateau
      while (!placement_valide) {
         // Créer un navire et vérifier si sa position est occupée
         Navire navire = creer_navire(taille_navire, taille_plateau);
         int navire_valide = est_valide(plateau, taille_plateau, &navire);

         // Placer le navire sur le plateau
         if (navire_valide) {
            for (int j = 0; j < taille_navire; j++) {
               int x = navire.premiere_case.x;
               int y = navire.premiere_case.y;
               int sens = navire.sens;

               changer_case(&x, &y, sens, j);
               plateau[x][y] = OCCUPE;
               ajouter_position_navire(x, y, i, j, types_navire);
            }
            placement_valide = 1;
         }
      }
   }
}

/**
 * Fonction: 'modifier_grille'
 *
 * Modifie la grille du jeu selon le tir du joueur.
 *
 * @param x                Abscisse du tir
 * @param y                Ordonnée du tir
 * @param case_plateau     Valeur de la case du plateau (0: vide, 1: navire)
 * @param grille           Grille du jeu
 */

void modifier_grille(int x, int y, int case_plateau, char **grille) {
   switch (case_plateau) {
      case (VIDE):
         grille[x][y] = RATE;
         break;
      case (OCCUPE):
         grille[x][y] = TOUCHE;
         break;
   }
}

/**
 * Fonction: 'affichage_grille'
 *
 * Affiche la grille du jeu
 *
 * @param grille           Grille du jeu
 * @param taille_plateau   Taille du plateau
 */

void affichage_grille(char **grille, int taille_plateau) {
   for (int i = 0; i < taille_plateau; i++) {
      for (int j = 0; j < taille_plateau; j++) {
         printf("%c", grille[j][i]);
      }
      printf("\n");
   }
   printf("\n");
}

/**
 * Fonction: 'liberer_plateau'
 *
 * Libère la mémoire allouée pour un plateau.
 *
 * @param plateau          Pointeur vers le plateau actuel
 * @param taille_plateau   Taille du plateau actuel
 */

void liberer_plateau(int **plateau, int taille_plateau) {
   // Libérer la mémoire allouée pour chaque rangée du plateau
   for (int i = 0; i < taille_plateau; i++) {
      free(plateau[i]);
   }

   // Libérer la mémoire allouée au plateau
   free(plateau);
}

/**
 * Fonction: 'liberer_grille'
 *
 * Libère la mémoire allouée pour une grille..
 *
 * @param grille           Pointeur vers la grille actuelle
 * @param taille_plateau   Taille de la grille actuelle
 */

void liberer_grille(char **grille, int taille_plateau) {
   for (int i = 0; i < taille_plateau; i++) {
      free(grille[i]);
   }
   free(grille);
}

/**
 * Fonction: 'affichage_navire_coule'
 *
 * Affiche différemment les navires coulés (avec '/') des navires touchés (avec 'x').
 *
 * @param grille         Pointeur vers la grille actuelle
 * @param navire_coule   Indique si le navire est coulé
 * @param types_navire
 */

void affichage_navire_coule(char **grille, int navire_coule, TypeNavire *types_navire) {
   if (navire_coule) {
      for (int i = 0; i < NB_NAVIRES; i++) {
         for (int j = 0; j < types_navire[i].taille; j++) {
            if (types_navire[i].taille == types_navire[i].coups_subis) {
               int x = types_navire[i].positions[j]->x;
               int y = types_navire[i].positions[j]->y;
               grille[x][y] = COULE;
            }
         }
      }
   }
}
