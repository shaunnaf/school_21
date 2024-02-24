#include "../s21_tests.h"

START_TEST(empty) {
  char str1[] = "";
  char str2[] = "";
  s21_size_t n_byte = 0;

  int our = s21_strncmp(str1, str2, n_byte);
  int expected = strncmp(str1, str2, n_byte);

  if (our > 1) our = 1;
  if (expected > 1) expected = 1;

  if (our < -1) our = -1;
  if (expected < -1) expected = -1;

  ck_assert_int_eq(our, expected);
}
END_TEST

START_TEST(qwerty_) {
  char str1[] = "qwerty";
  char str2[] = "";
  s21_size_t n_byte = 0;

  int our = s21_strncmp(str1, str2, n_byte);
  int expected = strncmp(str1, str2, n_byte);

  if (our > 1) our = 1;
  if (expected > 1) expected = 1;

  if (our < -1) our = -1;
  if (expected < -1) expected = -1;

  ck_assert_int_eq(our, expected);
}
END_TEST

START_TEST(_qwerty) {
  char str1[] = "";
  char str2[] = "qwerty";
  s21_size_t n_byte = 0;

  int our = s21_strncmp(str1, str2, n_byte);
  int expected = strncmp(str1, str2, n_byte);

  if (our > 1) our = 1;
  if (expected > 1) expected = 1;

  if (our < -1) our = -1;
  if (expected < -1) expected = -1;

  ck_assert_int_eq(our, expected);
}
END_TEST

START_TEST(qwerty_qwerty) {
  char str1[] = "qwerty";
  char str2[] = "qwerty";
  s21_size_t n_byte = 6;

  int our = s21_strncmp(str1, str2, n_byte);
  int expected = strncmp(str1, str2, n_byte);

  if (our > 1) our = 1;
  if (expected > 1) expected = 1;

  if (our < -1) our = -1;
  if (expected < -1) expected = -1;

  ck_assert_int_eq(our, expected);
}
END_TEST

START_TEST(qwertyqwerty) {
  char str1[] = "qwertyqwerty";
  char str2[] = "qwe";
  s21_size_t n_byte = 4;

  int our = s21_strncmp(str1, str2, n_byte);
  int expected = strncmp(str1, str2, n_byte);

  if (our > 1) our = 1;
  if (expected > 1) expected = 1;

  if (our < -1) our = -1;
  if (expected < -1) expected = -1;

  ck_assert_int_eq(our, expected);
}
END_TEST

START_TEST(qwertyqwerty_1) {
  char str1[] = "qwerty";
  char str2[] = "qwerty";
  s21_size_t n_byte = 1;

  int our = s21_strncmp(str1, str2, n_byte);
  int expected = strncmp(str1, str2, n_byte);

  if (our > 1) our = 1;
  if (expected > 1) expected = 1;

  if (our < -1) our = -1;
  if (expected < -1) expected = -1;

  ck_assert_int_eq(our, expected);
}
END_TEST

Suite *suite_strncmp(void) {
  Suite *s = suite_create("suite_strncmp");
  TCase *tc = tcase_create("strncmp_tc");

  tcase_add_test(tc, empty);
  tcase_add_test(tc, qwerty_);
  tcase_add_test(tc, _qwerty);
  tcase_add_test(tc, qwerty_qwerty);
  tcase_add_test(tc, qwertyqwerty);
  tcase_add_test(tc, qwertyqwerty_1);

  suite_add_tcase(s, tc);
  return s;
}