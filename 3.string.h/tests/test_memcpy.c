#include "../s21_tests.h"

START_TEST(memcpy_1) {
  char str_5[3] = "q\n\0";
  char str_6[3] = "\0";
  ck_assert_str_eq(memcpy(str_5, str_6, 2), s21_memcpy(str_5, str_6, 2));
}
END_TEST

START_TEST(memcpy_2) {
  char str_1[] = "\0";
  char str_2[] = " ";
  ck_assert_str_eq(memcpy(str_1, str_2, 2), s21_memcpy(str_1, str_2, 1));
}
END_TEST

START_TEST(memcpy_3) {
  char str_1[] = "qwerty ";
  char str_2[] = "112";
  ck_assert_str_eq(memcpy(str_1, str_2, 2), s21_memcpy(str_1, str_2, 5));
}
END_TEST

START_TEST(memcpy_4) {
  char str_1[] = "\n/n";
  char str_2[] = "-55";
  ck_assert_str_eq(memcpy(str_1, str_2, 2), s21_memcpy(str_1, str_2, 5));
}
END_TEST

START_TEST(memcpy_5) {
  char str_1[] = "1234";
  char str_2[] = "\0\f";
  ck_assert_str_eq(memcpy(str_1, str_2, 2), s21_memcpy(str_1, str_2, 5));
}
END_TEST

START_TEST(memcpy_6) {
  char str_1[] = "%hf*-5";
  char str_2[] = "\0\f";
  ck_assert_str_eq(memcpy(str_1, str_2, 2), s21_memcpy(str_1, str_2, 5));
}
END_TEST

START_TEST(memcpy_7) {
  char s1[255] = "QWERTY";
  char s2[255] = "E";
  ck_assert_pstr_eq(memcpy(s1, s2, 6), s21_memcpy(s1, s2, 6));
}
END_TEST

Suite *suite_memcpy(void) {
  Suite *s = suite_create("suite_memcpy");
  TCase *tc = tcase_create("memcpy_tc");
  tcase_add_test(tc, memcpy_1);
  tcase_add_test(tc, memcpy_2);
  tcase_add_test(tc, memcpy_3);
  tcase_add_test(tc, memcpy_4);
  tcase_add_test(tc, memcpy_5);
  tcase_add_test(tc, memcpy_6);
  tcase_add_test(tc, memcpy_7);
  suite_add_tcase(s, tc);
  return s;
}