#ifndef S21_STRING_H
#define S21_STRING_H

#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define s21_size_t unsigned long long
#define s21_NULL (void *)0

void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
char *s21_strcpy(char *dest, const char *src);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);

//////////////////////////////SPRINTF//////////////////////////////
///////////////////////////////////////////////////////////////////

#define is_flag(c) \
  ((c) == '-') || ((c) == '+') || ((c) == ' ') || ((c) == '#') || ((c) == '0')

#define is_digit(c) ((c) >= '0' && (c) <= '9')

#define is_length(c) ((c) == 'h' || (c) == 'l' || (c) == 'L')

#define is_specifier(c)                                                  \
  ((c) == 'c' || (c) == 'd' || (c) == 'f' || (c) == 's' || (c) == 'u' || \
   (c) == 'g' || (c) == 'G' || (c) == 'e' || (c) == 'E' || (c) == 'G' || \
   (c) == 'x' || (c) == 'X' || (c) == 'o' || (c) == 'p' || (c) == '%')

#define BUFF_SIZE 1024

typedef struct {
  int minus;
  int plus;
  int space;
  int sharp;
  int zero;
  int width;
  int precision;
  char length;
  char specifier;
  int sign;
  int point;
} Formats;
// %[flag][width][.point][length][specifier]

int s21_sprintf(char *str, const char *format, ...);
void reading_format(char *str, const char *format, va_list *args);
void get_flag(Formats *Parameters, const char *format);
char *str_to_number(int *number, const char *format, va_list *args);
char *get_specifier(char *str, va_list *args, Formats *Parameters,
                    s21_size_t *length);
void specifier_c(char *str, va_list *args, Formats *Parameters);
void specifier_d(char *str, va_list *args, Formats *Parameters);
void specifier_fgGeE(char *str, va_list *args, Formats *Parameters);
void specifier_s(char *str, va_list *args, Formats *Parameters);
void specifier_uxXo(char *str, va_list *args, Formats *Parameters);
void specifier_p(char *str, va_list *args, Formats *Parameters);
void processing_flags(char *str, Formats *Parameters);
void processing_width(char *str, Formats *Parameters);
void processing_precision(char *str, Formats *Parameters);
void move_string(char *str);
void reverse(char *str);
void duxXo_to_str(char *str, Formats *Parameters, long long number, int base);
void f_to_str(char *str, Formats *Parameters, long double number);
void gG_to_str(char *str, Formats *Parameters, long double number);
void delete_zero(char *str, Formats *Parameters);
void eE_to_str(char *str, Formats *Parameters, long double number);
int check_rounding(Formats *Parameters, long double number);
void converting_mantis(Formats *Parameters, char *mantis, int exponent);

//////////////////////////////SSCANF//////////////////////////////
//////////////////////////////////////////////////////////////////

enum Condition { NO_CONDITION, IN_FORMAT, IN_WIDTH };

enum LenghtModifier { NONE, SHORT, LONG, LONG_DOUBLE };

int process_specifier(const char *format, const char *buf, va_list *args,
                      int *count_arg);
void in_width(const char *format, int *miss_input, s21_size_t *i,
              int *number_width, enum Condition *condition);
int no_condition(const char *format, const char *buf, s21_size_t *i,
                 int *curr_char_in_buf, enum Condition *condition);
void type_data(const char *format, s21_size_t *i, int *lenght_modifier);
void processing_char(const char *buf, int miss_input, va_list *args,
                     int *curr_char_in_buf, enum Condition *condition);
void processing_decimal(const char *buf, char spec, int miss_input,
                        va_list *args, int *curr_char_in_buf, int number_width,
                        int lenght_modifier, enum Condition *condition);
void processing_oct(const char *buf, int miss_input, va_list *args,
                    int *curr_char_in_buf, int number_width,
                    int lenght_modifier, enum Condition *condition);
void oct_to_number(const char *buf, int *curr_char_in_buf, int number_width,
                   long long int *number);
void hex_to_number(const char *buf, int *curr_char_in_buf, int number_width,
                   long long int *number);
void neg_miss_input_decimal(va_list *args, int lenght_modifier,
                            long long int number);
void processing_hex(const char *buf, int miss_input, va_list *args,
                    int *curr_char_in_buf, int number_width,
                    int lenght_modifier, enum Condition *condition);
void processing_string(const char *format, const char *buf,
                       s21_size_t *curr_char_in_format, int miss_input,
                       va_list *args, int *curr_char_in_buf,
                       enum Condition *condition);
void neg_miss_input_float(va_list *args, long double number);
void processing_float(const char *buf, int miss_input, va_list *args,
                      int *curr_char_in_buf, int number_width,
                      int lenght_modifier, enum Condition *condition);
void neg_miss_input_unsigned(va_list *args, int lenght_modifier,
                             long long int number);
void processing_n(int miss_input, va_list *args, int *curr_char_in_buf,
                  enum Condition *condition);
void neg_miss_input_long_double(va_list *args, long double number);
void neg_miss_input_double(va_list *args, long double number);
void processing_p(const char *buf, int miss_input, va_list *args,
                  int *curr_char_in_buf, enum Condition *condition);

int s21_sscanf(const char *buf, const char *format, ...);

#endif