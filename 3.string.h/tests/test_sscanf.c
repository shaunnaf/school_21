#include "../s21_tests.h"

START_TEST(sscanf_1) {
  char *str2 = malloc(sizeof(char *) * 20);
  char *str4 = malloc(sizeof(char *) * 20);
  long long unsigned a = 0;
  int b = 0;
  char str3 = '1';
  char str = '1';
  char res[100];
  char res2[100];
  sprintf(
      res, "%d %llu %s %d %c %c",
      sscanf("-032.2xaav 2 h", "%llu %s %c %n %c", &a, str2, &str, &b, &str3),
      a, str2, b, str, str3);

  sprintf(res2, "%d %llu %s %d %c %c",
          s21_sscanf("-032.2xaav 2 h", "%llu %s %c %n %c", &a, str4, &str, &b,
                     &str3),
          a, str4, b, str, str3);
  ck_assert_str_eq(res, res2);
  free(str2);
  free(str4);
}
END_TEST

START_TEST(sscanf_2) {
  int a = 0;
  char str3 = '1';
  char res[100];
  char res2[100];
  sprintf(res, "%d %c %d", sscanf("  2 2 3 ", "%c %d", &str3, &a), str3, a);

  sprintf(res2, "%d %c %d", s21_sscanf("  2 2 3 ", "%c %d", &str3, &a), str3,
          a);

  ck_assert_str_eq(res, res2);
}
END_TEST

START_TEST(sscanf_3) {
  unsigned short a = 3;
  char str3 = '1';
  char res[100];
  char res2[100];
  sprintf(res, "%d %c %hu", sscanf("  2323232 2 3 ", "%c %hu", &str3, &a), str3,
          a);

  sprintf(res2, "%d %c %hu", s21_sscanf("  2323232 2 3 ", "%c %hu", &str3, &a),
          str3, a);

  ck_assert_str_eq(res, res2);
}
END_TEST

START_TEST(sscanf_4) {
  unsigned short a = 3;
  char str3 = '1';
  char res[100];
  char res2[100];
  sprintf(res, "%d %c %hu", sscanf("  2323232 2 3 ", "%c r %hu", &str3, &a),
          str3, a);

  sprintf(res2, "%d %c %hu",
          s21_sscanf("  2323232 2 3 ", "%c r %hu", &str3, &a), str3, a);

  ck_assert_str_eq(res, res2);
}
END_TEST

START_TEST(sscanf_5) {
  float a = 3;
  char str3 = '1';
  char res[100];
  char res2[100];
  sprintf(res, "%d %c %f", sscanf("  -23232.32 2 3 ", "%c %3f", &str3, &a),
          str3, a);

  sprintf(res2, "%d %c %f", s21_sscanf("  -23232.32 2 3 ", "%c %3f", &str3, &a),
          str3, a);

  ck_assert_str_eq(res, res2);
}
END_TEST

START_TEST(sscanf_6) {
  long double a = 3;
  char str3 = '1';
  char res[100];
  char res2[100];
  sprintf(res, "%d %c %Lf", sscanf("  -23232.32 2 3 ", "%c %Lf", &str3, &a),
          str3, a);

  sprintf(res2, "%d %c %Lf",
          s21_sscanf("  -23232.32 2 3 ", "%c %Lf", &str3, &a), str3, a);

  ck_assert_str_eq(res, res2);
}
END_TEST

START_TEST(sscanf_7) {
  double a = 3;
  char str3 = '1';
  char res[100];
  char res2[100];
  sprintf(res, "%d %c %lf",
          sscanf("  -23232323232.32 2 3 ", "%c %lf", &str3, &a), str3, a);

  sprintf(res2, "%d %c %lf",
          s21_sscanf("  -23232323232.32 2 3 ", "%c %lf", &str3, &a), str3, a);

  ck_assert_str_eq(res, res2);
}
END_TEST

START_TEST(sscanf_8) {
  int a = 3;
  char str3 = '1';
  char res[100];
  char res2[100];
  sprintf(res, "%d %c %o", sscanf("  +322 3 ", "%c %o", &str3, &a), str3, a);

  sprintf(res2, "%d %c %o", s21_sscanf("  +322 3 ", "%c %o", &str3, &a), str3,
          a);

  ck_assert_str_eq(res, res2);
}
END_TEST

START_TEST(sscanf_9) {
  int a = 3;
  char str3 = '1';
  char res[100];
  char res2[100];
  sprintf(res, "%d %c %i", sscanf("  -0x2acs32 3 ", "%c %i", &str3, &a), str3,
          a);

  sprintf(res2, "%d %c %i", s21_sscanf("  -0x2acs32 3 ", "%c %i", &str3, &a),
          str3, a);

  ck_assert_str_eq(res, res2);
}
END_TEST

