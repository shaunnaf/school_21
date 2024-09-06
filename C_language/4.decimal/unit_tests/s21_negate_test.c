#include <check.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "../s21_decimal.h"

static s21_decimal arr[] = {
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},
    {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},
    {{0xCF5C048C, 0x004D2BEF, 0x00000000, 0x00070000}},
    {{0xFEADBDA2, 0x000001FB, 0x00000000, 0x80060000}},
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}},
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}},
    {{0x00000000, 0x00000000, 0x00000000, 0x00020000}},
    {{0x00000000, 0x00000000, 0x00000000, 0x80020000}},
    {{0x000F4240, 0x00000000, 0x00000000, 0x00020000}},
    {{0x000F4240, 0x00000000, 0x00000000, 0x80020000}},
    {{0x00000467, 0x0000007A, 0x00000000, 0x00040000}},
    {{0x00000467, 0x0000007A, 0x00000000, 0x80000000}},
    {{0x00000467, 0x0000007A, 0x00003215, 0x00010000}},
    {{0x00000467, 0x0000007A, 0x00205FF0, 0x80020000}},
    {{0x000F4240, 0x00002710, 0x00002710, 0x80050000}},
};

static s21_decimal result[] = {
    {{0x00000000, 0x00000000, 0x00000000, 0x80000000}},  // 0
    {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},  //-1
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // 1
    {{0xCF5C048C, 0x004D2BEF, 0x00000000, 0x80070000}},  //-2172188218.2812812
    {{0xFEADBDA2, 0x000001FB, 0x00000000, 0x00060000}},  // 2181821.218210
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}},
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}},
    {{0x00000000, 0x00000000, 0x00000000, 0x80020000}},
    {{0x00000000, 0x00000000, 0x00000000, 0x00020000}},
    {{0x000F4240, 0x00000000, 0x00000000, 0x80020000}},
    {{0x000F4240, 0x00000000, 0x00000000, 0x00020000}},
    {{0x00000467, 0x0000007A, 0x00000000, 0x80040000}},
    {{0x00000467, 0x0000007A, 0x00000000, 0x00000000}},
    {{0x00000467, 0x0000007A, 0x00003215, 0x80010000}},
    {{0x00000467, 0x0000007A, 0x00205FF0, 0x00020000}},
    {{0x000F4240, 0x00002710, 0x00002710, 0x00050000}},
};

START_TEST(test) {
  for (size_t i = 0; i < sizeof(arr) / sizeof(s21_decimal); ++i) {
    s21_decimal value = arr[i];
    s21_decimal tmp;
    int ret = s21_negate(value, &tmp);
    ck_assert_int_eq(result[i].bits[0], tmp.bits[0]);
    ck_assert_int_eq(result[i].bits[1], tmp.bits[1]);
    ck_assert_int_eq(result[i].bits[2], tmp.bits[2]);
    ck_assert_int_eq(result[i].bits[3], tmp.bits[3]);
    ck_assert_int_eq(ret, 0);
  }
}
END_TEST

Suite *suite_negate(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_negate");
  tc = tcase_create("s21_negate");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, test);
    suite_add_tcase(s, tc);
  }

  return (s);
}
