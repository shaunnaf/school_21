#include "../s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  *str = '\0';
  reading_format(str, format, &args);
  va_end(args);
  return (int)s21_strlen(str);
}

void reading_format(char *str, const char *format, va_list *args) {
  s21_size_t i = 0;
  while (*format) {
    if (*format == '%') {
      Formats Parameters = {0};
      format++;
      if (is_flag(*format)) {
        while (is_flag(*format)) get_flag(&Parameters, format++);
      }
      if (is_digit(*format) || *format == '*')
        format = str_to_number(&Parameters.width, format++, args);
      if (*format == '.') {
        Parameters.point = 1;
        Parameters.precision = 0;
        format++;
        if (is_digit(*format) || *format == '*')
          format = str_to_number(&Parameters.precision, format++, args);
      }
      if (is_length(*format)) {
        while (is_length(*format)) Parameters.length = *(format++);
      }
      if (is_specifier(*format)) Parameters.specifier = *(format++);
      str = get_specifier(str, args, &Parameters, &i);
    } else {
      str[i++] = *(format++);
      str[i] = '\0';
    }
  }
}

void get_flag(Formats *Parameters, const char *format) {
  switch (*format) {
    case '-':
      Parameters->minus = 1;
      Parameters->zero = 0;
      break;
    case '+':
      Parameters->plus = 1;
      Parameters->space = 0;
      break;
    case ' ':
      Parameters->space = 1;
      break;
    case '#':
      Parameters->sharp = 1;
      break;
    case '0':
      Parameters->zero = 1;
      break;
  }
}

char *str_to_number(int *number, const char *format, va_list *args) {
  char buffer[BUFF_SIZE] = "";
  char *ptr = s21_NULL;
  int count = 0;
  while (is_digit(*format)) buffer[count++] = *(format++);
  ptr = buffer;
  while (count > 0) *number += (*(ptr++) - '0') * pow(10, --count);
  if (*format == '*') {
    *number = va_arg(*args, int);
    format++;
  }
  return (char *)format;
}

char *get_specifier(char *str, va_list *args, Formats *Parameters,
                    s21_size_t *length) {
  char *buffer = calloc(BUFF_SIZE, sizeof(char));
  switch (Parameters->specifier) {
    case 'c':
      specifier_c(buffer, args, Parameters);
      break;
    case 'd':
      specifier_d(buffer, args, Parameters);
      break;
    case 'f':
    case 'g':
    case 'G':
    case 'e':
    case 'E':
      if (!Parameters->point) Parameters->precision = 6;
      specifier_fgGeE(buffer, args, Parameters);
      break;
    case 's':
      specifier_s(buffer, args, Parameters);
      break;
    case 'u':
    case 'x':
    case 'X':
    case 'o':
      specifier_uxXo(buffer, args, Parameters);
      break;
    case 'p':
      specifier_p(buffer, args, Parameters);
      break;
    case '%':
      s21_strncat(str, "%", 1);
      break;
  }
  s21_strncat(str, buffer, s21_strlen(buffer));
  free(buffer);
  *length = s21_strlen(str);
  return str;
}

void specifier_c(char *str, va_list *args, Formats *Parameters) {
  if (Parameters->length == 'l') {
    wchar_t wchar = va_arg(*args, wchar_t);
    char buffer[BUFF_SIZE] = "";
    wcstombs(buffer, &wchar, BUFF_SIZE);
    s21_strncat(str, buffer, 1);
    str[1] = '\0';
  } else {
    str[0] = va_arg(*args, int);
    str[1] = '\0';
  }
  processing_flags(str, Parameters);
  processing_width(str, Parameters);
}

void specifier_d(char *str, va_list *args, Formats *Parameters) {
  short int short_number = 0;
  long int long_number = 0;
  long long int long_long_number = 0;
  int number = 0;
  if (Parameters->length == 'h') {
    short_number = (short)va_arg(*args, int);
    duxXo_to_str(str, Parameters, short_number, 10);
  } else if (Parameters->length == 'l') {
    long_number = va_arg(*args, long int);
    duxXo_to_str(str, Parameters, long_number, 10);
  } else if (Parameters->length == 'L') {
    long_long_number = va_arg(*args, long long int);
    duxXo_to_str(str, Parameters, long_long_number, 10);
  } else {
    number = va_arg(*args, int);
    duxXo_to_str(str, Parameters, number, 10);
  }
  processing_precision(str, Parameters);
  processing_flags(str, Parameters);
  processing_width(str, Parameters);
}

