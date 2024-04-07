#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_matrix.h"

START_TEST(s21_create_matrix_test) {
  matrix_t m;
  ck_assert_int_eq(s21_create_matrix(0, 1, &m), 1);
  s21_create_matrix(4, 4, &m);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_int_eq(m.matrix[i][j], 0);
    }
  }
}
END_TEST

START_TEST(s21_remove_matrix_test) {
  matrix_t m;
  s21_create_matrix(3, 3, &m);
  s21_remove_matrix(&m);
  ck_assert_int_eq(0, m.rows);
  ck_assert_int_eq(0, m.columns);
  ck_assert_ptr_null(m.matrix);
}
END_TEST

START_TEST(s21_eq_matrix_test) {
  matrix_t m1, m2;
  s21_create_matrix(3, 3, &m1);
  s21_create_matrix(3, 3, &m2);
  m1.matrix[0][0] = m2.matrix[0][0] = 1;
  m1.matrix[0][1] = m2.matrix[0][1] = 2.34;
  m1.matrix[0][2] = m2.matrix[0][2] = 3.1234567;
  m1.matrix[1][0] = m2.matrix[1][0] = 4.12345678;
  m1.matrix[1][1] = m2.matrix[1][1] = -432;
  m1.matrix[1][2] = 32.4232424244;
  m2.matrix[1][2] = 32.4232424243;
  m1.matrix[2][0] = m2.matrix[2][0] = 0;
  m1.matrix[2][1] = m2.matrix[2][1] = 123456789;
  m1.matrix[2][2] = m2.matrix[2][2] = 98;
  ck_assert_int_eq(s21_eq_matrix(&m1, &m2), 1);
  m2.matrix[1][0] = 4.12345679;
  ck_assert_int_eq(s21_eq_matrix(&m1, &m2), 1);
  m2.matrix[0][2] = 4.1234568;
  ck_assert_int_eq(s21_eq_matrix(&m1, &m2), 0);
}
END_TEST

START_TEST(s21_sum_matrix_test) {
  matrix_t m1, m2, result;
  m1.rows = -1;
  m1.columns = 3;
  s21_create_matrix(3, 3, &m2);
  ck_assert_int_eq(s21_sum_matrix(&m1, &m2, &result), 1);
  s21_create_matrix(3, 3, &m1);
  m2.columns = 0;
  ck_assert_int_eq(s21_sum_matrix(&m1, &m2, &result), 1);
  m2.columns = 2;
  ck_assert_int_eq(s21_sum_matrix(&m1, &m2, &result), 2);
  m2.columns = 3;
  m1.matrix[0][0] = 1;
  m2.matrix[0][0] = -1;
  m1.matrix[0][1] = m2.matrix[0][1] = 2.34;
  m1.matrix[0][2] = m2.matrix[0][2] = 3.1234567;
  m1.matrix[1][0] = m2.matrix[1][0] = 4.12345678;
  m1.matrix[1][1] = m2.matrix[1][1] = -432;
  s21_sum_matrix(&m1, &m2, &result);
  ck_assert_double_eq(result.matrix[0][0], 0);
  ck_assert_double_eq(result.matrix[0][1], 4.68);
  ck_assert_double_eq(result.matrix[0][2], 6.2469134);
  ck_assert_double_eq(result.matrix[1][0], 8.24691356);
  ck_assert_double_eq(result.matrix[1][1], -864);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&result);
  s21_create_matrix(3, 2, &m1);
  s21_create_matrix(3, 2, &m2);
  m1.matrix[0][0] = 1;
  m2.matrix[0][0] = -1;
  m1.matrix[0][1] = m2.matrix[0][1] = 2.34;
  m1.matrix[1][0] = m2.matrix[1][0] = 4.12345678;
  m1.matrix[1][1] = m2.matrix[1][1] = -432;
  m1.matrix[2][0] = m2.matrix[2][0] = 4;
  m1.matrix[2][1] = m2.matrix[2][1] = 4;
  s21_sum_matrix(&m1, &m2, &result);
  ck_assert_double_eq(result.matrix[0][0], 0);
  ck_assert_double_eq(result.matrix[0][1], 4.68);
  ck_assert_double_eq(result.matrix[1][0], 8.24691356);
  ck_assert_double_eq(result.matrix[1][1], -864);
  ck_assert_double_eq(result.matrix[2][0], 8);
  ck_assert_double_eq(result.matrix[2][1], 8);
}
END_TEST

