#include "../s21_tests.h"

START_TEST(strstr_1) {
  char haystack[] = "";
  char needle[] = "";

  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(strstr_2) {
  char haystack[] = "";
  char needle[] = "jho1faQsdkjnSa3aefwf8hiuJafeHioj";

  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(strstr_3) {
  char haystack[] = "safQhilufas7MaSef2345wknwefnkjHawe2fhilu";
  char needle[] = "";

  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(strstr_4) {
  char haystack[] = "qwerty 12345";
  char needle[] = "12345";

  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(strstr_5) {
  char haystack[] = "qwerty";
  char needle[] = "NOT";

  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(strstr_6) {
  char haystack[] = "AbOBosNyTSa";
  char needle[] = "aBoboSNYTsa";

  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(strstr_7) {
  char haystack[] = "AD AD AD";
  char needle[] = "AD";

  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(strstr_8) {
  char haystack[] = "22 321 123";
  char needle[] = "123";

  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(strstr_9) {
  char haystack[] = "1";
  char needle[] = "1";

  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(strstr_10) {
  char haystack[] =
      "13625523478437263475984675342345sdghyftrg freshtsyASFWEt wEafe";
  char needle[] = " ";

  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(strstr_11) {
  char haystack[] = "-";
  char needle[] = "1234567890qwertyuiopasdfghjk-";

  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

Suite *suite_strstr(void) {
  Suite *s = suite_create("suite_strstr");
  TCase *tc = tcase_create("strstr_tc");

  tcase_add_test(tc, strstr_1);
  tcase_add_test(tc, strstr_2);
  tcase_add_test(tc, strstr_3);
  tcase_add_test(tc, strstr_4);
  tcase_add_test(tc, strstr_5);
  tcase_add_test(tc, strstr_6);
  tcase_add_test(tc, strstr_7);
  tcase_add_test(tc, strstr_8);
  tcase_add_test(tc, strstr_9);
  tcase_add_test(tc, strstr_10);
  tcase_add_test(tc, strstr_11);

  suite_add_tcase(s, tc);
  return s;
}