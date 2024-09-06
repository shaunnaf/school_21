#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int res = 0;
  s21_big_decimal value_1_b = {0}, value_2_b = {0}, result_b = {0};
  s21_to_big(value_1, &value_1_b);
  s21_to_big(value_2, &value_2_b);
  if (s21_is_zero_arithmetic(value_2_b)) res = 3;
  if (s21_is_zero_arithmetic(value_1_b))
    for (int i = 0; i < 4; i++) result->bits[i] = 0;
  else {
    for (int i = 0; i < 4; i++) result->bits[i] = 0;
    int sign = _G_S_(value_1) 1 == _G_S_(value_2) 1;
    int deg = _G_D_(value_1_b) - _G_D_(value_2_b);
    if (deg >= 0) {
      s21_left_shift_big(value_2_b, deg, 1, &value_2_b);
    } else {
      s21_left_shift_big(value_1_b, -deg, 1, &value_1_b);
    }
    res = s21_div_recursive_big(&value_1_b, &value_2_b, &result_b, 1);
    if (sign)
      _S_S_((*result), +)
    else
      _S_S_((*result), -)
    res = s21_from_big(result_b, result);
  }
  return res;
}