void specifier_fgGeE(char *str, va_list *args, Formats *Parameters) {
  long double long_number = 0;
  double number = 0;
  if (Parameters->length == 'L') {
    long_number = va_arg(*args, long double);
    if (Parameters->specifier == 'f') f_to_str(str, Parameters, long_number);
    if (Parameters->specifier == 'g' || Parameters->specifier == 'G')
      gG_to_str(str, Parameters, long_number);
    if (Parameters->specifier == 'e' || Parameters->specifier == 'E')
      eE_to_str(str, Parameters, long_number);
  } else {
    number = va_arg(*args, double);
    if (Parameters->specifier == 'f') f_to_str(str, Parameters, number);
    if (Parameters->specifier == 'g' || Parameters->specifier == 'G')
      gG_to_str(str, Parameters, number);
    if (Parameters->specifier == 'e' || Parameters->specifier == 'E')
      eE_to_str(str, Parameters, number);
  }
  processing_flags(str, Parameters);
  processing_width(str, Parameters);
}

void specifier_s(char *str, va_list *args, Formats *Parameters) {
  char *string = s21_NULL;
  string = va_arg(*args, char *);
  s21_size_t length = s21_strlen(string);
  if (Parameters->precision > 0) {
    s21_strncat(str, string, Parameters->precision);
    str[Parameters->precision + 1] = '\0';
  } else {
    s21_strncat(str, string, length);
    str[length + 1] = '\0';
  }
  processing_flags(str, Parameters);
  processing_width(str, Parameters);
}

void specifier_uxXo(char *str, va_list *args, Formats *Parameters) {
  unsigned short short_number = 0;
  unsigned long long_number = 0;
  unsigned long long long_long_number = 0;
  unsigned int number = 0;
  if (Parameters->length == 'h') {
    short_number = (short)va_arg(*args, unsigned int);
    if (Parameters->specifier == 'u')
      duxXo_to_str(str, Parameters, short_number, 10);
    if (Parameters->specifier == 'x' || Parameters->specifier == 'X')
      duxXo_to_str(str, Parameters, short_number, 16);
    if (Parameters->specifier == 'o')
      duxXo_to_str(str, Parameters, short_number, 8);
  } else if (Parameters->length == 'l') {
    long_number = va_arg(*args, unsigned long);
    if (Parameters->specifier == 'u')
      duxXo_to_str(str, Parameters, long_number, 10);
    if (Parameters->specifier == 'x' || Parameters->specifier == 'X')
      duxXo_to_str(str, Parameters, long_number, 16);
    if (Parameters->specifier == 'o')
      duxXo_to_str(str, Parameters, long_number, 8);
  } else if (Parameters->length == 'L') {
    long_long_number = va_arg(*args, unsigned long long);
    if (Parameters->specifier == 'u')
      duxXo_to_str(str, Parameters, long_long_number, 10);
    if (Parameters->specifier == 'x' || Parameters->specifier == 'X')
      duxXo_to_str(str, Parameters, long_long_number, 16);
    if (Parameters->specifier == 'o')
      duxXo_to_str(str, Parameters, long_long_number, 8);
  } else {
    number = va_arg(*args, unsigned int);
    if (Parameters->specifier == 'u') duxXo_to_str(str, Parameters, number, 10);
    if (Parameters->specifier == 'x' || Parameters->specifier == 'X')
      duxXo_to_str(str, Parameters, number, 16);
    if (Parameters->specifier == 'o') duxXo_to_str(str, Parameters, number, 8);
  }
  processing_precision(str, Parameters);
  processing_flags(str, Parameters);
  processing_width(str, Parameters);
}

void specifier_p(char *str, va_list *args, Formats *Parameters) {
  int width = Parameters->width < 15 ? 15 : Parameters->width;
  char *ptr = s21_NULL;
  ptr = str;
  int *p = va_arg(*args, int *);
  char buffer[BUFF_SIZE] = "x0";
  if (p == s21_NULL) s21_memcpy(buffer, "0x0", 3);
  for (int *j = p, k = 0; j && k < width;
       j = (void *)(((s21_size_t)j) >> 4), k++) {
    unsigned int digit = (s21_size_t)j % 16;
    *(ptr++) = (char)((digit < 10) ? ('0' + digit) : ('a' + (digit - 10)));
  }
  *ptr = '\0';
  s21_strncat(str, buffer, (int)s21_strlen(buffer));
  reverse(str);
  processing_flags(str, Parameters);
  processing_width(str, Parameters);
}

