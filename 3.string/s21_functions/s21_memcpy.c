#include "../s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *destination = (unsigned char *)dest;
  const unsigned char *source = (const unsigned char *)src;
  for (s21_size_t i = 0; i < n && source && destination; i++)
    destination[i] = source[i];
  return (void *)destination;
}