#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

int s21_is_less(s21_decimal value1, s21_decimal value2) {
  return s21_is_greater(value2, value1);
}

int s21_is_less_or_equal(s21_decimal value1, s21_decimal value2) {
  return s21_is_greater_or_equal(value2, value1);
}

int s21_is_greater(s21_decimal value1, s21_decimal value2) {
  int result = FALSE;
  int sign1 = _IS_POS_(value1), sign2 = _IS_POS_(value2);
  if (sign1 > sign2)
    result = TRUE;
  else if (sign1 == sign2) {
    s21_big_decimal b_value1 = {0}, b_value2 = {0}, tmp = {0};
    if (sign1) {
      s21_to_big(value1, &b_value1);
      s21_to_big(value2, &b_value2);
    } else {
      s21_to_big(value2, &b_value1);
      s21_to_big(value1, &b_value2);
    }
    s21_align_big(&b_value1, &b_value2, &tmp);
    int len1 = s21_len_big(b_value1), len2 = s21_len_big(b_value2);
    if (len1 >= len2)
      for (int i = len1 - 1; i >= 0 && !result; i--)
        if (_G_B_(b_value1, i) > _G_B_(b_value2, i)) result = TRUE;
  }
  return result;
}

int s21_is_greater_or_equal(s21_decimal value1, s21_decimal value2) {
  return s21_is_equal(value1, value2) || s21_is_greater(value1, value2);
}

int s21_is_equal(s21_decimal value1, s21_decimal value2) {
  int result = FALSE;
  int sign1 = _IS_POS_(value1), sign2 = _IS_POS_(value2);
  if (sign1 == sign2) {
    s21_big_decimal b_value1 = {0}, b_value2 = {0}, tmp = {0};
    s21_to_big(value1, &b_value1);
    s21_to_big(value2, &b_value2);
    s21_align_big(&b_value1, &b_value2, &tmp);
    int len1 = s21_len_big(b_value1), len2 = s21_len_big(b_value2);
    if (len1 == len2) {
      result = TRUE;
      for (int i = 0; i < len1 && result; i++)
        if (_G_B_(b_value1, i) != _G_B_(b_value2, i)) result = FALSE;
    }
  }
  return result;
}

int s21_is_not_equal(s21_decimal value1, s21_decimal value2) {
  return !s21_is_equal(value1, value2);
}