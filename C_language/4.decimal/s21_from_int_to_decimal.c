#include "s21_decimal.h"
int s21_from_int_to_decimal(int src, s21_decimal* dst) {  //тесты проходит
  for (int i = 0; i < 4; i++) dst->bits[i] = 0;
  int sign = 1;

  if (src < 0) {
    _S_S_((*dst), -);
    sign = -1;
  }
  int absValue = src * sign;
  _S_D_((*dst), 0);
  int bit = 0;
  while (absValue != 0) {
    _S_B_((*dst), bit, absValue % 2);
    absValue /= 2;
    bit++;
  }

  return 0;
}