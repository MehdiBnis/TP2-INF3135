#include "test_statistiques.h"

void test_initialisation_stats() {
   Statistiques *stats = malloc(sizeof(Statistiques));
   initialisation_stats(stats);
   CU_ASSERT_EQUAL(stats->total_coups, 0);
   CU_ASSERT_EQUAL(stats->nb_lettres_premier_navire, 0);
   CU_ASSERT_EQUAL(stats->total_coups_a_leau, 0);
   CU_ASSERT_EQUAL(stats->total_coups_deja_joue, 0);
   CU_ASSERT_EQUAL(stats->total_coups_touche, 0);
   CU_ASSERT_STRING_EQUAL(stats->dernier_navire_coule, " ");

   free(stats);
}

void test_mise_a_jour_stats() {
   Statistiques *stats = malloc(sizeof(Statistiques));
   initialisation_stats(stats);
   mise_a_jour_stats(stats, 1, 5, 5, 0, "Porte-avions");

   CU_ASSERT_EQUAL(stats->total_coups, 5);
   CU_ASSERT_EQUAL(stats->total_coups_a_leau, 0);
   CU_ASSERT_EQUAL(stats->total_coups_deja_joue, 0);
   CU_ASSERT_EQUAL(stats->total_coups_touche, 5);
   CU_ASSERT_STRING_EQUAL(stats->dernier_navire_coule, "Porte-avions");

   free(stats);
}

int main_statistiques() {
   CU_initialize_registry();
   CU_pSuite suite = CU_add_suite("Suite de tests pour statistiques.c", NULL, NULL);
   CU_add_test(suite, "Test pour 'initialisation_stats'", test_initialisation_stats);
   CU_add_test(suite, "Test pour 'mise_a_jour_stats'", test_mise_a_jour_stats);

   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
