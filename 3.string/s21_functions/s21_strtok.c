#include "../s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *token = s21_NULL;
  char *ret = s21_NULL;
  if (str != s21_NULL) {
    token = str;
  }
  s21_size_t del_length = s21_strlen(delim);
  if (token != s21_NULL) {
    while (s21_memchr(delim, *token, del_length) != s21_NULL) {
      token++;
    }
    if (*token != '\0') {
      ret = token;
      while (*token) {
        if (s21_memchr(delim, *token, del_length) != s21_NULL) {
          break;
        } else {
          token++;
        }
      }
      if (*token) {
        token[0] = '\0';
        token++;
      }
    }
  }
  return ret;
}