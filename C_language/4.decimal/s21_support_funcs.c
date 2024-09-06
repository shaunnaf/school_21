#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

double s21_pow(double x, double y) {
  double res = 1;
  while (y != 0) {
    res *= x;
    y--;
  }
  return res;
}

s21_decimal s21_to_positive(s21_decimal value_1) {
  s21_decimal result = value_1;
  _S_S_(result, +);
  return result;
}

void s21_to_big(s21_decimal src, s21_big_decimal* dst) {
  dst->bits[0] = src.bits[0];
  dst->bits[1] = src.bits[1];
  dst->bits[2] = src.bits[2];
  dst->bits[7] = src.bits[3];
}

void s21_optimize_big_decimal(s21_big_decimal* value) {
  char str_num[100] = {0};
  s21_get_string_big_decimal(*value, str_num);
  size_t i = 0;
  int deg = _G_D_((*value));
  while (str_num[i] == '0' && deg > (int)i && i < (strlen(str_num) - 1llu)) i++;
  s21_right_shift_big(*value, (int)i, 1, value);
  _S_D_((*value), deg - i);
}

int s21_from_big(s21_big_decimal src, s21_decimal* dst) {
  int res = 0, deg = _G_D_(src), startLen = s21_len_big(src);
  size_t index = 0;
  char str[100] = {0};
  s21_get_string_big_decimal(src, str);
  while (deg > 0 && (index < strlen(str)) &&
         (deg > 28 || src.bits[3] != 0 || src.bits[4] != 0 ||
          src.bits[5] != 0 || src.bits[6] != 0)) {
    s21_right_shift_big(src, 1, 1, &src);
    deg--;
    index++;
    _S_D_(src, deg);
  }

  if (index != 0llu) {
    char num = str[index - 1llu] - '0';
    if (num > 5 || (num == 5 && ((str[index] - '0') % 2) != 0)) {
      s21_big_decimal tmp = {{1, 0, 0, 0, 0, 0, 0, 0}};
      s21_add_bit(src, tmp, &src);
    }
  }

  if (src.bits[3] != 0 || src.bits[4] != 0 || src.bits[5] != 0 ||
      src.bits[6] != 0)
    res = 1;
  else if (_G_D_(src) > 28 || (startLen != 0 && s21_len_big(src) == 0)) {
    res = 2;
  }

  dst->bits[0] = src.bits[0];
  dst->bits[1] = src.bits[1];
  dst->bits[2] = src.bits[2];
  dst->bits[3] = src.bits[7];
  return res;
}

void s21_get_string_big_decimal(s21_big_decimal value, char* str) {
  char double_deg[100] = {0};
  double_deg[0] = '1';
  int len_dec = s21_len_big(value);
  for (int i = 0; i < len_dec; i++) {
    if (_G_B_(value, i) == 1) {
      int mem = 0;
      for (int j = 0; j < (int)strlen(double_deg); j++) {
        int num = 0;
        if (str[j] != '\0') num = str[j] - '0';
        num += double_deg[j] - '0' + mem;
        if (num > 9) {
          num -= 10;
          mem = 1;
        } else
          mem = 0;
        str[j] = num + '0';
      }
      if (mem != 0) str[strlen(str)] = mem + '0';
    }
    int mem = 0;
    char tmp[100] = {0};
    for (int j = 0; j < (int)strlen(double_deg); j++) {
      int num = 0;
      if (double_deg[j] != '\0') num = double_deg[j] - '0';
      num = (double_deg[j] - '0') * 2 + mem;
      if (num > 9) {
        mem = 1;
        num -= 10;
      } else
        mem = 0;
      tmp[j] = num + '0';
    }
    if (mem != 0) tmp[strlen(tmp)] = mem + '0';
    strcpy(double_deg, tmp);
  }
}

void s21_get_string_decimal(s21_decimal value, char* str) {
  char double_deg[40] = {0};
  double_deg[0] = '1';
  int len_dec = s21_len(value);
  for (int i = 0; i < len_dec; i++) {
    if (_G_B_(value, i) == 1) {
      int mem = 0;
      for (int j = 0; j < (int)strlen(double_deg); j++) {
        int num = 0;
        if (str[j] != '\0') num = str[j] - '0';
        num += double_deg[j] - '0' + mem;
        if (num > 9) {
          num -= 10;
          mem = 1;
        } else
          mem = 0;
        str[j] = num + '0';
      }
      if (mem != 0) str[strlen(str)] = mem + '0';
    }
    int mem = 0;
    char tmp[40] = {0};
    for (int j = 0; j < (int)strlen(double_deg); j++) {
      int num = 0;
      if (double_deg[j] != '\0') num = double_deg[j] - '0';
      num = (double_deg[j] - '0') * 2 + mem;
      if (num > 9) {
        mem = 1;
        num -= 10;
      } else
        mem = 0;
      tmp[j] = num + '0';
    }
    if (mem != 0) tmp[strlen(tmp)] = mem + '0';
    strcpy(double_deg, tmp);
  }
}

