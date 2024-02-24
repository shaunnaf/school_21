#include "../s21_tests.h"

START_TEST(trim_1) {
  char *str1 = "Hello World";
  char *str2 = "H";
  char *str3 = (char *)s21_trim(str1, str2);
  ck_assert_str_eq(str3, "ello World");
  free(str3);
}
END_TEST

START_TEST(trim_2) {
  char *str1 = "My Friend";
  char *str2 = "end";
  char *str3 = (char *)s21_trim(str1, str2);
  ck_assert_str_eq(str3, "My Fri");
  free(str3);
}
END_TEST

START_TEST(trim_3) {
  char *str1 = "";
  char *str2 = "";
  char *str3 = (char *)s21_trim(str1, str2);
  ck_assert_ptr_null(str3);
  free(str3);
}
END_TEST

START_TEST(trim_4) {
  char *str = "qwerty";
  char *str2 = "qwerty";
  char *str3 = (char *)s21_trim(str, str2);
  ck_assert_ptr_eq(str3, s21_NULL);
  free(str3);
}
END_TEST

START_TEST(trim_6) {
  char *str = "";
  char *str2 = s21_NULL;
  char *str3 = (char *)s21_trim(str, str2);
  ck_assert_ptr_eq(str3, s21_NULL);
  free(str3);
}
END_TEST

Suite *suite_trim(void) {
  Suite *s = suite_create("suite_trim");
  TCase *tc = tcase_create("trim_tc");
  tcase_add_test(tc, trim_1);
  tcase_add_test(tc, trim_2);
  tcase_add_test(tc, trim_3);
  tcase_add_test(tc, trim_4);
  tcase_add_test(tc, trim_6);
  suite_add_tcase(s, tc);
  return s;
}