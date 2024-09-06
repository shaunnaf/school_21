#include "s21_decimal.h"
int s21_negate(s21_decimal value, s21_decimal* result) {
  int degree = _G_D_(value);
  int result_of_function = 0;
  if (degree > 28) {
    result_of_function = 1;
  } else {
    int sign = _G_S_(value) 1;
    printf("%d", sign);
    (*result) = value;
    if (sign > 0) {
      _S_S_((*result), -);
    } else {
      _S_S_((*result), +);
    }
  }

  return result_of_function;
}