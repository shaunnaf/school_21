#include "s21_decimal.h"
int s21_from_decimal_to_float(s21_decimal src, float* dst) {
  char tmp[512];
  s21_help_for_convert(&src, tmp);
  *dst = atof(tmp);
  return 0;
}