void s21_help_for_convert(s21_decimal* value, char third[]) {
  char double_deg[40] = {0};
  char string_num[40] = {0};
  double_deg[0] = '1';
  int len_dec = s21_len(*value);
  for (int i = 0; i < len_dec; i++) {
    if (_G_B_((*value), i) == 1) {
      int mem = 0;
      for (size_t j = 0; j < strlen(double_deg); j++) {
        int num = 0;
        if (string_num[j] != '\0') num = string_num[j] - '0';
        num += double_deg[j] - '0' + mem;
        if (num > 9) {
          num -= 10;
          mem = 1;
        } else
          mem = 0;
        string_num[j] = num + '0';
      }
      if (mem != 0) string_num[strlen(string_num)] = mem + '0';
    }
    int mem = 0;
    char tmp[40] = {0};
    for (size_t j = 0; j < strlen(double_deg); j++) {
      int num = 0;
      if (double_deg[j] != '\0') num = double_deg[j] - '0';
      num = (double_deg[j] - '0') * 2 + mem;
      if (num > 9) {
        mem = 1;
        num -= 10;
      } else
        mem = 0;
      tmp[j] = num + '0';
    }
    if (mem != 0) tmp[strlen(tmp)] = mem + '0';
    strcpy(double_deg, tmp);
  }

  int deg = _G_D_((*value));
  if (deg >= (int)strlen(string_num)) {
    snprintf(third, 512, "%s", "0.");

    for (int i = 0; i < deg - (int)strlen(string_num); i++) {
      snprintf(third, 512, "%s", "0");
    }
  }
  char* tmp = {0};
  tmp = third;
  for (int i = (int)strlen(string_num) - 1; i >= 0; i--) {
    snprintf(tmp, 511, "%c", string_num[i]);
    tmp++;

    if (deg == i && i != 0lu) {
      snprintf(tmp, 511, "%s", ".");

      tmp++;
    }
  }
};

int s21_left_shift_big(s21_big_decimal decimal, int shift, int save_degree,
                       s21_big_decimal* result) {
  int res = 0;
  if (shift != 0) {
    if (!save_degree) {
      int new_degree = _G_D_(decimal) + shift;
      if (new_degree > 29) {
        res = 1;
      } else {
        _S_D_(decimal, new_degree);
      }
    }
    if (!res) {
      s21_big_decimal ten = {0};
      ten.bits[0] = 10;
      *result = decimal;
      for (int i = 0; i < shift && !res; i++)
        res = s21_mul_big(*result, ten, result);
    }
  }
  return res;
}

int s21_left_shift(s21_decimal decimal, int shift, int save_degree,
                   s21_decimal* result) {
  int res = 0;
  if (shift != 0) {
    if (!save_degree) {
      int new_degree = _G_D_(decimal) + shift;
      if (new_degree > 28) {
        res = 1;
      } else {
        _S_D_(decimal, new_degree);
      }
    }
    if (!res) {
      s21_decimal ten = {0};
      ten.bits[0] = 10;
      *result = decimal;
      for (int i = 0; i < shift && !res; i++)
        res = s21_mul(*result, ten, result);
    }
  }
  return res;
}
int s21_right_shift_big(s21_big_decimal decimal, int shift, int save_degree,
                        s21_big_decimal* result) {
  int res = 0;
  if (shift != 0) {
    s21_big_decimal ten = {0};
    ten.bits[0] = 10;
    int sign = _G_S_(decimal) 1;
    for (int i = 0; i < shift && !res; i++) {
      for (int i = 0; i < 8; i++) result->bits[i] = 0;
      res = s21_div_recursive_big(&decimal, &ten, result, !save_degree);

      decimal = *result;
    }
    if (sign == 1)
      _S_S_((*result), +)
    else
      _S_S_((*result), -)
  }
  return res;
}
int s21_right_shift(s21_decimal decimal, int shift, int save_degree,
                    s21_decimal* result) {
  int res = 0;
  if (shift != 0) {
    s21_decimal ten = {0};
    ten.bits[0] = 10;
    int sign = _G_S_(decimal) 1;
    for (int i = 0; i < shift && !res; i++) {
      for (int i = 0; i < 4; i++) result->bits[i] = 0;
      res = s21_div_recursive(&decimal, &ten, result, !save_degree);

      decimal = *result;
    }
    if (sign == 1)
      _S_S_((*result), +)
    else
      _S_S_((*result), -)
  }
  return res;
}

