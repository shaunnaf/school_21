#include "../s21_tests.h"

START_TEST(insert_1) {
  char str1[6] = "Hello";
  char str2[11] = " my friend";
  char *str3 = (char *)s21_insert(str1, str2, 5);
  ck_assert_str_eq(str3, "Hello my friend");
  free(str3);
}
END_TEST

START_TEST(insert_2) {
  char str1[1] = "";
  char str2[14] = "checking null";
  char *str3 = (char *)s21_insert(str1, str2, 1);
  ck_assert_ptr_eq(str3, s21_NULL);
  free(str3);
}
END_TEST

START_TEST(insert_3) {
  char str1[7] = "qwerty";
  char str2[2] = " ";
  char *str3 = (char *)s21_insert(str1, str2, 4);
  ck_assert_str_eq(str3, "qwer ty");
  free(str3);
}
END_TEST

START_TEST(insert_5) {
  char str1[8] = "journey";
  char str2[7] = "start";
  char *str3 = (char *)s21_insert(str1, str2, 0);
  ck_assert_str_eq(str3, "startjourney");
  free(str3);
}
END_TEST

START_TEST(insert_6) {
  char str1[5] = "qwer";
  char str2[3] = "ty";
  char *str3 = (char *)s21_insert(str1, str2, -1);
  ck_assert_ptr_eq(str3, NULL);
  free(str3);
}
END_TEST

START_TEST(insert_8) {
  char str1[2] = " ";
  char str2[12] = "hello world";
  char *str3 = (char *)s21_insert(str1, str2, 3);
  ck_assert_ptr_eq(str3, s21_NULL);
  free(str3);
}
END_TEST

START_TEST(insert_11) {
  char str1[4] = "";
  char str2[6] = "";
  char *str3 = (char *)s21_insert(str1, str2, 1);
  ck_assert_ptr_eq(str3, s21_NULL);
  free(str3);
}
END_TEST

Suite *suite_insert(void) {
  Suite *s = suite_create("suite_insert");
  TCase *tc = tcase_create("insert_tc");
  tcase_add_test(tc, insert_1);
  tcase_add_test(tc, insert_2);
  tcase_add_test(tc, insert_3);
  tcase_add_test(tc, insert_5);
  tcase_add_test(tc, insert_6);
  tcase_add_test(tc, insert_8);
  tcase_add_test(tc, insert_11);
  suite_add_tcase(s, tc);
  return s;
}