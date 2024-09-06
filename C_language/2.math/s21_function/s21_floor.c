#include "../s21_math.h"

long double s21_floor(double x) {
  long double result = (long long)x;
  if (x < 0 && (x - result)) result--;
  return (long double)result;
}