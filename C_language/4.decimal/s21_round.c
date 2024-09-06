#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal* result) {
  int degree = _G_D_(value);
  int return_result = 0;
  for (int i = 0; i < 4; i++) result->bits[i] = 0;
  if (degree > 28) {
    return_result = 1;
  } else {
    int degree_tmp = degree;
    char str[150] = {0};
    int sign = _G_S_(value) 1;
    s21_decimal tmp = {{0x00000001, 0x00000000, 0x00000000, 0x00000000}};
    s21_get_string_decimal(value, str);
    while (degree > 0) {
      s21_right_shift(value, 1, TRUE, &value);
      degree--;
    }
    if (sign > 0) {
      _S_S_((tmp), +);
    } else {
      _S_S_((tmp), -);
    }

    _S_D_(value, 0);
    _S_D_(tmp, 0);
    int not_null = 0;
    for (int i = 0; i < degree_tmp; i++) {
      if (str[i] - '0' != 0) {
        not_null++;
      }
    }
    int num_after_point = str[degree_tmp] - '0';

    if (str[degree_tmp - 1] - '0' >= 5 &&
        (num_after_point % 2 != 0 || (degree_tmp > 1 && not_null > 1))) {
      s21_add(value, tmp, &value);
    }
    (*result) = value;
  }
  return return_result;
}