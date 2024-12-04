#include "test_entree.h"

void test_verifier_position_valide1() {
   int taille_plateau = 10;
   // Cas où la position est valide
   int x_valide = 5, y_valide = 5;
   CU_ASSERT_TRUE(verifier_position(x_valide, y_valide, taille_plateau));
}

void test_verifier_position_valide2() {
   int taille_plateau = 10;
   // Cas où la position est valide
   int x_limite = 10, y_limite = 10;
   CU_ASSERT_TRUE(verifier_position(x_limite, y_limite, taille_plateau));
}

void test_verifier_position_invalide_x() {
   int taille_plateau = 10;
   // Cas où x est hors du plateau
   int x_invalide = 0, y_valide = 5;
   CU_ASSERT_FALSE(verifier_position(x_invalide, y_valide, taille_plateau));
}

void test_verifier_position_invalide_y() {
   int taille_plateau = 10;
   // Cas où y est hors du plateau
   int x_valide = 5, y_invalide = 0;
   CU_ASSERT_FALSE(verifier_position(x_valide, y_invalide, taille_plateau));
}

void test_verifier_position_invalide_xy() {
   int taille_plateau = 10;
   // Cas où x et y sont hors du plateau
   int x_invalide = 11, y_invalide = 11;
   CU_ASSERT_FALSE(verifier_position(x_invalide, y_invalide, taille_plateau));
}

int main_entree() {
   CU_initialize_registry();
   CU_pSuite suite = CU_add_suite("Suite de tests pour entree.c", NULL, NULL);
   CU_add_test(suite, "Test valide 1 de 'verifier_position_valide'", test_verifier_position_valide1);
   CU_add_test(suite, "Test valide 2 de 'verifier_position_valide'", test_verifier_position_valide2);
   CU_add_test(suite, "Test de 'verifier_position_valide' avec x invalide", test_verifier_position_invalide_x);
   CU_add_test(suite, "Test de 'verifier_position_valide' avec y invalide", test_verifier_position_invalide_y);
   CU_add_test(suite, "Test de 'verifier_position_valide' avec x et y invalides", test_verifier_position_invalide_xy);

   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}