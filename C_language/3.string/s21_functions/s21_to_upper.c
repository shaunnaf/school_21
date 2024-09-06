#include "../s21_string.h"

void *s21_to_upper(const char *str) {
  char *result = s21_NULL;
  if (str != s21_NULL) {
    result = calloc(s21_strlen(str) + sizeof(int), sizeof(char));
    if (result != s21_NULL) {
      for (int i = 0; str[i]; i++) {
        if ('a' <= str[i] && str[i] <= 122)
          result[i] = str[i] - 32;
        else
          result[i] = str[i];
      }
    }
  }
  return result;
}
