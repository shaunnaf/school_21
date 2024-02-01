#include "../s21_math.h"

long double s21_fmod(double x, double y) {
  long double result = 0.0;
  if (y == 0)
    result = S21_NAN;
  else {
    int n = x / y;
    result = x - n * y;
  }
  return result;
}