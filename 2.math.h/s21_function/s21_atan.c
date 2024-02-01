
#include "../s21_math.h"

/* У арктангенса на удивление одз от -inf до +inf
Разложение Маклорена
Нужно заменить на pow и sqrt на функции Алины и потестить
*/
long double s21_atan(double x) {
  long double result = 0;

  if (x == 0.0) {
    result = 0.0;

  } else if (x == 1.0 || x == -1.0) {
    result = (x == 1.0) ? S21_PI / 4.0 : S21_PI / 4.0 * (-1);

  } else if (-1.0 < x && x < 1.0) {
    for (register int i = 0; i < 5000; i++) {
      result += s21_pow(-1, i) * s21_pow(x, 1 + (2 * i)) / ((2 * i) + 1);
    }
  } else {
    for (register int i = 0; i < 7000; i++) {
      result += s21_pow(-1, i) * s21_pow(x, -1 - (2 * i)) / ((2 * i) + 1);
    }
    result = S21_PI * s21_sqrt(x * x) / (2 * x) - result;
  }

  return result;
}
