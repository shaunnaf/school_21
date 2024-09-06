#include "../s21_string.h"
// Копирует до n символов из строки, на которую указывает src, в dest
char *s21_strcpy(char *dest, const char *src) {
  for (int i = 0; src[i]; i++) {
    dest[i] = src[i];
  }
  dest[s21_strlen(src)] = '\0';
  return dest;
}