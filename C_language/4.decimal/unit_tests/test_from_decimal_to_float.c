#include <check.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "../s21_decimal.h"

static s21_decimal src[] = {
    {{0x000026B9, 0x00000000, 0x00000000, 0x00030000}},
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},
    {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},
    {{0x00000002, 0x00000000, 0x00000000, 0x00000000}},
    {{0x00000002, 0x00000000, 0x00000000, 0x80000000}},
    {{0x0000000F, 0x00000000, 0x00000000, 0x00010000}},
    {{0x0000000F, 0x00000000, 0x00000000, 0x80010000}},
    {{0x00000009, 0x00000000, 0x00000000, 0x00010000}},
    {{0x00000009, 0x00000000, 0x00000000, 0x80010000}},
    {{0x00000001, 0x00000000, 0x00000000, 0x80010000}},
    {{0x00000001, 0x00000000, 0x00000000, 0x00010000}},
    {{0x0000000B, 0x00000000, 0x00000000, 0x80010000}},
    {{0x0000000B, 0x00000000, 0x00000000, 0x00010000}},
    {{0x000031DD, 0x00000000, 0x00000000, 0x00030000}},
    {{0x00002F0D, 0x00000000, 0x00000000, 0x80030000}},
    {{0x0001869F, 0x00000000, 0x00000000, 0x00040000}},
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}},
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}},
    {{0x000000D3, 0x00007C45, 0x00007C57, 0x80080000}},
    {{0x003A6E50, 0x007F1483, 0x003215CF, 0x00020000}},
    {{0x00000000, 0x00000000, 0x00000000, 0x800A0000}},
    {{0xF533512E, 0x0000004B, 0x00000000, 0x00060000}},
    {{0x51A337CD, 0x00000002, 0x00000000, 0x80040000}},
    {{0xDC425734, 0x01C068FA, 0x00000000, 0x00070000}},
    {{0xCC133B70, 0x004D86D4, 0x00000000, 0x000B0000}},
    {{0x00000001, 0x00000000, 0x00000000, 0x00140000}},
};

static float dst[] = {
    9.91300011f,
    0.f,
    1.f,
    -1.f,
    2.f,
    -2.f,
    1.5f,
    -1.5f,
    0.899999976f,
    -0.899999976f,
    -0.100000001f,
    0.100000001f,
    -1.10000002f,
    1.10000002f,
    12.7650003f,
    -12.0450001f,
    9.99989986f,
    79228162500000000000000000000.f,
    -79228162500000000000000000000.f,
    -5871782930000000.f,
    605492757000000000000000.f,
    0.f,
    326236.344f,
    -995958.563f,
    12621621200.f,
    218218.219f,
    9.99999968E-21f,
};

START_TEST(test) {
  float tmp;
  int ret = s21_from_decimal_to_float(src[0], &tmp);
  if (tmp != dst[0]) {
    char buf1[512];
    char buf2[512];
    sprintf(buf1, "%.6E", tmp);
    sprintf(buf2, "%.6E", dst[0]);

    ck_assert(strcmp(buf1, buf2) == 0);
  } else {
    ck_assert_float_eq(tmp, dst[0]);
    ck_assert_int_eq(ret, 0);
  }
}
END_TEST
START_TEST(test1) {
  float tmp;
  int ret = s21_from_decimal_to_float(src[1], &tmp);
  if (tmp != dst[1]) {
    char buf1[512];
    char buf2[512];
    sprintf(buf1, "%.6E", tmp);
    sprintf(buf2, "%.6E", dst[1]);

    ck_assert(strcmp(buf1, buf2) == 0);
  } else {
    ck_assert_float_eq(tmp, dst[1]);
    ck_assert_int_eq(ret, 0);
  }
}
END_TEST

Suite *suite_from_decimal_to_float(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_from_decimal_to_float");
  tc = tcase_create("s21_from_decimal_to_float");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, test);
    tcase_add_test(tc, test1);
    suite_add_tcase(s, tc);
  }

  return (s);
}
