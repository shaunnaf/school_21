#include <check.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "../s21_decimal.h"
static s21_decimal dst[] = {
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // 1
    {{0x000000FF, 0x00000000, 0x00000000, 0x00000000}},  // 255
    {{0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000}},  // 18446744073709551615
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543950335
};

static char *mul_res[] = {"+0.0000000000000000000000000000",
                          "+0.0000000000000000000000000000",
                          "+0.0000000000000000000000000000",
                          "+0.0000000000000000000000000008",
                          "+0.0000000000000000000000000001",
                          "+0.0000000000000000000000000255",
                          "+0.0000000018446744073709551615",
                          "+7.9228162514264337593543950335",
                          "+0.0000000000000000000000000000",
                          "+0.0000000000000000000000000000",
                          "+0.0000000000000000000000000000",
                          "+0.0000000000000000000000002020",
                          "+0.0000000000000000000000000255",
                          "+0.0000000000000000000000065025",
                          "+0.0000004703919738795935661825",
                          "+2020.3181441137406086353707335",
                          "+0.0000000000000000000000000000",
                          "+0.0000000000000000000000000000",
                          "+0.0000000000000000034028236692",
                          "+0.0000000146150163733090291812",
                          "+0.0000000018446744073709551615",
                          "+0.0000004703919738795935661825",
                          "+34028236692.093846342648111928",
                          "+146150163733090291812.44566702",
                          "+0.0000000000000000000000000008",
                          "+0.0000000000000000000000002020",
                          "+0.0000000146150163733090291812",
                          "+62.771017353866807638357894230",
                          "+7.9228162514264337593543950335",
                          "+2020.3181441137406086353707335",
                          "+146150163733090291812.44566702",
                          "+0.0000000000000000000000000000",
                          "+0.0000000000000000000000000001",
                          "+0.0000000000000000000000000255",
                          "+0.0000000018446744073709551615",
                          "+7.9228162514264337593543950335",
                          "+1",
                          "+255",
                          "+18446744073709551615",
                          "+79228162514264337593543950335",
                          "+0.0000000000000000000000000255",
                          "+0.0000000000000000000000065025",
                          "+0.0000004703919738795935661825",
                          "+2020.3181441137406086353707335",
                          "+255",
                          "+65025",
                          "+4703919738795935661825",
                          "+0.0000000000000000000000000000",
                          "+0.0000000018446744073709551615",
                          "+0.0000004703919738795935661825",
                          "+34028236692.093846342648111928",
                          "+146150163733090291812.44566702",
                          "+18446744073709551615",
                          "+4703919738795935661825",
                          "+0.0000000000000000000000000000",
                          "+0.0000000000000000000000000000",
                          "+7.9228162514264337593543950335",
                          "+2020.3181441137406086353707335",
                          "+146150163733090291812.44566702",
                          "+0.0000000000000000000000000000",
                          "+79228162514264337593543950335",
                          "+0.0000000000000000000000000000",
                          "+0.0000000000000000000000000000",
                          "+0.0000000000000000000000000000"};
START_TEST(test_mul) {
  s21_decimal dec1 = {0}, dec2 = {0};
  int index = 0;
  for (int x = 1; x >= 0; x--)
    for (size_t i = 0; i < 4; i++) {
      for (int t = 0; t < 4; t++) dec1.bits[t] = dst[i].bits[t];
      if (x) {
        _S_D_(dec1, 28);
      } else {
        _S_D_(dec1, 0);
      }
      for (int y = 1; y >= 0; y--)
        for (size_t j = 0; j < 4; j++) {
          for (int t = 0; t < 4; t++) dec2.bits[t] = dst[j].bits[t];
          if (y) {
            _S_D_(dec2, 28);
          } else {
            _S_D_(dec2, 0);
          }
          s21_decimal res = {0};
          int result = s21_mul(dec1, dec2, &res);
          char str_res[100] = {0};
          get_formatted_str_decimal(res, str_res);
          if (!result) {
            ck_assert_pstr_eq(str_res, mul_res[index]);
          }
          index++;
        }
    }
}

Suite *suite_mul_test(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_mul");
  tc = tcase_create("s21_mul");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, test_mul);
    //   tcase_add_test(tc, test1);
    suite_add_tcase(s, tc);
  }

  return (s);
}