#include <check.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "../s21_decimal.h"
static s21_decimal dst[] = {
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // 1
    {{0x00000002, 0x00000000, 0x00000000, 0x00000000}},  // 2
    {{0x000000FF, 0x00000000, 0x00000000, 0x00000000}},  // 255
    {{0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000}},  // 18446744073709551615
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543950335
};

static int greate_equal[] = {
    1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1,
    0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0,
    1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
    0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1,
    1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
    0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
    1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
    0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
    0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0,
    0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
    1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1,
    1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1,
    1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0,
    0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
    1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1,
    1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1};

START_TEST(test_greater_equal) {
  s21_decimal dec1 = {0}, dec2 = {0};
  int index = 0;
  for (int x = 1; x >= 0; x--)
    for (size_t i = 0; i < 5; i++) {
      for (int t = 0; t < 4; t++) dec1.bits[t] = dst[i].bits[t];
      if (!x) {
        _S_D_(dec1, 28);
      } else {
        _S_D_(dec1, 0);
      }
      for (int y = 1; y >= 0; y--)
        for (size_t j = 0; j < 5; j++) {
          for (int t = 0; t < 4; t++) dec2.bits[t] = dst[j].bits[t];
          if (!y) {
            _S_D_(dec2, 28);
          } else {
            _S_D_(dec2, 0);
          }

          _S_S_(dec1, +);
          _S_S_(dec2, +);
          ck_assert_int_eq(s21_is_greater_or_equal(dec1, dec2),
                           greate_equal[index++]);
          _S_S_(dec1, -);
          _S_S_(dec2, +);
          ck_assert_int_eq(s21_is_greater_or_equal(dec1, dec2),
                           greate_equal[index++]);
          _S_S_(dec1, +);
          _S_S_(dec2, -);
          ck_assert_int_eq(s21_is_greater_or_equal(dec1, dec2),
                           greate_equal[index++]);
          _S_S_(dec1, -);
          _S_S_(dec2, -);
          ck_assert_int_eq(s21_is_greater_or_equal(dec1, dec2),
                           greate_equal[index++]);
        }
    }
}

Suite *suite_greate_equal_test(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_greater_equal");
  tc = tcase_create("s21_greater_equal");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, test_greater_equal);
    suite_add_tcase(s, tc);
  }

  return (s);
}