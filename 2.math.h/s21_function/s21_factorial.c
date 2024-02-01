#include "../s21_math.h"

long double s21_factorial(int x) {
  long double result = 1;
  if (x == 0) result = 1;
  if (x > 0) {
    for (int i = 1; i <= x; i++) result = result * i;
  }
  return (x < 0) ? S21_NAN : result;
}