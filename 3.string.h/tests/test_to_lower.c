#include "../s21_tests.h"

START_TEST(to_lower_1) {
  char str1[11] = "HELLOWORLD";
  char *str2 = s21_to_lower(str1);
  ck_assert_str_eq(str2, "helloworld");
  free(str2);
}
END_TEST

START_TEST(to_lower_2) {
  char str1[19] = "FEW WORDS TO LOWER";
  char *str2 = s21_to_lower(str1);
  ck_assert_str_eq(str2, "few words to lower");
  free(str2);
}
END_TEST

START_TEST(to_lower_3) {
  char str1[1] = "";
  char *str2 = s21_to_lower(str1);
  ck_assert_str_eq(str2, "");
  free(str2);
}
END_TEST

START_TEST(to_lower_4) {
  char str1[7] = "qwerty";
  char *str2 = s21_to_lower(str1);
  ck_assert_str_eq(str2, "qwerty");
  free(str2);
}
END_TEST

START_TEST(to_lower_5) {
  char *str1 = s21_NULL;
  char *str2 = s21_to_lower(str1);
  ck_assert_ptr_eq(str2, s21_NULL);
  free(str2);
}
END_TEST

START_TEST(to_lower_6) {
  char str1[12] = "QWERTY12345";
  char *str2 = s21_to_lower(str1);
  ck_assert_str_eq(str2, "qwerty12345");
  free(str2);
}
END_TEST

START_TEST(to_lower_7) {
  char str1[12] = "HELLO\0WORLD";
  char *str2 = s21_to_lower(str1);
  ck_assert_str_eq(str2, "hello");
  free(str2);
}
END_TEST

START_TEST(to_lower_8) {
  char str1[10] = "\0A\0";
  char *str2 = s21_to_lower(str1);
  ck_assert_str_eq(str2, "");
  free(str2);
}
END_TEST

Suite *suite_to_lower(void) {
  Suite *s = suite_create("suite_to_lower");
  TCase *tc = tcase_create("to_lower_tc");
  tcase_add_test(tc, to_lower_1);
  tcase_add_test(tc, to_lower_2);
  tcase_add_test(tc, to_lower_3);
  tcase_add_test(tc, to_lower_4);
  tcase_add_test(tc, to_lower_5);
  tcase_add_test(tc, to_lower_6);
  tcase_add_test(tc, to_lower_7);
  tcase_add_test(tc, to_lower_8);
  suite_add_tcase(s, tc);
  return s;
}