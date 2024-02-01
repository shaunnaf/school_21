#include "../s21_math.h"

long double s21_exp(double x) {
  long double result = 0.0;
  long double k = (long long)(x / S21_LN2);
  long double r = x - k * S21_LN2;
  int i = 0;
  while (1) {
    long double current = s21_auxiliary(r, i) / s21_factorial(i);
    if (s21_fabs(current) < 0.00000001) break;
    result += current;
    i++;
  }
  result *= s21_auxiliary(2, k);
  return (x == 0) ? 1.0 : result;
}
