#include <string.h>

#include "../s21_string.h"
// Сравнивает не более первых n байтов str1 и str2
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int res = 0;
  s21_size_t i = 0;
  while (i < n) {
    if (*str2 != *str1 || !*str1) {
      res = *str1 - *str2;
      break;
    }
    str1++;
    str2++;
    i++;
  }
  return res;
}