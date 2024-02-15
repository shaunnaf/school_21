#include "../s21_tests.h"

START_TEST(empty) {
  char src[] = "";
  char res[] = "";
  char exp[] = "";
  s21_size_t n_byte = 0;

  s21_strncpy(res, src, n_byte);
  strncpy(exp, src, n_byte);

  ck_assert_str_eq(res, exp);
}
END_TEST

START_TEST(zero_byte) {
  char src[] = "123";
  char res[] = "123";
  char exp[] = "123";
  s21_size_t n_byte = 0;

  s21_strncpy(res, src, n_byte);
  strncpy(exp, src, n_byte);

  ck_assert_str_eq(res, exp);
}
END_TEST

START_TEST(empty_src) {
  char src[] = "";
  char res[] = "qwe";
  char exp[] = "qwe";
  s21_size_t n_byte = 0;

  s21_strncpy(res, src, n_byte);
  strncpy(exp, src, n_byte);

  ck_assert_str_eq(res, exp);
}
END_TEST

START_TEST(byte_1) {
  char src[] = "qwe";
  char res[5] = "qwe";
  char exp[5] = "qwe";
  s21_size_t n_byte = 1;

  s21_strncpy(res, src, n_byte);
  strncpy(exp, src, n_byte);

  ck_assert_str_eq(res, exp);
}
END_TEST

START_TEST(byte_2) {
  char src[] = "qwe";
  char res[7] = "qwe";
  char exp[7] = "qwe";
  s21_size_t n_byte = 2;

  s21_strncpy(res, src, n_byte);
  strncpy(exp, src, n_byte);

  ck_assert_str_eq(res, exp);
}
END_TEST

START_TEST(string) {
  char src[] = "Str1ng";
  char res[7 + 7] = "Str1ng";
  char exp[7 + 7] = "Str1ng";
  s21_size_t n_byte = 7;

  s21_strncpy(res, src, n_byte);
  strncpy(exp, src, n_byte);

  ck_assert_str_eq(res, exp);
}
END_TEST

Suite *suite_strncpy(void) {
  Suite *s = suite_create("suite_strncpy");
  TCase *tc = tcase_create("strncpy_tc");

  tcase_add_test(tc, empty);
  tcase_add_test(tc, zero_byte);
  tcase_add_test(tc, empty_src);
  tcase_add_test(tc, byte_1);
  tcase_add_test(tc, byte_2);
  tcase_add_test(tc, string);

  suite_add_tcase(s, tc);
  return s;
}