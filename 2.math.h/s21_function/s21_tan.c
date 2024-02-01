#include "../s21_math.h"

long double s21_tan(double x) {
  if (s21_cos(x) == 0) {
    return S21_NAN;
  } else {
    return s21_sin(x) / s21_cos(x);
  }
}
