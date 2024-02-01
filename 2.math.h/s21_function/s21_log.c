#include "../s21_math.h"

long double s21_log(double x) {
  long double result = 0.0;
  if (x == 0)
    result = S21_INF_NEG;
  else if (x < 0)
    result = S21_NAN;
  else {
    int count = 0;
    for (; x >= S21_E; count++) x /= S21_E;
    long double temp = 0.0;
    for (int i = 0; i < 10; i++) {
      temp = result;
      result = temp + 2 * (x - s21_exp(temp)) / (x + s21_exp(temp));
    }
    result += count;
  }
  return result;
}
