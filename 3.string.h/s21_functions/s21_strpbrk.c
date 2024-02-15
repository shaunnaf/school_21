#include "../s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = s21_NULL;

  while (*str1 != '\0') {
    const char *accept = str2;
    while (*accept != '\0') {
      if (*accept == *str1) {
        result = (char *)str1;
        break;
      }
      accept++;
    }
    if (result != s21_NULL) {
      break;
    }
    str1++;
  }

  return result;
}
