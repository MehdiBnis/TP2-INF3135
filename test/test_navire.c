#include "test_navire.h"

void test_positionner_case() {
   int x_case = 0, y_case = 0;
   int sens_navire = 1; // Testons avec le sens à droite
   int taille_navire = 3;
   int taille_plateau = 10;

   positionner_case(&x_case, &y_case, sens_navire, taille_navire, taille_plateau);

   /* Vérifier que la position est dans les limites du plateau */
   CU_ASSERT(x_case >= 0 && x_case < taille_plateau);
   CU_ASSERT(y_case >= 0 && y_case <= (taille_plateau - taille_navire));
}

void test_ajouter_position_navire() {
   TypeNavire *types_navire = initialiser_types();
   ajouter_position_navire(2, 3, 0, 0, types_navire);

   // Vérifier que la position a été ajoutée
   CU_ASSERT_PTR_NOT_NULL(types_navire[0].positions);
   CU_ASSERT_EQUAL(types_navire[0].positions[0]->x, 2);
   CU_ASSERT_EQUAL(types_navire[0].positions[0]->y, 3);

   // Libérer la mémoire allouée
   liberer_types(types_navire);
}

void test_verifier_navire_coule(void) {
   TypeNavire *types_navire = initialiser_types();

   // Définir un navire coulé
   types_navire[0].coups_subis = types_navire[0].taille;

   CU_ASSERT_TRUE(verifier_navire_coule(types_navire, 0));

   // Définir un navire non-coulé
   types_navire[1].coups_subis = types_navire[1].taille - 1;

   CU_ASSERT_FALSE(verifier_navire_coule(types_navire, 1));

   // Libérer la mémoire allouée
   liberer_types(types_navire);
}

int main_navire() {
   CU_initialize_registry();
   CU_pSuite suite = CU_add_suite("Suite de tests pour navire.c", NULL, NULL);
   CU_add_test(suite, "Test de 'positionner_case'", test_positionner_case);
   CU_add_test(suite, "Test de 'ajouter_position_navire'", test_ajouter_position_navire);
   CU_add_test(suite, "Test de 'verifier_navire_coule'", test_verifier_navire_coule);

   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}