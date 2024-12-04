#include "test_plateau.h"

void test_creer_plateau_vide() {
   int taille_plateau = 10;
   int **plateau = creer_plateau_vide(taille_plateau);

   CU_ASSERT_PTR_NOT_NULL(plateau);

   // Vérifier si toutes les cases du plateau sont initialisées à VIDE
   for (int i = 0; i < taille_plateau; ++i) {
      for (int j = 0; j < taille_plateau; ++j) {
         CU_ASSERT_EQUAL(plateau[i][j], VIDE);
      }
   }
   // Libération de la mémoire allouée pour le plateau
   liberer_plateau(plateau, taille_plateau);
}

void test_changer_case() {
   int x = 5, y = 5;
   int sens = 0;
   changer_case(&x, &y, sens, 1); // Vers le haut

   CU_ASSERT_EQUAL(x, 5);
   CU_ASSERT_EQUAL(y, 4);
}

void test_est_valide() {
   int taille_plateau = 10;
   int **plateau = creer_plateau_vide(taille_plateau);
   Navire navire;
   navire.sens = 0;
   navire.taille_navire = 3;
   navire.premiere_case.x = 5;
   navire.premiere_case.y = 5;

   int resultat = est_valide(plateau, taille_plateau, &navire);
   CU_ASSERT_EQUAL(resultat, 1);

   liberer_plateau(plateau, taille_plateau);
}

void test_modifier_grille() {
   int taille_plateau = 10;
   char **grille = creer_grille_vide(taille_plateau);

   modifier_grille(5, 5, grille[5][5], grille);

   CU_ASSERT_TRUE(grille[5][5] = TOUCHE || grille[5][5] == RATE);

   liberer_grille(grille, taille_plateau);
}

int main_plateau() {
   CU_initialize_registry();
   CU_pSuite suite = CU_add_suite("Suite de tests pour plateau.c", NULL, NULL);
   CU_add_test(suite, "Test de 'changer_case'", test_changer_case);
   CU_add_test(suite, "Test de 'est_valide'", test_est_valide);
   CU_add_test(suite, "Test de 'modifier_grille'", test_modifier_grille);

   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