START_TEST(s21_sub_matrix_test) {
  matrix_t m1, m2, result;
  m1.rows = -1;
  m1.columns = 3;
  s21_create_matrix(3, 3, &m2);
  s21_create_matrix(3, 3, &result);
  ck_assert_int_eq(s21_sub_matrix(&m1, &m2, &result), 1);
  m1.rows = 1;
  ck_assert_int_eq(s21_sub_matrix(&m1, &m2, &result), 2);
  s21_create_matrix(3, 3, &m1);
  m1.matrix[0][0] = 1;
  m2.matrix[0][0] = -1;
  m1.matrix[0][1] = m2.matrix[0][1] = 2.34;
  m1.matrix[0][2] = m2.matrix[0][2] = 3.1234567;
  m1.matrix[1][0] = m2.matrix[1][0] = 4.12345678;
  m1.matrix[1][1] = m2.matrix[1][1] = -432;
  s21_sub_matrix(&m1, &m2, &result);
  ck_assert_double_eq(result.matrix[0][0], 2);
  ck_assert_double_eq(result.matrix[0][1], 0);
  ck_assert_double_eq(result.matrix[0][2], 0);
  ck_assert_double_eq(result.matrix[1][0], 0);
  ck_assert_double_eq(result.matrix[1][1], 0);
}
END_TEST

START_TEST(s21_mult_number_test) {
  matrix_t m1, result;
  m1.rows = -1;
  m1.columns = 3;
  double number = 2;
  ck_assert_int_eq(1, s21_mult_number(&m1, number, &result));
}
END_TEST

START_TEST(s21_mult_matrix_test) {
  matrix_t m1, m2, result;
  m1.rows = -1;
  m1.columns = 3;
  s21_create_matrix(2, 3, &m2);
  s21_create_matrix(3, 3, &result);
  ck_assert_int_eq(s21_mult_matrix(&m1, &m2, &result), 1);
  s21_create_matrix(1, 6, &m1);
  ck_assert_int_eq(s21_mult_matrix(&m1, &m2, &result), 2);
  s21_remove_matrix(&m1);
  s21_create_matrix(3, 2, &m1);
  m1.matrix[0][0] = 1;
  m1.matrix[0][1] = 4;
  m1.matrix[1][0] = 2;
  m1.matrix[1][1] = 5;
  m1.matrix[2][0] = 3;
  m1.matrix[2][1] = 6;
  m2.matrix[0][0] = 1;
  m2.matrix[0][1] = -1;
  m2.matrix[0][2] = 1;
  m2.matrix[1][0] = 2;
  m2.matrix[1][1] = 3;
  m2.matrix[1][2] = 4;
  s21_mult_matrix(&m1, &m2, &result);
  ck_assert_double_eq(result.matrix[0][0], 9);
  ck_assert_double_eq(result.matrix[0][1], 11);
  ck_assert_double_eq(result.matrix[0][2], 17);
  ck_assert_double_eq(result.matrix[1][0], 12);
  ck_assert_double_eq(result.matrix[1][1], 13);
  ck_assert_double_eq(result.matrix[1][2], 22);
  ck_assert_double_eq(result.matrix[2][0], 15);
  ck_assert_double_eq(result.matrix[2][1], 15);
  ck_assert_double_eq(result.matrix[2][2], 27);
}
END_TEST