void s21_optimize_decimal(s21_decimal* value) {
  char str_num[40] = {0};
  s21_get_string_decimal(*value, str_num);
  size_t i = 0;
  int deg = _G_D_((*value));
  while (str_num[i] == '0' && deg > (int)i && i < (strlen(str_num) - 1llu)) i++;
  s21_right_shift(*value, (int)i, 1, value);
  _S_D_((*value), deg - i);
}
int s21_add_bit(s21_big_decimal value_1, s21_big_decimal value_2,
                s21_big_decimal* result) {
  int res = 0;
  int member = 0;
  for (int i = 0; i < 224; i++) {
    int bit1 = _G_B_(value_1, i), bit2 = _G_B_(value_2, i),
        res = bit1 + bit2 + member;
    member = 0;
    if (res > 1) {
      member = 1;
      res -= 2;
    }
    _S_B_((*result), i, res);
  }
  if (member != 0) res = 1;
  return res;
}

int s21_sub_bit(s21_big_decimal value_1, s21_big_decimal value_2,
                s21_big_decimal* result) {
  int res = 0;
  for (int i = 0; i < 7; i++) result->bits[i] = 0;
  int member = 0;
  for (int i = 0; i < 224; i++) {
    int res = _G_B_(value_1, i) - _G_B_(value_2, i) - member;
    member = 0;
    if (res < 0) {
      member = 1;
      res += 2;
    }
    _S_B_((*result), i, res);
  }
  if (member != 0) res = 2;
  return res;
}

void s21_align_big(s21_big_decimal* value_1, s21_big_decimal* value_2,
                   s21_big_decimal* result) {
  int deg1 = _G_D_((*value_1)), deg2 = _G_D_((*value_2));
  if (deg1 < deg2) {
    s21_left_shift_big(*value_1, deg2 - deg1, 0, value_1);
    _S_D_((*result), deg2);
  } else if (deg1 > deg2) {
    s21_left_shift_big(*value_2, deg1 - deg2, 0, value_2);
    _S_D_((*result), deg1);
  } else {
    _S_D_((*result), deg1);
  }
}

typedef int (*operation)(s21_big_decimal, s21_big_decimal, s21_big_decimal*);

void s21_get_max_big(s21_big_decimal* value1, s21_big_decimal* value2,
                     s21_big_decimal* result) {
  if (s21_is_less_arithmetic_big(*value1, *value2)) {
    s21_big_decimal temp = *value1;
    *value1 = *value2;
    *value2 = temp;
  }
  if (_IS_POS_((*value1)))
    _S_S_((*result), +)
  else
    _S_S_((*result), -)
}

operation s21_get_operation(s21_big_decimal* value1, s21_big_decimal* value2) {
  operation res = 0;
  int sign1 = _G_S_((*value1)) 1 + 1, sign2 = _G_S_((*value2)) 1 + 1;
  if (sign1 == sign2) {
    res = s21_add_bit;
  } else {
    res = s21_sub_bit;
  }
  return res;
}

int s21_mul_big(s21_big_decimal value_1, s21_big_decimal value_2,
                s21_big_decimal* result) {
  int res = 0;
  for (int i = 0; i < 8; i++) result->bits[i] = 0;
  int devider = _G_D_(value_1) + _G_D_(value_2);
  if (_G_S_(value_1) 1 == _G_S_(value_2) 1)
    _S_S_((*result), +)
  else
    _S_S_((*result), -)
  int len1 = s21_len_big(value_1), len2 = s21_len_big(value_2);
  for (int j = 0; j < len2 && !res; j++) {
    if (_G_B_(value_2, j)) {
      int member = 0;
      for (int i = 0; (i < len1 || (member != 0 && i < 224)) && !res; i++) {
        int tmpres = _G_B_((*result), i + j) + _G_B_(value_1, i) + member;
        member = 0;
        if (tmpres > 1) {
          member = 1;
          tmpres -= 2;
        }
        _S_B_((*result), i + j, tmpres);
        if (member != 0 && i >= len1) res = 1;
      }
    }
  }
  _S_D_((*result), devider);
  return res;
}

