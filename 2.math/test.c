#include <math.h>
#include <stdlib.h>

#include "check.h"
#include "s21_math.h"

START_TEST(s21_abs_tests) {
  ck_assert_int_eq(s21_abs(-13), abs(-13));
  ck_assert_int_eq(abs(13), s21_abs(13));
  ck_assert_int_eq(abs(323462342), s21_abs(323462342));
  ck_assert_int_eq(abs(0), s21_abs(0));
}
END_TEST

START_TEST(s21_acos_tests) {
  ck_assert_float_eq(s21_acos(-0.3232), acos(-0.3232));
  ck_assert_ldouble_eq(s21_acos(1), acos(1));
  ck_assert_ldouble_nan(s21_acos(3));
  ck_assert_ldouble_nan(s21_acos(-3));
  ck_assert_ldouble_eq(s21_acos(0), acos(0));
  ck_assert_ldouble_eq(s21_acos(-1), acos(-1));
}
END_TEST

START_TEST(s21_asin_tests) {
  ck_assert_float_eq(s21_asin(-0.3232), asin(-0.3232));
  ck_assert_ldouble_eq(s21_asin(1), asin(1));
  ck_assert_ldouble_nan(s21_asin(3));
  ck_assert_ldouble_nan(s21_asin(-3));
  ck_assert_ldouble_eq(s21_asin(0), asin(0));
  ck_assert_ldouble_eq(s21_asin(-1), asin(-1));
}
END_TEST

START_TEST(s21_atan_tests) {
  ck_assert_float_eq(s21_atan(-0.3232), atan(-0.3232));
  ck_assert_ldouble_eq(s21_atan(1), atan(1));
  ck_assert_ldouble_eq(s21_atan(0), atan(0));
  ck_assert_ldouble_eq(s21_atan(-1), atan(-1));
}
END_TEST

START_TEST(s21_ceil_tests) {
  ck_assert_ldouble_eq(s21_ceil(-0), ceil(-0));
  ck_assert_ldouble_eq(s21_ceil(4.5), ceil(4.5));
  ck_assert_ldouble_eq(s21_ceil(413431423232311132), ceil(413431423232311132));
}
END_TEST

START_TEST(s21_cos_tests) {
  ck_assert_float_eq(s21_cos(-0.3232), cos(-0.3232));
  ck_assert_float_eq(s21_cos(1), cos(1));
  ck_assert_float_eq(s21_cos(5), cos(5));
  ck_assert_float_eq(s21_cos(-10), cos(-10));
  ck_assert_float_eq(s21_cos(0), cos(0));
  ck_assert_float_eq(s21_cos(-1), cos(-1));
}
END_TEST

START_TEST(s21_exp_tests) {
  ck_assert_float_eq(s21_exp(1), exp(1));
  ck_assert_float_eq(s21_exp(5), exp(5));
  ck_assert_ldouble_eq(s21_exp(0), exp(0));
  ck_assert_float_eq(s21_exp(-1), exp(-1));
  ck_assert_float_eq(s21_exp(-3.2), exp(-3.2));
}
END_TEST

START_TEST(s21_fabs_tests) {
  ck_assert_int_eq(s21_fabs(-13.21313), fabs(-13.21313));
  ck_assert_float_eq(s21_fabs(2.2), fabs(2.2));
}
END_TEST

START_TEST(s21_floor_tests) {
  ck_assert_ldouble_eq(s21_floor(5.3), floor(5.3));
}
END_TEST

START_TEST(s21_fmod_tests) {
  ck_assert_float_eq(s21_fmod(-4.2, -2), fmod(-4.2, -2));
  ck_assert_float_eq(s21_fmod(8.4, 2.4), fmod(8.4, 2.4));
  ck_assert_float_nan(s21_fmod(8.4, 0));
}
END_TEST

