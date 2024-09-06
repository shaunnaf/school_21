#include "../s21_math.h"

// ОДЗ от -inf до +inf
long double s21_cos(double x) { return s21_sin(x + S21_PI / 2.0); }