int s21_len(s21_decimal value) {
  int i = 96;
  for (; i >= 1 && !_G_B_(value, i - 1); i--)
    ;
  return i;
}

int s21_len_big(s21_big_decimal value) {
  int i = 224;
  for (; i >= 1 && !_G_B_(value, i - 1); i--)
    ;
  return i;
}

void s21_print_decimal_DEC(s21_decimal* value) {
  char double_deg[40] = {0}, string_num[40] = {0};
  double_deg[0] = '1';
  int len_dec = s21_len(*value);
  for (int i = 0; i < len_dec; i++) {
    if (_G_B_((*value), i) == 1) {
      int mem = 0;
      for (unsigned long j = 0; j < strlen(double_deg); j++) {
        int num = 0;
        if (string_num[j] != '\0') num = string_num[j] - '0';
        num += double_deg[j] - '0' + mem;
        if (num > 9) {
          num -= 10;
          mem = 1;
        } else
          mem = 0;
        string_num[j] = num + '0';
      }
      if (mem != 0) string_num[strlen(string_num)] = mem + '0';
    }
    int mem = 0;
    char tmp[40] = {0};
    for (size_t j = 0; j < strlen(double_deg); j++) {
      int num = 0;
      if (double_deg[j] != '\0') num = double_deg[j] - '0';
      num = (double_deg[j] - '0') * 2 + mem;
      if (num > 9) {
        mem = 1;
        num -= 10;
      } else
        mem = 0;
      tmp[j] = num + '0';
    }
    if (mem != 0) tmp[strlen(tmp)] = mem + '0';
    strcpy(double_deg, tmp);
  }
  if (_G_S_((*value)) 1 > 0)
    printf("+");
  else
    printf("-");

  int deg = _G_D_((*value));
  if (deg >= (int)strlen(string_num)) {
    printf("0.");
    for (size_t i = 0; i < deg - strlen(string_num); i++) printf("0");
  }
  for (int i = (int)strlen(string_num) - 1; i >= 0; i--) {
    printf("%c", string_num[i]);
    if (deg == i && i != 0lu) printf(".");
  }
}

int s21_is_less_arithmetic_big(s21_big_decimal value_1,
                               s21_big_decimal value_2) {
  int deg1 = _G_D_(value_1), deg2 = _G_D_(value_2), len1 = s21_len_big(value_1),
      len2 = s21_len_big(value_2);
  if (len1 == len2) {
    if (deg1 < deg2)
      return TRUE;
    else
      return FALSE;
  }
  if (len1 != len2) {
  }
  for (int i = 224; i >= 0; i--) {
    if (_G_B_(value_1, i) != _G_B_(value_2, i)) {
      if (_G_B_(value_1, i) < _G_B_(value_2, i))
        return TRUE;
      else
        return FALSE;
    }
  }
  return FALSE;
}

int s21_is_less_or_equal_arithmetic(s21_big_decimal value_1,
                                    s21_big_decimal value_2) {
  for (int i = 224; i >= 0; i--) {
    if (_G_B_(value_1, i) != _G_B_(value_2, i)) {
      if (_G_B_(value_1, i) < _G_B_(value_2, i))
        return TRUE;
      else
        return FALSE;
    }
  }
  return TRUE;
}

int s21_is_zero_arithmetic(s21_big_decimal value) {
  for (int i = 224; i >= 0; i--) {
    if (_G_B_(value, i)) return FALSE;
  }
  return TRUE;
}
int s21_div_recursive(s21_decimal* value_1, s21_decimal* value_2,
                      s21_decimal* result, int calcFractPart) {
  s21_big_decimal value_1_b = {0}, value_2_b = {0}, result_b = {0};
  s21_to_big(*value_1, &value_1_b);
  s21_to_big(*value_2, &value_2_b);
  s21_to_big(*result, &result_b);
  s21_div_recursive_big(&value_1_b, &value_2_b, &result_b, calcFractPart);
  return s21_from_big(result_b, result);
}

