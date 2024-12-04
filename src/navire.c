#include "navire.h"

/**
 * Fonction: 'positionner_case'
 *
 * Détermine la position de la première case d'un navire sur un plateau.
 *
 * @param x_case           Abscisse de la première case du navire
 * @param y_case           Ordonnée de la première case du navire
 * @param sens_navire      Sens du navire (0: haut, 1: droite, 2: bas, 3: gauche)
 * @param taille_navire    Taille du navire prédéfinie
 * @param taille_plateau   Taille du plateau entrée par l'utilisateur
 */

void positionner_case(int *x_case, int *y_case, int sens_navire, int taille_navire, int taille_plateau) {
   switch (sens_navire % 2) {
      case 0:   // Placer un navire dans les limites du plateau en vertical
         *x_case = nb_aleatoire(taille_plateau);
         *y_case = nb_aleatoire(taille_plateau - taille_navire);

         // Déplacer l'ordonnée de la première case vers le bas si le navire pointe vers le haut
         if (sens_navire == 0) {
            *y_case += (taille_navire - 1);
         }

         break;
      case 1:   // Placer un navire dans les limites du plateau en horizontal
         *x_case = nb_aleatoire(taille_plateau - taille_navire);
         *y_case = nb_aleatoire(taille_plateau);

         // Déplacer l'abscisse de la première case vers la droite si le navire pointe vers la gauche
         if (sens_navire == 3) {
            *x_case += (taille_navire - 1);
         }

         break;
   }
}

/**
 * Fonction: 'definir_noms'
 *
 * Assigne un nom à chaque navire.
 *
 * @param types_navire
 */

void definir_noms(TypeNavire *types_navire) {
   types_navire[0].nom = "Porte-avions";
   types_navire[1].nom = "Croiseur";
   types_navire[2].nom = "Contre-torpilleur";
   types_navire[3].nom = "Contre-torpilleur";
   types_navire[4].nom = "Torpilleur";
}

/**
 * Fonction: 'definir_tailles'
 *
 * Assigne une taille à chaque navire.
 *
 * @param types_navire
 */

void definir_tailles(TypeNavire *types_navire) {
   types_navire[0].taille = 5;
   types_navire[1].taille = 4;
   types_navire[2].taille = 3;
   types_navire[3].taille = 3;
   types_navire[4].taille = 2;
}

/**
 * Fonction: 'initialiser_positions"
 *
 * Initialise un tableau bi-dimensionnel pour la position des cases de chaque navire.
 *
 * @param types_navire
 */

void initialiser_positions(TypeNavire *types_navire) {
   // Allouer de l'espace pour les cases de chaque navire
   for (int i = 0; i < NB_NAVIRES; i++) {
      int taille_navire = types_navire[i].taille;
      types_navire[i].positions = malloc(taille_navire * sizeof(Case * ));
      // Allouer de l'espace pour les coordonnées de chaque case du navire
      for (int j = 0; j < taille_navire; j++) {
         types_navire[i].positions[j] = malloc(2 * sizeof(int));
      }
   }
}

/**
 * Fonction: 'initialiser_coups'
 *
 * Initialise le nombre de coups subis par chaque navire à 0.
 *
 * @param types_navire
 */

void initialiser_coups(TypeNavire *types_navire) {
   for (int i = 0; i < NB_NAVIRES; i++) {
      types_navire[i].coups_subis = 0;
   }
}

/**
 * Fonction: 'initialiser_types'
 *
 * Crée un tableau multidimensionnel contenant les informations de chaque navire du plateau.
 *
 * @param types_navire
 */

TypeNavire *initialiser_types() {
   // Allouer de l'espace pour la structure contenant les informations de chaque navire
   TypeNavire *types_navire = malloc(NB_NAVIRES * sizeof(TypeNavire));

   // Définir les noms des navires
   definir_noms(types_navire);
   //Définir les tailles des navires
   definir_tailles(types_navire);
   // Initialiser la position des cases des navires
   initialiser_positions(types_navire);
   // Initialiser le nombre de coups subis par les navires
   initialiser_coups(types_navire);

   return types_navire;
}

