#ifndef S21_MATH_H
#define S21_MATH_H

#include <stdio.h>

#define S21_PI 3.1415926535897932
#define S21_E 2.7182818284590452
#define S21_PI_2 1.57079632679489661923

#define S21_LN2 0.6931471805599453

#define S21_NAN __builtin_nanf("")
#define S21_INF_POS __builtin_inf()
#define S21_INF_NEG -S21_INF_POS

int s21_abs(int x);
long double s21_fabs(double x);
long double s21_fmod(double x, double y);
long double s21_ceil(double x);
long double s21_floor(double x);
long double s21_factorial(int x);
long double s21_auxiliary(double base, double exp);
long double s21_pow(double base, double exp);
long double s21_sqrt(double x);
long double s21_exp(double x);
long double s21_log(double x);
long double s21_acos(double x);
long double s21_asin(double x);
long double s21_atan(double x);
long double s21_cos(double x);
long double s21_sin(double x);
long double s21_tan(double x);

#endif