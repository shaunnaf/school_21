#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  s21_big_decimal value_1_big = {0}, value_2_big = {0}, result_big = {0};
  s21_to_big(value_1, &value_1_big);
  s21_to_big(value_2, &value_2_big);
  int res = s21_mul_big(value_1_big, value_2_big, &result_big);
  res |= s21_from_big(result_big, result);
  return res;
}
