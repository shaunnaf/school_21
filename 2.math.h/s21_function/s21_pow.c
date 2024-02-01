#include "../s21_math.h"

long double s21_pow(double base, double exp) {
  long double result = 0.0;
  if (base == 0 && exp > 0.0)
    result = 0.0;
  else if (base == 0 && exp < 0.0)
    result = S21_INF_POS;
  else if (base == 0 && exp == 0.0)
    result = 1.0;
  else if (exp == 0)
    result = 1.0;
  else {
    result = s21_exp(exp * s21_log(s21_fabs(base)));
    if (base < 0 && s21_fmod(exp, 2)) result = result * (-1);
  }
  return result;
}