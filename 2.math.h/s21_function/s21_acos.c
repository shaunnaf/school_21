#include "../s21_math.h"
// ОДЗ [-1; 1] иначе NAN
long double s21_acos(double x) {
  if (0 < x && x <= 1) {
    return s21_atan(s21_sqrt(1 - x * x) / x);
  } else if (-1.0 < x && x < 0) {
    return S21_PI + s21_atan(s21_sqrt(1 - x * x) / x);
  } else if (x == 0) {
    return S21_PI_2;
  } else if (x == -1) {
    return S21_PI;
  } else {
    return S21_NAN;
  }
}