START_TEST(s21_transpose_test) {
  matrix_t m1, result;
  m1.rows = 0;
  ck_assert_int_eq(s21_transpose(&m1, &result), 1);
  s21_create_matrix(3, 2, &m1);
  s21_create_matrix(2, 3, &result);
  m1.matrix[0][0] = 1;
  m1.matrix[0][1] = 4;
  m1.matrix[1][0] = 2;
  m1.matrix[1][1] = 5;
  m1.matrix[2][0] = 3;
  m1.matrix[2][1] = 6;
  s21_transpose(&m1, &result);
  ck_assert_double_eq(result.matrix[0][0], 1);
  ck_assert_double_eq(result.matrix[0][1], 2);
  ck_assert_double_eq(result.matrix[0][2], 3);
  ck_assert_double_eq(result.matrix[1][0], 4);
  ck_assert_double_eq(result.matrix[1][1], 5);
  ck_assert_double_eq(result.matrix[1][2], 6);
}
END_TEST

START_TEST(s21_calc_complements_test) {
  matrix_t m1, result;
  m1.rows = -1;
  ck_assert_int_eq(s21_calc_complements(&m1, &result), 1);
  s21_create_matrix(3, 2, &m1);
  s21_create_matrix(3, 3, &result);
  ck_assert_int_eq(s21_calc_complements(&m1, &result), 2);
  s21_remove_matrix(&m1);
  s21_create_matrix(3, 3, &m1);
  m1.matrix[0][0] = 1;
  m1.matrix[0][1] = 2;
  m1.matrix[0][2] = 3;
  m1.matrix[1][0] = 0;
  m1.matrix[1][1] = 4;
  m1.matrix[1][2] = 2;
  m1.matrix[2][0] = 5;
  m1.matrix[2][1] = 2;
  m1.matrix[2][2] = 1;
  s21_calc_complements(&m1, &result);
  ck_assert_double_eq(result.matrix[0][0], 0);
  ck_assert_double_eq(result.matrix[0][1], 10);
  ck_assert_double_eq(result.matrix[0][2], -20);
  ck_assert_double_eq(result.matrix[1][0], 4);
  ck_assert_double_eq(result.matrix[1][1], -14);
  ck_assert_double_eq(result.matrix[1][2], 8);
  ck_assert_double_eq(result.matrix[2][0], -8);
  ck_assert_double_eq(result.matrix[2][1], -2);
  ck_assert_double_eq(result.matrix[2][2], 4);
}
END_TEST

START_TEST(s21_determinant_test) {
  matrix_t m1;
  double result;
  m1.rows = -1;
  ck_assert_int_eq(s21_determinant(&m1, &result), 1);
  s21_create_matrix(3, 2, &m1);
  ck_assert_int_eq(s21_determinant(&m1, &result), 2);
  s21_remove_matrix(&m1);
  s21_create_matrix(1, 1, &m1);
  m1.matrix[0][0] = 4;
  s21_determinant(&m1, &result);
  ck_assert_double_eq(result, 4);
  s21_remove_matrix(&m1);
  s21_create_matrix(3, 3, &m1);
  m1.matrix[0][0] = 1;
  m1.matrix[0][1] = 2;
  m1.matrix[0][2] = 3;
  m1.matrix[1][0] = 4;
  m1.matrix[1][1] = 5;
  m1.matrix[1][2] = 6;
  m1.matrix[2][0] = 7;
  m1.matrix[2][1] = 8;
  m1.matrix[2][2] = 9;
  s21_determinant(&m1, &result);
  ck_assert_double_eq(result, 0);
}
END_TEST

