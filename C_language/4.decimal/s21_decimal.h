#ifndef _S21_SRC_DECIMAL_H_
#define _S21_SRC_DECIMAL_H_
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal_support.h"

/*------------------BASE_FUNCS----------------------*/
void s21_optimize_decimal(s21_decimal* value);
int s21_is_zero(s21_decimal value);
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
void s21_get_string_decimal(s21_decimal value, char* str);
void get_formatted_str_decimal(s21_decimal value, char*);
/*------------------SUPPORTING_FUNCS----------------*/

// int s21_less_comparing(s21_decimal value_1, s21_decimal value_2);
// неактуальная версия сравнения на меньший децимал
s21_decimal s21_to_positive(s21_decimal value_1);
int s21_is_zero(s21_decimal value_1);
// s21_big_decimal s21_to_big_decimal(s21_decimal value_1); тоже неактуальная
// функция преобразования деца в биг_дец
void s21_get_degree_diff_and_normalize(s21_decimal* value_1,
                                       s21_decimal* value_2);
void s21_normalize_degree(s21_decimal* value_1, int degree_diff);

int s21_comparison_int_bits(
    s21_decimal value_1,
    s21_decimal value_2);  // ПОБИТОВОЕ СРАВНЕНИЕ - ТРАЙХАРДОВЫЙ ВАРИАНТ
int s21_comparison_bits_int(s21_decimal value_1,
                            s21_decimal value_2);  // PRIORITY
// int s21_comparison_reverse(int flag);
int s21_exit_code_reverse_with_sign(int flag);

int s21_len(s21_decimal value);
int s21_div_recursive(s21_decimal* value_1, s21_decimal* value_2,
                      s21_decimal* result, int calcFractPart);
void s21_print_decimal_DEC(s21_decimal* value);
void s21_print_decimal_BIT(s21_decimal* value, int space);
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_from_decimal_to_float(s21_decimal src, float* dst);
int s21_from_float_to_decimal(float src, s21_decimal* dst);
int s21_from_decimal_to_int(s21_decimal src, int* dst);
int s21_from_int_to_decimal(int src, s21_decimal* dst);
int s21_left_shift(s21_decimal decimal, int shift, int save_degree,
                   s21_decimal* result);
int s21_right_shift(s21_decimal decimal, int shift, int save_degree,
                    s21_decimal* result);
typedef struct {
  unsigned int bits[8];
} s21_big_decimal;
void s21_align_big(s21_big_decimal* value_1, s21_big_decimal* value_2,
                   s21_big_decimal* result);
int s21_from_big(s21_big_decimal src, s21_decimal* dst);
void s21_to_big(s21_decimal src, s21_big_decimal* dst);
int s21_len_big(s21_big_decimal value);

int s21_add_bit(s21_big_decimal value_1, s21_big_decimal value_2,
                s21_big_decimal* result);
int s21_is_zero_arithmetic(s21_big_decimal value);
int s21_len_big(s21_big_decimal value);
int s21_mul_big(s21_big_decimal value_1, s21_big_decimal value_2,
                s21_big_decimal* result);
void s21_get_string_big_decimal(s21_big_decimal value, char* str);
int s21_right_shift_big(s21_big_decimal decimal, int shift, int save_degree,
                        s21_big_decimal* result);
void s21_get_string_big_decimal(s21_big_decimal value, char* str);
int s21_div_recursive_big(s21_big_decimal* value_1, s21_big_decimal* value_2,
                          s21_big_decimal* result, int calcFractPart);
int s21_is_less_arithmetic_big(s21_big_decimal value_1,
                               s21_big_decimal value_2);
int s21_num_len_str(char* str, int* fracPart);
int s21_nan_chek(float src);
int s21_max_check(float src);
int s21_convert(float src, char* str, s21_decimal* dst);
int s21_sum(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_left_shift_big(s21_big_decimal decimal, int shift, int save_degree,
                       s21_big_decimal* result);
void s21_help_for_convert(s21_decimal* value, char third[]);
#endif  //_S21_SRC_DECIMAL_H_
