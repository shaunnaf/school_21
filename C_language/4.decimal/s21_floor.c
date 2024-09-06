#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal* result) {
  int not_null = 0;
  int degree = _G_D_(value);
  int degree_tmp = degree;
  int return_result = 0;

  s21_decimal tmp = {{0x00000001, 0x00000000, 0x00000000, 0x00000000}};
  for (int i = 0; i < 4; i++) {
    result->bits[i] = 0;
  }

  if (degree > 28) {
    return_result = 1;
  } else {
    char str[150] = {0};
    s21_get_string_decimal(value, str);

    int sign = _G_S_(value) 1;
    if (strlen(str) > 0) {
      if (sign > 0) {
        while (degree > 0) {
          s21_right_shift(value, 1, TRUE, &value);
          degree--;
        }
      } else {
        while (degree > 0) {
          s21_right_shift(value, 1, TRUE, &value);
          degree--;
        }
        _S_D_(value, 0);
        _S_D_(tmp, 0);
        for (int i = 0; i < degree_tmp; i++) {
          if (str[i] - '0' != 0) {
            not_null++;
          }
        }

        if (degree_tmp > 0 && not_null != 0) {
          s21_sub(value, tmp, &value);
        }
      }
    } else {
      _S_D_(value, 0);
    }
    *result = value;
  }

  return return_result;
}