/**
 * Fonction: 'ajouter_position_navire'
 *
 * Ajoute une case d'un navire et ses coordonnées dans la structure.
 *
 * @param x_case         Ordonnée de la case
 * @param y_case         Abscisse de la case
 * @param index_navire   Index vers le navire
 * @param index_case     Index vers le tableau des coordonnées de la case
 * @param types_navire   Tableau des données des navires
 */

void ajouter_position_navire(int x_case, int y_case, int index_navire, int index_case, TypeNavire *types_navire) {
   types_navire[index_navire].positions[index_case]->x = x_case;
   types_navire[index_navire].positions[index_case]->y = y_case;
}

/**
 * Fonction: 'ajouter_coup_valide'
 *
 * Mets à jour la structure du type du navire pour indiquer un nouveau coup reçu.
 *
 * @param x_case         Abscisse de la case du navire
 * @param y_case         Ordonnée de la case du navire
 * @param navire_coule   Indique si le navire a coulé
 * @param nom_navire     Nom du navire
 * @param types_navire
 */

void ajouter_coup_navire(int x_case, int y_case, int **navire_coule, char **nom_navire, TypeNavire *types_navire) {
   for (int i = 0; i < NB_NAVIRES; i++) {
      int taille_navire = types_navire[i].taille;
      for (int j = 0; j < taille_navire; j++) {
         int x = types_navire[i].positions[j]->x;
         int y = types_navire[i].positions[j]->y;
         // Vétifier à quel navire appartient la case sélectionnée
         if (x_case == x && y_case == y) {
            // Mettre à jour les informations du navire
            types_navire[i].coups_subis++;
            strcpy(*nom_navire, types_navire[i].nom);
            **navire_coule = verifier_navire_coule(types_navire, i);
         }
      }
   }
}

/**
 * Fonction: 'verifier_navire_coule"
 *
 * Vérifie si le navire a coulé.
 *
 * @param types_navire
 * @param index_navire
 * @return
 */

int verifier_navire_coule(TypeNavire *types_navire, int index_navire) {
   int taille_navire = types_navire[index_navire].taille;
   int coups_navire = types_navire[index_navire].coups_subis;

   // Retourne 1 si la taille est égale aux coups subis et qu'il a donc coulé
   if (taille_navire == coups_navire) return 1;
   return 0;
}

/**
 * Fonction: 'liberer_types'
 *
 * Libère toute la mémoire allouée pour la création de 'types_navire'.
 *
 * @param types_navire
 */

void liberer_types(TypeNavire *types_navire) {
   // Libérer la mémoire allouée au nom, le nombre de coups subis, la taille et les cases
   for (int i = 0; i < NB_NAVIRES; i++) {
      // Libérer la mémoire allouée aux coordonnées de chaque case
      for (int j = 0; j < types_navire[i].taille; j++) {
         free(types_navire[i].positions[j]);
      }
      free(types_navire[i].positions);
   }
   free(types_navire);
}

/**
 * Fonction: 'creer_navire'
 *
 * Créer un navire à placer aléatoirement sur le plateau du jeu.
 *
 * @param taille           Taille du navire prédéfinie
 * @param taille_plateau   Taille du plateau entrée par l'utilisateur
 */

Navire creer_navire(int taille, int taille_plateau) {
   Navire navire;      // Initialiser un nouveau navire
   int sens = nb_aleatoire(4);   // Définir un sens aléatoire pour le navire (entre 0 et 3)
   int x, y;
   x = y = 0;

   // Définir la position de la première case du navire
   positionner_case(&x, &y, sens, taille, taille_plateau);

   // Définir les données du navire actuel
   navire.premiere_case.x = x;
   navire.premiere_case.y = y;
   navire.taille_navire = taille;
   navire.sens = sens;

   return navire;
}