START_TEST(s21_inverse_matrix_test) {
  matrix_t m1, result;
  m1.rows = -1;
  m1.columns = 2;
  ck_assert_int_eq(s21_inverse_matrix(&m1, &result), 1);
  s21_create_matrix(3, 2, &m1);
  ck_assert_int_eq(s21_inverse_matrix(&m1, &result), 2);
  s21_remove_matrix(&m1);
  s21_create_matrix(3, 3, &m1);
  m1.matrix[0][0] = 1;
  m1.matrix[0][1] = 2;
  m1.matrix[0][2] = 3;
  m1.matrix[1][0] = 4;
  m1.matrix[1][1] = 5;
  m1.matrix[1][2] = 6;
  m1.matrix[2][0] = 7;
  m1.matrix[2][1] = 8;
  m1.matrix[2][2] = 9;
  ck_assert_int_eq(s21_inverse_matrix(&m1, &result), 2);
  m1.matrix[0][0] = 2;
  m1.matrix[0][1] = 5;
  m1.matrix[0][2] = 7;
  m1.matrix[1][0] = 6;
  m1.matrix[1][1] = 3;
  m1.matrix[1][2] = 4;
  m1.matrix[2][0] = 5;
  m1.matrix[2][1] = -2;
  m1.matrix[2][2] = -3;
  s21_create_matrix(3, 3, &result);
  s21_inverse_matrix(&m1, &result);
  ck_assert_double_eq(result.matrix[0][0], 1);
  ck_assert_double_eq(result.matrix[0][1], -1);
  ck_assert_double_eq(result.matrix[0][2], 1);
  ck_assert_double_eq(result.matrix[1][0], -38);
  ck_assert_double_eq(result.matrix[1][1], 41);
  ck_assert_double_eq(result.matrix[1][2], -34);
  ck_assert_double_eq(result.matrix[2][0], 27);
  ck_assert_double_eq(result.matrix[2][1], -29);
  ck_assert_double_eq(result.matrix[2][2], 24);
}
END_TEST

START_TEST(s21_inverse_matrix_test_2) {
  matrix_t m1, result;
  s21_create_matrix(1, 1, &m1);
  m1.matrix[0][0] = 4;
  s21_inverse_matrix(&m1, &result);
  ck_assert_double_eq(result.matrix[0][0], 0.25);
}
END_TEST

START_TEST(s21_inverse_matrix_test_3) {
  matrix_t m1, result;
  s21_create_matrix(2, 2, &m1);
  m1.matrix[0][0] = 2;
  m1.matrix[0][1] = 5;
  m1.matrix[1][0] = -8;
  m1.matrix[1][1] = 4;
  s21_inverse_matrix(&m1, &result);
}

Suite *suite_create_matrix(void) {
  Suite *suite = suite_create("s21_matrix");
  // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
  TCase *tcase_core = tcase_create("matrix");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, s21_create_matrix_test);
  tcase_add_test(tcase_core, s21_remove_matrix_test);
  tcase_add_test(tcase_core, s21_eq_matrix_test);
  tcase_add_test(tcase_core, s21_sum_matrix_test);
  tcase_add_test(tcase_core, s21_sub_matrix_test);
  tcase_add_test(tcase_core, s21_mult_number_test);
  tcase_add_test(tcase_core, s21_mult_matrix_test);
  tcase_add_test(tcase_core, s21_transpose_test);
  tcase_add_test(tcase_core, s21_calc_complements_test);
  tcase_add_test(tcase_core, s21_determinant_test);
  tcase_add_test(tcase_core, s21_inverse_matrix_test);
  tcase_add_test(tcase_core, s21_inverse_matrix_test_2);
  tcase_add_test(tcase_core, s21_inverse_matrix_test_3);

  // Добавление теста в тестовый набор.
  suite_add_tcase(suite, tcase_core);

  return suite;
}

int main(void) {
  int failed_count;
  Suite *suite = suite_create_matrix();
  SRunner *suite_runner = srunner_create(suite);

  srunner_run_all(suite_runner, CK_NORMAL);
  failed_count =
      srunner_ntests_failed(suite_runner);  // запускаем все тестовые случаи
  srunner_free(suite_runner);
  return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
