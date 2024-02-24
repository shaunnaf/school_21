#include "../s21_string.h"
// Копирует до n символов из строки, на которую указывает src, в dest
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i = 0;
  char *ptr = dest;
  for (i = 0; i < n && *src != 0; i++) {
    *dest = *src;
    src++;
    dest++;
  }
  while (i < n) {
    *dest = '\0';
    i++;
    dest++;
  }
  return ptr;
}
