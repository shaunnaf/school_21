#include "../s21_tests.h"

START_TEST(qwerty_1) {
  char src[] = "qwerty";
  char find = 'r';

  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(qwerty_2) {
  char src[] = "qwerty";
  char find = 'T';

  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(qwerty_3) {
  char src[] = "qwerty";
  char find = '1';

  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(qwerty_4) {
  char src[] = "qwerty12345";
  char find = '2';

  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(qwerty_5) {
  char src[] = "qwerty12345";
  char find = '6';

  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(qwerty_6) {
  char src[] = "";
  char find = '6';

  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

Suite *suite_strchr(void) {
  Suite *s = suite_create("suite_strchr");
  TCase *tc = tcase_create("strchr_tc");

  tcase_add_test(tc, qwerty_1);
  tcase_add_test(tc, qwerty_2);
  tcase_add_test(tc, qwerty_3);
  tcase_add_test(tc, qwerty_4);
  tcase_add_test(tc, qwerty_5);
  tcase_add_test(tc, qwerty_6);

  suite_add_tcase(s, tc);
  return s;
}