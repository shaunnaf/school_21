#include "../s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *ptr1 = (const unsigned char *)str1;
  const unsigned char *ptr2 = (const unsigned char *)str2;
  int result = 0;
  for (s21_size_t i = 0; i < n && ptr1 && ptr2 && !result; i++) {
    if (ptr1[i] != ptr2[i]) result = ptr1[i] - ptr2[i];
  }
  return result;
}
