#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  if (_IS_POS_(value_2)) {
    _S_S_(value_2, -);
  } else {
    _S_S_(value_2, +);
  }
  return s21_sum(value_1, value_2, result);
}
