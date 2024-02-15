#include "../s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *last_char = s21_NULL;

  while (*str != '\0') {
    if (*str == (char)c) {
      last_char = (char *)str;
    }
    str++;
  }

  if (*str == (char)c) {
    last_char = (char *)str;
  }
  return last_char == s21_NULL ? s21_NULL : (char *)last_char;
}
