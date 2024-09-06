#include "../s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *ptr = (const unsigned char *)str;
  void *result = s21_NULL;
  for (s21_size_t i = 0; i < n && ptr && !result; i++)
    if (ptr[i] == c) result = (void *)&ptr[i];
  return result;
}