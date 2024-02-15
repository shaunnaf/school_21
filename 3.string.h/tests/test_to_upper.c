#include "../s21_tests.h"

START_TEST(to_upper_1) {
  char str1[11] = "helloworld";
  char *str2 = s21_to_upper(str1);
  ck_assert_str_eq(str2, "HELLOWORLD");
  free(str2);
}
END_TEST

START_TEST(to_upper_2) {
  char str1[19] = "few words to lower";
  char *str2 = s21_to_upper(str1);
  ck_assert_str_eq(str2, "FEW WORDS TO LOWER");
  free(str2);
}
END_TEST

START_TEST(to_upper_3) {
  char str1[1] = "";
  char *str2 = s21_to_upper(str1);
  ck_assert_str_eq(str2, "");
  free(str2);
}
END_TEST

START_TEST(to_upper_4) {
  char str1[7] = "qwerty";
  char *str2 = s21_to_upper(str1);
  ck_assert_str_eq(str2, "QWERTY");
  free(str2);
}
END_TEST

// START_TEST(to_upper_5) {
//     char *str1 = s21_NULL;
//     char *str2 = s21_to_upper(str1);
//     ck_assert_ptr_eq(str2, s21_NULL);
//     free(str2);
// } END_TEST

START_TEST(to_upper_6) {
  char str1[12] = "qwerty12345";
  char *str2 = s21_to_upper(str1);
  ck_assert_str_eq(str2, "QWERTY12345");
  free(str2);
}
END_TEST

START_TEST(to_upper_7) {
  char str1[12] = "hello\0world";
  char *str2 = s21_to_upper(str1);
  ck_assert_str_eq(str2, "HELLO");
  free(str2);
}
END_TEST

START_TEST(to_upper_8) {
  char str1[10] = "\0a\0";
  char *str2 = s21_to_upper(str1);
  ck_assert_str_eq(str2, "");
  free(str2);
}
END_TEST

Suite *suite_to_upper(void) {
  Suite *s = suite_create("suite_to_upper");
  TCase *tc = tcase_create("to_upper_tc");
  tcase_add_test(tc, to_upper_1);
  tcase_add_test(tc, to_upper_2);
  tcase_add_test(tc, to_upper_3);
  tcase_add_test(tc, to_upper_4);
  // tcase_add_test(tc, to_upper_5);
  tcase_add_test(tc, to_upper_6);
  tcase_add_test(tc, to_upper_7);
  tcase_add_test(tc, to_upper_8);
  suite_add_tcase(s, tc);
  return s;
}