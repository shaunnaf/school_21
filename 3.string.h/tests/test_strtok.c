#include "../s21_tests.h"

START_TEST(strtok_1) {
  char str_1[16] = "This,is,my,home";
  char str_2[2] = ",";
  ck_assert_pstr_eq(strtok(str_1, str_2), s21_strtok(str_1, str_2));
}
END_TEST

START_TEST(strtok_2) {
  char str1[6] = "qwert";
  char str2[2] = "q";
  ck_assert_pstr_eq(strtok(str1, str2), s21_strtok(str1, str2));
}
END_TEST

START_TEST(strtok_3) {
  char str1[50] = "No, :qwerty;qw astra";
  char str2[10] = " ,:\n\0";
  ck_assert_pstr_eq(strtok(str1, str2), s21_strtok(str1, str2));
}
END_TEST

START_TEST(strtok_4) {
  char str1[50] = "Per, :aspera;ad. astra";
  char str2[10] = ",:\n\0";
  ck_assert_pstr_eq(strtok(str1, str2), s21_strtok(str1, str2));
}
END_TEST

START_TEST(strtok_5) {
  char str1[50] = "Per :aspn::::::era;ad. ast::::ra:";
  char str2[10] = ":";
  ck_assert_pstr_eq(strtok(str1, str2), s21_strtok(str1, str2));
}
END_TEST

START_TEST(strtok_6) {
  char str1[50] = "test1/test2/test3/test4";
  char str2[10] = "/";
  ck_assert_pstr_eq(strtok(str1, str2), s21_strtok(str1, str2));
}
END_TEST

START_TEST(strtok_7) {
  char str[50] = "AadacAdxa";
  char str1[10] = "a";
  ck_assert_pstr_eq(strtok(str, str1), s21_strtok(str, str1));
}
END_TEST

START_TEST(strtok_8) {
  char str[] = "A";
  char str1[] = "\0";
  ck_assert_pstr_eq(strtok(str, str1), s21_strtok(str, str1));
}
END_TEST

START_TEST(strtok_9) {
  char str1[] = "qwerty";
  char str2[] = "1234";
  ck_assert_pstr_eq(strtok(str1, str2), s21_strtok(str1, str2));
}
END_TEST

START_TEST(strtok_10) {
  char str1[] = "check/Me/Out\\";
  char str2[] = "check/Me/Out\\";
  char simbols[] = "/";
  char *nstr_1, *nstr_2;
  nstr_1 = strtok(str1, simbols);
  nstr_2 = s21_strtok(str2, simbols);
  while (nstr_1 != s21_NULL) {
    ck_assert_pstr_eq(nstr_1, nstr_2);
    nstr_1 = strtok(s21_NULL, simbols);
    nstr_2 = s21_strtok(s21_NULL, simbols);
  }
}
END_TEST

START_TEST(strtok_11) {
  char str1[] = "Hello, my friend - say Charlie, pom.";
  char str2[] = "Hello, my friend - say Charlie, pom.";
  char simbols[5] = " ,.-";
  char *nstr_1, *nstr_2;
  nstr_1 = strtok(str1, simbols);
  nstr_2 = s21_strtok(str2, simbols);
  while (nstr_1 != s21_NULL) {
    ck_assert_pstr_eq(nstr_1, nstr_2);
    nstr_1 = strtok(s21_NULL, simbols);
    nstr_2 = s21_strtok(s21_NULL, simbols);
  }
}
END_TEST

START_TEST(strtok_12) {
  char str4_1[] = "testing with original string.h";
  char str4_2[] = "testing with original string.h";
  char del4[3] = ". ";
  char *nstr_1, *nstr_2;
  nstr_1 = strtok(str4_1, del4);
  nstr_2 = s21_strtok(str4_2, del4);
  while (nstr_1 != s21_NULL) {
    ck_assert_pstr_eq(nstr_1, nstr_2);
    nstr_1 = strtok(s21_NULL, del4);
    nstr_2 = s21_strtok(s21_NULL, del4);
  }
}
END_TEST

START_TEST(strtok_13) {
  char *str1 = s21_NULL;
  char *str2 = "a";
  ck_assert_pstr_eq(strtok(str1, str2), s21_strtok(str1, str2));
}
END_TEST

START_TEST(strtok_14) {
  char *str1 = s21_NULL;
  char *str3 = s21_NULL;
  char *str2 = "";
  ck_assert_pstr_eq(strtok(str1, str2), s21_strtok(str3, str2));
}
END_TEST

Suite *suite_strtok(void) {
  Suite *s = suite_create("suite_strtok");
  TCase *tc = tcase_create("strtok_tc");
  tcase_add_test(tc, strtok_1);
  tcase_add_test(tc, strtok_3);
  tcase_add_test(tc, strtok_2);
  tcase_add_test(tc, strtok_3);
  tcase_add_test(tc, strtok_4);
  tcase_add_test(tc, strtok_5);
  tcase_add_test(tc, strtok_6);
  tcase_add_test(tc, strtok_7);
  tcase_add_test(tc, strtok_8);
  tcase_add_test(tc, strtok_9);
  tcase_add_test(tc, strtok_10);
  tcase_add_test(tc, strtok_11);
  tcase_add_test(tc, strtok_12);
  tcase_add_test(tc, strtok_13);
  tcase_add_test(tc, strtok_14);

  suite_add_tcase(s, tc);
  return s;
}