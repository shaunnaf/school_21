#include "../s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  s21_size_t len_src = s21_strlen(src), len_str = s21_strlen(str);
  char *final_string = s21_NULL;

  if ((len_str != 0 || len_src != 0) && start_index <= len_src) {
    s21_size_t i = 0;
    final_string = calloc(len_src + len_str + 2, 1);
    if (final_string != s21_NULL) {
      for (; i < start_index; i++) {
        final_string[i] = src[i];
      }
      int j = 0;
      for (; i < start_index + len_str; i++, j++) {
        final_string[i] = str[0 + j];
      }
      for (; i < len_src + len_str; i++) {
        final_string[i] = src[i - len_str];
      }
    }
  }
  return final_string;
}