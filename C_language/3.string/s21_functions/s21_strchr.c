#include "../s21_string.h"
// Выполняет поиск первого вхождения символа c (беззнаковый тип)
// в строке, на которую указывает аргумент str
char *s21_strchr(const char *str, int c) {
  char *res = s21_NULL;
  s21_size_t len = s21_strlen(str);
  for (s21_size_t i = 0; i <= len; i++) {
    if (*str == (char)c) {
      res = (char *)str;
      break;
    }
    str++;
  }
  return res;
}
