#include "../s21_tests.h"

START_TEST(memchr_1) {
  s21_size_t n_byte = 0;
  char str[10] = "";
  int find_byte = '\0';

  ck_assert_ptr_eq(s21_memchr(str, find_byte, n_byte),
                   memchr(str, find_byte, n_byte));
}
END_TEST

START_TEST(memchr_2) {
  s21_size_t n_byte = 7;
  char str[10] = "qwerty";
  int find_byte = '\0';

  ck_assert_ptr_eq(s21_memchr(str, find_byte, n_byte),
                   memchr(str, find_byte, n_byte));
}
END_TEST

START_TEST(memchr_3) {
  s21_size_t n_byte = 6;
  char str[10] = "Qwerty";
  int find_byte = 'Q';

  ck_assert_ptr_eq(s21_memchr(str, find_byte, n_byte),
                   memchr(str, find_byte, n_byte));
}
END_TEST

START_TEST(memchr_4) {
  s21_size_t n_byte = 7;
  char str[10] = "qwertY";
  int find_byte = 'Y';

  ck_assert_ptr_eq(s21_memchr(str, find_byte, n_byte),
                   memchr(str, find_byte, n_byte));
}
END_TEST

START_TEST(memchr_5) {
  s21_size_t n_byte = 15;
  char str[16] = "Str55333222ingA";
  int find_byte = '3';

  ck_assert_ptr_eq(s21_memchr(str, find_byte, n_byte),
                   memchr(str, find_byte, n_byte));
}
END_TEST

START_TEST(memchr_8) {
  s21_size_t n_byte = 5;
  char str[10] = "aboba";
  int find_byte = 'c';

  ck_assert_ptr_eq(s21_memchr(str, find_byte, n_byte),
                   memchr(str, find_byte, n_byte));
}
END_TEST

Suite *suite_memchr(void) {
  Suite *s = suite_create("suite_memchr");
  TCase *tc = tcase_create("memchr_tc");

  tcase_add_test(tc, memchr_1);
  tcase_add_test(tc, memchr_2);
  tcase_add_test(tc, memchr_3);
  tcase_add_test(tc, memchr_4);
  tcase_add_test(tc, memchr_5);
  tcase_add_test(tc, memchr_8);

  suite_add_tcase(s, tc);
  return s;
}