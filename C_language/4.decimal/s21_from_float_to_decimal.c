#include "s21_decimal.h"
int s21_from_float_to_decimal(float src, s21_decimal* dst) {
  int result = 0;
  if (src < 0) {
    result = s21_nan_chek(src);
  } else if (isnan(src) || isinf(src) || src == FLT_MIN || src == FLT_MAX) {
    result = 1;
  }
  if (result == 0) {
    char str[100] = {0};
    int fracPart = 0;
    sprintf(str, "%+.28f", src);
    s21_num_len_str(str, &fracPart);
    if (s21_max_check(src) ||
        (fracPart == 0 && src != 0 && (src < 0 ? src > -1 : src < 1)))
      result = 1;
    else {
      for (int i = 0; i < 4; i++) dst->bits[i] = 0;
      if (str[0] == '+') {
        _S_S_((*dst), +);
      } else {
        _S_S_((*dst), -);
      }
      if (src != 0.f) {
        int deg = s21_convert(src, str, dst);
        if (!s21_is_zero(*dst)) {
          while (deg > 1 && dst->bits[0] % 10 == 0) {
            s21_right_shift(*dst, 1, 1, dst);
            deg--;
          }
          _S_D_((*dst), deg - 1);
        }

        if (str[0] == '-') {
          _S_S_((*dst), -);

        } else {
          _S_S_((*dst), +);
        }
      }
    }
  }
  return result;
}