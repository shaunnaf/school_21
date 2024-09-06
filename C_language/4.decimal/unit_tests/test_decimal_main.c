#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "test_decimal.h"

static int run_test_suite(Suite *test_suite) {
  int number_failed = 0;
  SRunner *sr = NULL;

  sr = srunner_create(test_suite);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed);
}

int main(void) {
  int number_failed = 0;
  Suite *suite_array[] = {suite_truncate(),
                          suite_from_decimal_to_int(),
                          suite_from_decimal_to_float(),
                          suite_from_int_to_decimal(),
                          suite_from_float_to_decimal(),

                          suite_add_test(),
                          suite_sub_test(),
                          suite_div_test(),
                          suite_mul_test(),
                          suite_round(),
                          suite_floor(),
                          suite_negate(),
                          suite_equal_test(),
                          suite_greate_equal_test(),
                          suite_greater_test(),
                          suite_less_equal_test(),
                          suite_less_test(),
                          suite_not_equal_test(),

                          NULL};

  for (size_t i = 0; suite_array[i]; ++i) {
    number_failed += run_test_suite(suite_array[i]);
  }
  printf("Auxiliary functions\n");

  return (number_failed ? EXIT_FAILURE : EXIT_SUCCESS);
}