START_TEST(s21_log_tests) {
  ck_assert_float_eq(s21_log(4.2), log(4.2));
  ck_assert_float_eq(s21_log(0), log(0));
  ck_assert_ldouble_nan(s21_log(-3));
}
END_TEST

START_TEST(s21_pow_tests) {
  ck_assert_float_eq(s21_pow(3.2, 2), pow(3.2, 2));
  ck_assert_double_eq(s21_pow(0, 2), pow(0, 2));
  ck_assert_double_eq(s21_pow(0, -2), pow(0, -2));
  ck_assert_double_eq(s21_pow(0, 0), pow(0, 0));
  ck_assert_double_eq(s21_pow(3, 0), pow(3, 0));
  ck_assert_float_eq(s21_pow(-3.2, 2), pow(-3.2, 2));
}
END_TEST

START_TEST(s21_sin_tests) {
  ck_assert_float_eq(s21_sin(-1.2), sin(-1.2));
  ck_assert_float_eq(s21_sin(-0.3232), sin(-0.3232));
  ck_assert_float_eq(s21_sin(1), sin(1));
  ck_assert_float_eq(s21_sin(5), sin(5));
  ck_assert_float_eq(s21_sin(-10), sin(-10));
  ck_assert_float_eq(s21_sin(0), sin(0));
  ck_assert_float_eq(s21_sin(-1), sin(-1));
}
END_TEST

START_TEST(s21_sqrt_tests) {
  ck_assert_float_nan(s21_sqrt(-3));
  ck_assert_float_eq(s21_sqrt(0), sqrt(0));
  ck_assert_float_eq(s21_sqrt(9), sqrt(9));
  ck_assert_float_eq(s21_sqrt(9.2), sqrt(9.2));
}
END_TEST

START_TEST(s21_tan_tests) {
  ck_assert_float_eq(s21_tan(3), tan(3));
  ck_assert_float_eq(s21_tan(21), tan(21));
  ck_assert_float_eq(s21_tan(0), tan(0));
  ck_assert_float_eq(s21_tan(-43), tan(-43));
  ck_assert_float_eq(s21_tan(90), tan(90));
}
END_TEST

START_TEST(s21_factorial_tests) {
  ck_assert_ldouble_eq(s21_factorial(5), 120);
  ck_assert_ldouble_nan(s21_factorial(-2));
}
END_TEST

// Функция создания набора тестов.
Suite *suite_create_math(void) {
  Suite *suite = suite_create("s21_math");
  // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
  TCase *tcase_core = tcase_create("math");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, s21_factorial_tests);
  tcase_add_test(tcase_core, s21_abs_tests);
  tcase_add_test(tcase_core, s21_acos_tests);
  tcase_add_test(tcase_core, s21_asin_tests);
  tcase_add_test(tcase_core, s21_atan_tests);
  tcase_add_test(tcase_core, s21_ceil_tests);
  tcase_add_test(tcase_core, s21_cos_tests);
  tcase_add_test(tcase_core, s21_exp_tests);
  tcase_add_test(tcase_core, s21_fabs_tests);
  tcase_add_test(tcase_core, s21_floor_tests);
  tcase_add_test(tcase_core, s21_fmod_tests);
  tcase_add_test(tcase_core, s21_pow_tests);
  tcase_add_test(tcase_core, s21_sin_tests);
  tcase_add_test(tcase_core, s21_sqrt_tests);
  tcase_add_test(tcase_core, s21_tan_tests);
  tcase_add_test(tcase_core, s21_log_tests);

  // Добавление теста в тестовый набор.
  suite_add_tcase(suite, tcase_core);

  return suite;
}

int main(void) {
  int failed_count;
  Suite *suite = suite_create_math();
  SRunner *suite_runner = srunner_create(suite);

  srunner_run_all(suite_runner, CK_NORMAL);
  failed_count =
      srunner_ntests_failed(suite_runner);  // запускаем все тестовые случаи
  srunner_free(suite_runner);
  return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}