void processing_precision(char *str, Formats *Parameters) {
  char buffer[BUFF_SIZE] = "";
  int length = 0;
  if (s21_strchr("duxXo", Parameters->specifier)) {
    while (length < Parameters->precision - (int)s21_strlen(str))
      buffer[length++] = '0';
    for (int i = 0; str[i] != '\0'; i++) buffer[length++] = str[i];
    s21_memcpy(str, buffer, length);
  }
}

void processing_flags(char *str, Formats *Parameters) {
  int length = 0;
  if (s21_strchr("dfgGeE", Parameters->specifier)) {
    if (Parameters->sign < 0) {
      move_string(str);
      str[length] = '-';
      Parameters->sign = 0;
    }
    if (Parameters->plus && Parameters->sign != 0) {
      move_string(str);
      str[length] = (Parameters->sign > 0) ? '+' : '-';
      Parameters->sign = 0;
    }
    if (Parameters->space && Parameters->sign != 0) {
      move_string(str);
      str[length] = (Parameters->sign > 0) ? ' ' : '-';
      Parameters->sign = 0;
    }
  }
  if (Parameters->minus) {
    length = (int)s21_strlen(str);
    while (length < Parameters->width) str[length++] = ' ';
  }
}

void processing_width(char *str, Formats *Parameters) {
  int length = (int)s21_strlen(str);
  if (Parameters->width > length) {
    str[Parameters->width + 1] = '\0';
    while (length >= 0) str[Parameters->width--] = str[length--];
    for (length = 0; length <= Parameters->width; length++) {
      if (s21_strchr("cduxXo", Parameters->specifier)) {
        if (Parameters->zero && !Parameters->point)
          str[s21_strchr(str, '-') ? length + 1 : length] = '0';
        else
          str[length] = ' ';
      }
      if (s21_strchr("fgGeEp", Parameters->specifier)) {
        if (Parameters->zero)
          str[s21_strchr(str, '-') ? length + 1 : length] = '0';
        else
          str[length] = ' ';
      }
    }
  }
}

void move_string(char *str) {
  int length = (int)s21_strlen(str);
  str[length + 1] = '\0';
  for (; length > 0; length--) str[length] = str[length - 1];
}

void duxXo_to_str(char *str, Formats *Parameters, long long number, int base) {
  Parameters->sign = number < 0 ? -1 : 1;
  number *= Parameters->sign;
  char *ptr = s21_NULL;
  int flag = 1;
  ptr = str;
  while (flag) {
    int digit = 0;
    if (Parameters->specifier == 'u' || Parameters->specifier == 'x' ||
        Parameters->specifier == 'X' || Parameters->specifier == 'o')
      digit = (unsigned)digit;
    if (number >= base) {
      digit = number % base;
      number = (number - digit) / base;
    } else {
      digit = number;
      flag = 0;
    }
    if (s21_strchr("dfugGeEo", Parameters->specifier))
      *(ptr++) = (char)(digit + '0');
    if (s21_strchr("xX", Parameters->specifier))
      *(ptr++) =
          (char)((digit < 10) ? (digit + '0')
                              : (digit + 'A' +
                                 (Parameters->specifier == 'x' ? 32 : 0) - 10));
  }
  if (Parameters->sharp && Parameters->specifier == 'o') *(ptr++) = '0';
  *ptr = '\0';
  if (Parameters->sharp && s21_strchr("xX", Parameters->specifier))
    s21_strncat(ptr, (Parameters->specifier == 'x') ? "x0" : "X0", 3);
  reverse(str);
}

void reverse(char *str) {
  char *start = str;
  char *end = str + (int)s21_strlen(str) - 1;
  for (; start < end; start++, end--) {
    char temp = *start;
    *start = *end;
    *end = temp;
  }
}

