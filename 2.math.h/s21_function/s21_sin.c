#include "../s21_math.h"

long double s21_sin(double x) {
  while (s21_fabs(x) - 2 * S21_PI > 0) {
    x += 2 * S21_PI * x / s21_fabs(x) * -1;  // заменить на s21_fabs;
  }

  long double result = 0;
  long double x_squared =
      x * x;  // для уменьшения количества повторных умножений в цикле
  long double term = x;

  for (register int i = 1; i <= 15; i++) {  // подумать с итерациями
    result += term;
    term *= -x_squared / ((2 * i) * (2 * i + 1));
  }

  return result;
}
