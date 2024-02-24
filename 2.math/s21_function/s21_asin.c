#include "../s21_math.h"
// ОДЗ [-1; 1] иначе NAN

long double s21_asin(double x) {
  if (-1.0 < x && x < 1.0) {
    return s21_atan(x / s21_sqrt(1.0 - x * x));
  } else if (x == 1.0) {
    return S21_PI_2;
  } else if (x == -1.0) {
    return -S21_PI_2;
  } else {
    return S21_NAN;
  }
}