int s21_div_recursive_big(s21_big_decimal* value_1, s21_big_decimal* value_2,
                          s21_big_decimal* result, int calcFractPart) {
  int res = 0;
  // char str1[100] = {0}, str2[100] = {0}, str3[100] = {0};
  // char *ptr1 = str1, *ptr2 = str2, *ptr3 = str3;
  int def_len1 = s21_len_big(*value_1), def_len2 = s21_len_big(*value_2);
  if (def_len1 > def_len2) _LS_B_((*value_2), def_len1 - def_len2);
  s21_big_decimal result_temp = {0};
  result_temp.bits[7] = value_1->bits[7];
  for (int i = 0; i <= def_len1 - def_len2 ||
                  s21_is_less_or_equal_arithmetic(*value_2, *value_1);
       i++) {
    _LS_B_(result_temp, 1);
    if (s21_is_less_or_equal_arithmetic(*value_2, *value_1)) {
      _S_B_(result_temp, 0, 1);
      s21_sub_bit(*value_1, *value_2, value_1);
    } else {
      _S_B_(result_temp, 0, 0);
    }
    if (s21_len_big(*value_2) > def_len2) _RS_B_((*value_2), 1)
  }
  int res_temp = 0;
  if (s21_is_zero_arithmetic(*result)) {
    for (int i = 0; i < 7; i++) result->bits[i] = result_temp.bits[i];
  } else
    s21_add_bit(*result, result_temp, result);
  if (!s21_is_zero_arithmetic(*value_1) && _G_D_((*result)) != 29 &&
      !res_temp && calcFractPart) {
    s21_left_shift_big(*value_1, 1, 1, value_1);
    s21_left_shift_big(*result, 1, 0, result);
    res = s21_div_recursive_big(value_1, value_2, result, calcFractPart);
  }
  return res;
}

void s21_print_decimal_BIT(s21_decimal* value, int space) {
  if (_G_S_((*value)) 1 > 0)
    printf("+");
  else
    printf("-");
  if (space == 0 || space < s21_len(*value)) space = s21_len(*value);
  for (; space >= 0; space--) printf("%d", _G_B_((*value), space));
  printf("x%d", _G_D_((*value)));
}

int s21_sum(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int res = 0;
  for (int i = 0; i < 4; i++) result->bits[i] = 0;
  s21_big_decimal value_1_big = {0}, value_2_big = {0}, result_big = {0};
  s21_to_big(value_1, &value_1_big);
  s21_to_big(value_2, &value_2_big);

  s21_optimize_big_decimal(&value_1_big);
  s21_optimize_big_decimal(&value_2_big);

  s21_align_big(&value_1_big, &value_2_big, &result_big);
  s21_get_max_big(&value_1_big, &value_2_big, &result_big);

  operation op = s21_get_operation(&value_1_big, &value_2_big);

  res = op(value_1_big, value_2_big, &result_big);
  if (!res) res = s21_from_big(result_big, result);
  return res;
}

void get_formatted_str_decimal(s21_decimal value, char* res) {
  char tmp[100] = {0};
  s21_get_string_decimal(value, tmp);
  int deg = _G_D_(value), dec_len = 0, i = 0;
  for (; tmp[dec_len] != '\000'; dec_len++)
    ;
  if (_IS_POS_(value))
    res[i++] = '+';
  else
    res[i++] = '-';
  if (dec_len != 0) {
    // int len = deg > dec_len ? deg : dec_len;
    int point = 0;
    if (deg >= dec_len) {
      res[i++] = '0';
      res[i++] = '.';
      point = 1;
    }
    while (deg > dec_len) {
      deg--;
      res[i++] = '0';
    }
    for (int j = dec_len - 1; j >= 0; j--) {
      if (j == deg - 1 && !point) res[i++] = '.';
      res[i++] = tmp[j];
    }
  } else {
    res[i++] = '0';
    res[i++] = '.';
    for (int t = 0; t < 28; t++) res[i + t] = '0';
  }
}

int s21_less_comparing(s21_decimal value_1, s21_decimal value_2) {
  int exit_code = FALSE;
  if ((_G_D_(value_1)) > (_G_D_(value_2))) {
    exit_code = TRUE;
  } else if ((_G_D_(value_1)) == (_G_D_(value_2))) {
    for (int i = 2; i > -1 && exit_code != 1; i--) {
      if (value_1.bits[i] < value_2.bits[i]) {
        exit_code = TRUE;
      }
    }
  }
  return exit_code;
}

int s21_is_zero(s21_decimal value_1) {
  int exit_code = FALSE;
  if (value_1.bits[0] == 0 && value_1.bits[1] == 0 && value_1.bits[2] == 0) {
    exit_code = TRUE;
  }
  return exit_code;
}

void s21_get_degree_diff_and_normalize(s21_decimal* value_1,
                                       s21_decimal* value_2) {
  int degree_diff = 0;
  degree_diff = _G_D_((*value_1)) - _G_D_((*value_2));

  if (degree_diff > 0) {
    s21_normalize_degree(value_2, degree_diff);
  } else {
    s21_normalize_degree(value_1, -degree_diff);
  }
}