void f_to_str(char *str, Formats *Parameters, long double number) {
  Parameters->sign = number < 0 ? -1 : 1;
  number *= Parameters->sign;
  int sign = Parameters->sign;
  if (Parameters->precision == 0)
    duxXo_to_str(str, Parameters, roundl(number), 10);
  else {
    long double integer = 0;
    long double fractional = 0;
    int length = 0;
    char buffer[BUFF_SIZE] = "";
    fractional = modfl(number, &integer);
    if (s21_strchr("gG", Parameters->specifier) && Parameters->precision == 1 &&
        fractional >= 0.5)
      integer++;
    duxXo_to_str(str, Parameters, roundl(integer), 10);
    s21_strncat(str, ".", 1);
    int local_precision = Parameters->precision;
    if (s21_strchr("gG", Parameters->specifier)) {
      if (integer >= 1)
        local_precision = Parameters->precision - (int)s21_strlen(str) + 1;
      else if (fractional * pow(10, local_precision) < 1)
        local_precision = 4;
    }
    for (int i = 0; i < local_precision; i++) fractional *= 10;
    duxXo_to_str(buffer, Parameters, roundl(fractional), 10);
    length = (int)s21_strlen(buffer);
    if (s21_strchr("gG", Parameters->specifier) && (int)roundl(number) != 0)
      buffer[Parameters->precision + (int)s21_strlen(str) + 1] = '\0';
    s21_strncat(str, buffer, length);
  }
  Parameters->sign = sign;
}

void gG_to_str(char *str, Formats *Parameters, long double number) {
  Parameters->sign = number < 0 ? -1 : 1;
  number *= Parameters->sign;
  int sign = Parameters->sign;
  if ((number / pow(10, Parameters->precision)) > 1 ||
      ((number * (pow(10, 4))) < 1 && (number * (pow(10, 21))) >= 1)) {
    if (number < 1 && Parameters->precision == 0)
      Parameters->precision = 4;
    else
      --Parameters->precision;
    eE_to_str(str, Parameters, number);
  } else {
    f_to_str(str, Parameters, number);
    delete_zero(str, Parameters);
  }
  Parameters->sign = sign;
}

void delete_zero(char *str, Formats *Parameters) {
  int length = (int)s21_strlen(str) - 1;
  for (; str[length] == '0'; length--) {
    if (!Parameters->sharp ||
        (Parameters->sharp && length > Parameters->precision))
      str[length] = '\0';
  }
}

void eE_to_str(char *str, Formats *Parameters, long double number) {
  Parameters->sign = number < 0 ? -1 : 1;
  number *= Parameters->sign;
  int sign = Parameters->sign;
  int exponent = 0;
  if (number < 1) {
    for (; number < 1; exponent--) number *= 10;
    while (check_rounding(Parameters, number) && Parameters->precision >= 0) {
      exponent++;
      Parameters->precision--;
    }
  } else {
    for (; number >= 10; exponent++) number /= 10;
    while (check_rounding(Parameters, number) && Parameters->precision >= 0) {
      exponent++;
      Parameters->precision--;
    }
  }
  number = roundl(number * pow(10, Parameters->precision));
  duxXo_to_str(str, Parameters, number, 10);
  if (Parameters->precision > 0) {
    move_string(&str[1]);
    str[1] = '.';
  }
  converting_mantis(Parameters, &str[(int)s21_strlen(str)], exponent);
  Parameters->sign = sign;
}

int check_rounding(Formats *Parameters, long double number) {
  char buffer[BUFF_SIZE] = "";
  int length = 0;
  int length_round = 0;
  number *= pow(10, Parameters->precision);
  duxXo_to_str(buffer, Parameters, number, 10);
  length = (int)s21_strlen(buffer);
  number = roundl(number);
  duxXo_to_str(buffer, Parameters, number, 10);
  length_round = (int)s21_strlen(buffer);
  return length < length_round ? 1 : 0;
}

void converting_mantis(Formats *Parameters, char *mantis, int exponent) {
  int length = 0;
  if (Parameters->sharp && !Parameters->precision) mantis[length++] = '.';
  mantis[length++] = s21_strchr("ge", Parameters->specifier) ? 'e' : 'E';
  mantis[length++] = (exponent >= 0) ? '+' : '-';
  if (abs(exponent) < 10) {
    mantis[length++] = '0';
    duxXo_to_str(&mantis[length], Parameters, abs(exponent), 10);
  } else
    duxXo_to_str(&mantis[length], Parameters, abs(exponent), 10);
}
