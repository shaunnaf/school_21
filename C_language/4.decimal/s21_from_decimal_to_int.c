#include "s21_decimal.h"
int s21_from_decimal_to_int(s21_decimal src, int* dst) {
  int degree = _G_D_(src);
  int result = 0;
  if (degree > 28) {
    result = 1;
  } else {
    *dst = 0;

    int sign = _G_S_(src) 1;

    while (degree > 0) {
      s21_right_shift(src, 1, TRUE, &src);
      // degree = _G_D_(src);
      // s21_print_decimal_DEC(&src);
      // printf("\n");
      degree--;
    }
    unsigned int unint = src.bits[0];
    if (src.bits[1] != 0 || src.bits[2] != 0 || unint > 2147483647u) {
      result = 1;
    } else {
      *dst = sign * src.bits[0];
    }
    while (degree > 0) {
      *dst = *dst / 10;
      degree--;
    }
  }

  return result;
}