void s21_normalize_degree(s21_decimal* value_1, int degree_diff) {
  s21_decimal degree_in_decimal = {0};
  s21_decimal result = {0};
  s21_from_float_to_decimal((pow(10, degree_diff)), &degree_in_decimal);
  s21_mul(*value_1, degree_in_decimal, &result);
  int new_degree = _G_D_(result) + degree_diff;
  _S_D_(result, new_degree);
  for (int i = 0; i < 4; i++) {
    value_1->bits[i] = result.bits[i];
  }
}

int s21_comparison_int_bits(s21_decimal value_1, s21_decimal value_2) {
  int bit_1 = 0;
  int bit_2 = 0;

  int exit_code = 0;

  for (int i = 95; i > -1 && exit_code == 0; i--) {
    bit_1 = _G_B_(value_1, i);
    bit_2 = _G_B_(value_2, i);
    if (bit_2 > bit_1) {
      exit_code = 1;
    }
  }
  return exit_code;
}

int s21_comparison_bits_int(s21_decimal value_1, s21_decimal value_2) {
  int exit_code = 0;
  for (int i = 0; i < 3 && (exit_code == 0); i++) {
    if ((value_2.bits[i] > value_1.bits[i])) {
      exit_code = 1;
    }
  }
  return exit_code;
}

int s21_exit_code_reverse_with_sign(int flag) {
  if (flag == 0) {
    flag = 1;
  } else if (flag == 1) {
    flag = 0;
  }
  return flag;
}

int s21_nan_chek(float src) {
  int result = 0;
  if (isnan(src * (-1)) || isinf(src * (-1)) || src == -FLT_MIN ||
      src == -FLT_MAX) {
    result = 1;
  }
  return result;
}

int s21_max_check(float src) {
  int result = OK;
  char max[] = _MAX_DECIMAL_STR_, str[100] = {0};
  sprintf(str, "%.0f", src);
  if (strlen(max) < strlen(str))
    result = ERROR;
  else if (strlen(max) == strlen(str)) {
    int flag = 0;
    for (size_t i = 0; i < strlen(max) && !flag; i++) {
      if (max[i] != str[i]) {
        if (max[i] < str[i]) result = ERROR;
        flag = 1;
      }
    }
  }
  return result;
}

int s21_num_len_str(char* str, int* fracPart) {
  str++;
  int num_len = 0, totalLen = 0, intPart = 0;
  for (size_t i = 0; i < strlen(str); i++) {
    if (str[i] != '.') totalLen++;
  }
  *fracPart = 0;
  for (size_t i = 0; str[i] != '.'; i++) {
    intPart++;
  }
  for (; str[totalLen] == '0'; totalLen--)
    ;
  *fracPart = totalLen - intPart;
  for (size_t i = 0; i < strlen(str); i++) {
    if (str[i] - '0' == 0) {
      num_len++;
    }
  }
  return num_len;
}

int s21_convert(float src, char* str, s21_decimal* dst) {
  sprintf(str, "%+.28f", src);
  size_t len = strlen(str), i;
  int deg = 0, step = 0, size_dec = 0;
  for (i = 1; step != 3 && i < len; i++) {
    deg += deg > 0 || str[i] == '.' ? 1 : 0;
    if (step == 0) {
      if (str[i] != '0' && str[i] != '.') {
        step++;
        size_dec++;
      }
    } else if (step == 1) {
      size_dec++;
      if (size_dec >= 7) step++;
    } else if (step == 2) {
      if (deg != 0) step++;
    }
  }
  i = i;
  step = 0;
  for (size_t j = 1; j < i; j++) {
    if (str[j] != '.') {
      s21_left_shift(*dst, 1, 1, dst);
      if (size_dec > 0) {
        s21_decimal tmp = {0};
        int num = str[j] - '0';
        if (num != 0) step++;
        s21_from_int_to_decimal(num, &tmp);
        s21_add(*dst, tmp, dst);
        if (step != 0) size_dec--;
      }
      if (size_dec == 0) {
        if (j + 1 < len && str[j + 1] == '.') j++;
        if (j + 1 < len && str[j + 1] - '0' >= 5) {
          s21_decimal tmp = {{1, 0, 0, 0}};
          s21_add(*dst, tmp, dst);
        }
        size_dec--;
      }
    }
  }
  return deg;
}