START_TEST(sscanf_10) {
  int a = 3;
  char str3 = '1';
  char res[100];
  char res2[100];
  sprintf(res, "%d %c %i", sscanf("  -0232 3 ", "%c %i", &str3, &a), str3, a);

  sprintf(res2, "%d %c %i", s21_sscanf("  -0232 3 ", "%c %i", &str3, &a), str3,
          a);

  ck_assert_str_eq(res, res2);
}
END_TEST

START_TEST(sscanf_11) {
  int a = 3;
  char str3 = '1';
  char res[100];
  char res2[100];
  sprintf(res, "%d %c %x", sscanf("  -223a 3 ", "%c %x", &str3, &a), str3, a);

  sprintf(res2, "%d %c %x", s21_sscanf("  -223a 3 ", "%c %x", &str3, &a), str3,
          a);

  ck_assert_str_eq(res, res2);
}
END_TEST

START_TEST(sscanf_12) {
  int a = 3;
  char str3 = '1';
  char res[100];
  char res2[100];
  sprintf(res, "%d %c %o", sscanf("f a -322 3 ", "f %c %o", &str3, &a), str3,
          a);

  sprintf(res2, "%d %c %o", s21_sscanf("f a -322 3 ", "f %c %o", &str3, &a),
          str3, a);

  ck_assert_str_eq(res, res2);
}
END_TEST

START_TEST(sscanf_13) {
  long unsigned a = 3;
  long unsigned b = 1;
  char str3 = '1';
  char res[100];
  char res2[100];
  sprintf(res, "%d %c %lu", sscanf("f a -322 3 ", "f %c %lu", &str3, &a), str3,
          a);

  sprintf(res2, "%d %c %lu", s21_sscanf("f a -322 3 ", "f %c %lu", &str3, &b),
          str3, b);

  ck_assert_str_eq(res, res2);
}
END_TEST

START_TEST(sscanf_14) {
  unsigned a = 3;
  unsigned b = 1;
  char str3 = '1';
  char res[100];
  char res2[100];
  sprintf(res, "%d %c %u", sscanf("f a -322 3 ", "f %c %u", &str3, &a), str3,
          a);

  sprintf(res2, "%d %c %u", s21_sscanf("f a -322 3 ", "f %c %u", &str3, &b),
          str3, b);

  ck_assert_str_eq(res, res2);
}
END_TEST

START_TEST(sscanf_15) {
  long a = 3;
  short a1 = 3;
  long long int a2 = 3;
  long b = 3;
  short b1 = 3;
  long long int b2 = 3;
  char str3 = '1';
  char res[100];
  char res2[100];
  sprintf(res, "%d %c %hd %ld %lld",
          sscanf("f a -322 42 41 3 ", "f %*c %hd %ld %lld", &a1, &a, &a2), str3,
          a1, a, a2);

  sprintf(res2, "%d %c %hd %ld %lld",
          s21_sscanf("f a -322 42 41 3 ", "f %*c %hd %ld %lld", &b1, &b, &b2),
          str3, b1, b, b2);

  ck_assert_str_eq(res, res2);
}
END_TEST

START_TEST(sscanf_16) {
  void *address1 = NULL;
  void *address2 = NULL;
  char a[100];
  char b[100];

  s21_sscanf("f 0x123A4Ff", "%s %p", a, &address1);
  sscanf("f 0x123A4Ff", "%s %p", b, &address2);

  ck_assert_str_eq(a, b);
  ck_assert_ptr_eq(address1, address2);
}
END_TEST

Suite *suite_sscanf(void) {
  Suite *s = suite_create("suite_sscanf");
  TCase *tc = tcase_create("sscanf_tc");

  tcase_add_test(tc, sscanf_1);
  tcase_add_test(tc, sscanf_2);
  tcase_add_test(tc, sscanf_3);
  tcase_add_test(tc, sscanf_4);
  tcase_add_test(tc, sscanf_5);
  tcase_add_test(tc, sscanf_6);
  tcase_add_test(tc, sscanf_7);
  tcase_add_test(tc, sscanf_8);
  tcase_add_test(tc, sscanf_9);
  tcase_add_test(tc, sscanf_10);
  tcase_add_test(tc, sscanf_11);
  tcase_add_test(tc, sscanf_12);
  tcase_add_test(tc, sscanf_13);
  tcase_add_test(tc, sscanf_14);
  tcase_add_test(tc, sscanf_15);
  tcase_add_test(tc, sscanf_16);

  suite_add_tcase(s, tc);
  return s;
}