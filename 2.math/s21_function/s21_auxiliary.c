#include "../s21_math.h"

long double s21_auxiliary(double base, double exp) {
  long double result = 1.0;
  if (base == 0 && exp > 0.0)
    result = 0.0;
  else if (base == 0 && exp == 0.0)
    result = 1.0;
  else if (exp == 0)
    result = 1.0;
  else {
    if (exp > 0) {
      for (int i = 0; i < exp; i++) result *= base;
    } else if (exp < 0) {
      for (int i = 0; i > exp; i--) result /= base;
    }
  }
  return result;
}
