#include "../s21_string.h"
/*
Manual
Возвращает подстроку строки haystack,
начиная с первого вхождения needle (и включая его) и до конца строки haystack
*/

char *s21_strstr(const char *haystack, const char *needle) {
  char *position = s21_NULL;
  int flag = 0;

  if (*needle == '\0') {  // Если подстрока пустая, возвращаем строку целиком
    position = (char *)haystack;
  } else if (*haystack == '\0') {  // Если строка пустая, возвращаем NULL
    flag = 1;
  } else {
    while (*haystack != '\0') {
      const char *h = haystack;
      const char *n = needle;

      while (*n != '\0' && *h == *n) {
        h++;
        n++;
      }

      if (*n == '\0') {
        position = (char *)haystack;
        break;
      }

      haystack++;
    }
  }

  return flag == 0 ? position : s21_NULL;
}