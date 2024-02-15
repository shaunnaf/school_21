#include "../s21_string.h"

int s21_sscanf(const char *buf, const char *format, ...) {
  int count_arg = 0;
  va_list args;
  va_start(args, format);

  if (process_specifier(format, buf, &args, &count_arg)) {
    fprintf(stderr, "bad input");
  }
  va_end(args);

  return count_arg;
}

int process_specifier(const char *format, const char *buf, va_list *args,
                      int *count_arg) {
  enum Condition condition = NO_CONDITION;
  int error = 0;
  int number_width = -1;
  int miss_input = 0;
  s21_size_t curr_char_in_format = 0;
  int curr_char_in_buf = 0;
  int lenght_modifier = NONE;

  while (format[curr_char_in_format] != '\0' && error != 1) {
    switch (condition) {
      case NO_CONDITION:
        if (no_condition(format, buf, &curr_char_in_format, &curr_char_in_buf,
                         &condition) == 1) {
          error = 1;
        }
        break;
      case IN_WIDTH:
        miss_input = 0;
        number_width = -1;
        in_width(format, &miss_input, &curr_char_in_format, &number_width,
                 &condition);
        break;
      case IN_FORMAT:
        lenght_modifier = 0;
        type_data(format, &curr_char_in_format, &lenght_modifier);
        switch (format[curr_char_in_format]) {
          case 'c':
            processing_char(buf, miss_input, args, &curr_char_in_buf,
                            &condition);
            if (!miss_input) *count_arg += 1;
            curr_char_in_format += 1;
            break;
          case 'd':
          case 'u':
          case 'i':
            processing_decimal(buf, format[curr_char_in_format], miss_input,
                               args, &curr_char_in_buf, number_width,
                               lenght_modifier, &condition);
            if (!miss_input) *count_arg += 1;
            curr_char_in_format += 1;
            break;
          case 'f':
          case 'g':
          case 'G':
          case 'e':
          case 'E':
            processing_float(buf, miss_input, args, &curr_char_in_buf,
                             number_width, lenght_modifier, &condition);
            if (!miss_input) *count_arg += 1;
            curr_char_in_format += 1;
            break;
          case 'o':
            processing_oct(buf, miss_input, args, &curr_char_in_buf,
                           number_width, lenght_modifier, &condition);
            if (!miss_input) *count_arg += 1;
            curr_char_in_format += 1;
            break;
          case 'x':
          case 'X':
            processing_hex(buf, miss_input, args, &curr_char_in_buf,
                           number_width, lenght_modifier, &condition);
            if (!miss_input) *count_arg += 1;
            curr_char_in_format += 1;
            break;
          case 'p':
            processing_p(buf, miss_input, args, &curr_char_in_buf, &condition);
            if (!miss_input) *count_arg += 1;
            curr_char_in_format += 1;
            break;
          case 'n':
            processing_n(miss_input, args, &curr_char_in_buf, &condition);
            curr_char_in_format += 1;
            break;
          case 's':
            processing_string(format, buf, &curr_char_in_format, miss_input,
                              args, &curr_char_in_buf, &condition);
            if (!miss_input) *count_arg += 1;
            curr_char_in_format += 1;
            break;
        }
    }
  }
  return error;
}

void processing_n(int miss_input, va_list *args, int *curr_char_in_buf,
                  enum Condition *condition) {
  if (!miss_input) {
    int *arg = va_arg(*args, int *);
    *arg = *curr_char_in_buf;
  }
  *condition = NO_CONDITION;
}

void processing_string(const char *format, const char *buf,
                       s21_size_t *curr_char_in_format, int miss_input,
                       va_list *args, int *curr_char_in_buf,
                       enum Condition *condition) {
  int lenght_string = s21_strlen(buf) - *curr_char_in_buf;
  if (!miss_input) {
    char *arg = va_arg(*args, char *);
    for (int i = 0; i < lenght_string; i++) {
      if (buf[*curr_char_in_buf] == format[*(curr_char_in_format) + 1]) {
        *curr_char_in_format += 1;
        break;
      }
      arg[i] = buf[*curr_char_in_buf];
      *curr_char_in_buf += 1;
    }
  }
  *condition = NO_CONDITION;
  *curr_char_in_buf += 1;
}

void processing_float(const char *buf, int miss_input, va_list *args,
                      int *curr_char_in_buf, int number_width,
                      int lenght_modifier, enum Condition *condition) {
  long double number = 0;
  int negativ = 0;
  if (buf[*curr_char_in_buf] == '-' || buf[*curr_char_in_buf] == '+') {
    if (buf[*curr_char_in_buf] == '-') negativ = 1;
    *curr_char_in_buf += 1;
    number_width -= 1;
  }
  while (isdigit(buf[*curr_char_in_buf]) && number_width != 0) {
    number = 10 * (number) + buf[*curr_char_in_buf] - '0';
    *curr_char_in_buf += 1;
    number_width -= 1;
  }
  if (buf[*curr_char_in_buf] == '.' && number_width != 0) {
    *curr_char_in_buf += 1;
    number_width -= 1;
    int counter = 0;
    while (isdigit(buf[*curr_char_in_buf]) && number_width != 0) {
      counter += 1;
      long double temp_number = buf[*curr_char_in_buf] - '0';
      int temp_counter = counter;
      while (temp_counter != 0) {
        temp_number = temp_number / 10;
        temp_counter -= 1;
      }
      number += temp_number;
      *curr_char_in_buf += 1;
    }
  }
  if (!miss_input) {
    if (negativ) {
      number = number - number - number;
    }
    if (lenght_modifier == 0)
      neg_miss_input_float(args, number);
    else if (lenght_modifier == 2)
      neg_miss_input_double(args, number);
    else
      neg_miss_input_long_double(args, number);
  }
  *condition = NO_CONDITION;
}

void processing_oct(const char *buf, int miss_input, va_list *args,
                    int *curr_char_in_buf, int number_width,
                    int lenght_modifier, enum Condition *condition) {
  long long number = 0;
  int negativ = 0;
  if (buf[*curr_char_in_buf] == '-' || buf[*curr_char_in_buf] == '+') {
    if (buf[*curr_char_in_buf] == '-') negativ = 1;
    *curr_char_in_buf += 1;
    number_width -= 1;
  }
  oct_to_number(buf, curr_char_in_buf, number_width, &number);
  if (!miss_input) {
    if (negativ) {
      number = number - number - number;
    }
    neg_miss_input_decimal(args, lenght_modifier, number);
  }
  *condition = NO_CONDITION;
}

void processing_hex(const char *buf, int miss_input, va_list *args,
                    int *curr_char_in_buf, int number_width,
                    int lenght_modifier, enum Condition *condition) {
  long long number = 0;
  int negativ = 0;
  if (buf[*curr_char_in_buf] == '-' || buf[*curr_char_in_buf] == '+') {
    if (buf[*curr_char_in_buf] == '-') negativ = 1;
    *curr_char_in_buf += 1;
    number_width -= 1;
  }
  hex_to_number(buf, curr_char_in_buf, number_width, &number);
  if (!miss_input) {
    if (negativ) {
      number = number - number - number;
    }
    neg_miss_input_decimal(args, lenght_modifier, number);
  }
  *condition = NO_CONDITION;
}

void oct_to_number(const char *buf, int *curr_char_in_buf, int number_width,
                   long long int *number) {
  while (isdigit(buf[*curr_char_in_buf]) && number_width != 0 &&
         buf[*curr_char_in_buf] - '0' < 8) {
    *number = 8 * (*number) + buf[*curr_char_in_buf] - '0';
    *curr_char_in_buf += 1;
    number_width -= 1;
  }
}

void hex_to_number(const char *buf, int *curr_char_in_buf, int number_width,
                   long long int *number) {
  while (number_width != 0 && (isdigit(buf[*curr_char_in_buf]) ||
                               (tolower(buf[*curr_char_in_buf]) >= 'a' &&
                                tolower(buf[*curr_char_in_buf]) <= 'f'))) {
    *number =
        16 * (*number) + (isdigit(buf[*curr_char_in_buf])
                              ? (buf[*curr_char_in_buf] - '0')
                              : (tolower(buf[*curr_char_in_buf]) - 'a' + 10));
    number_width -= 1;
    *curr_char_in_buf += 1;
  }
}

void processing_decimal(const char *buf, char spec, int miss_input,
                        va_list *args, int *curr_char_in_buf, int number_width,
                        int lenght_modifier, enum Condition *condition) {
  long long int number = 0;
  int negativ = 0;
  if (buf[*curr_char_in_buf] == '-' || buf[*curr_char_in_buf] == '+') {
    if (buf[*curr_char_in_buf] == '-') negativ = 1;
    *curr_char_in_buf += 1;
    number_width -= 1;
  }
  if (buf[*curr_char_in_buf] == '0' && number_width != 0 && spec == 'i') {
    *curr_char_in_buf += 1;
    number_width -= 1;
    if (buf[*curr_char_in_buf] == 'x' || buf[*curr_char_in_buf] == 'X') {
      number_width -= 1;
      if (number_width != 0) {
        *curr_char_in_buf += 1;
        hex_to_number(buf, curr_char_in_buf, number_width, &number);
      }
    } else {
      oct_to_number(buf, curr_char_in_buf, number_width, &number);
    }
  } else {
    while (isdigit(buf[*curr_char_in_buf]) && number_width != 0) {
      number = 10 * (number) + buf[*curr_char_in_buf] - '0';
      *curr_char_in_buf += 1;
      number_width -= 1;
    }
  }
  if (!miss_input) {
    if (negativ) {
      number = number - number - number;
    }
    if (spec != 'u')
      neg_miss_input_decimal(args, lenght_modifier, number);
    else
      neg_miss_input_unsigned(args, lenght_modifier, number);
  }
  *condition = NO_CONDITION;
}

void neg_miss_input_unsigned(va_list *args, int lenght_modifier,
                             long long int number) {
  long long int *arg = va_arg(*args, long long int *);
  switch (lenght_modifier) {
    case 1:
      *arg = (unsigned short)number;
      break;
    case 2:
      *arg = (unsigned long)number;
      break;
    case 3:
      *arg = (unsigned long long)number;
      break;
    default:
      *arg = (unsigned int)number;
      break;
  }
}

void neg_miss_input_decimal(va_list *args, int lenght_modifier,
                            long long int number) {
  long long int *arg = va_arg(*args, long long int *);
  switch (lenght_modifier) {
    case 1:
      *arg = (short)number;
      break;
    case 2:
      *arg = (long)number;
      break;
    case 3:
      *arg = (long long)number;
      break;
    default:
      *arg = (int)number;
      break;
  }
}

void neg_miss_input_float(va_list *args, long double number) {
  float *arg = va_arg(*args, float *);
  *arg = (float)number;
}

void neg_miss_input_double(va_list *args, long double number) {
  double *arg = va_arg(*args, double *);
  *arg = (double)number;
}
void neg_miss_input_long_double(va_list *args, long double number) {
  long double *arg = va_arg(*args, long double *);
  *arg = (long double)number;
}

void processing_char(const char *buf, int miss_input, va_list *args,
                     int *curr_char_in_buf, enum Condition *condition) {
  if (!miss_input) {
    char *arg = va_arg(*args, char *);
    *arg = buf[*curr_char_in_buf];
  }
  *condition = NO_CONDITION;
  *curr_char_in_buf += 1;
}

void processing_p(const char *buf, int miss_input, va_list *args,
                  int *curr_char_in_buf, enum Condition *condition) {
  uintptr_t address = 0;
  if (buf[*curr_char_in_buf] == '0') *curr_char_in_buf += 1;

  if (buf[*(curr_char_in_buf)] == 'x' || buf[*(curr_char_in_buf)] == 'X')
    *curr_char_in_buf += 1;

  if (!miss_input) {
    void **arg = va_arg(*args, void **);

    while (*buf) {
      char digit = buf[*curr_char_in_buf];
      if (digit >= '0' && digit <= '9')
        address = (address << 4) | (digit - '0');
      else if (digit >= 'a' && digit <= 'f')
        address = (address << 4) | (digit - 'a' + 10);
      else if (digit >= 'A' && digit <= 'F')
        address = (address << 4) | (digit - 'A' + 10);
      else
        break;
      *curr_char_in_buf += 1;
    }
    *arg = (void *)address;
  }
  *condition = NO_CONDITION;
  *curr_char_in_buf += 1;
}

void type_data(const char *format, s21_size_t *curr_char_in_format,
               int *lenght_modifier) {
  switch (format[*curr_char_in_format]) {
    case 'h':
      *lenght_modifier = SHORT;
      *curr_char_in_format += 1;
      break;
    case 'l':
      if (format[*(curr_char_in_format) + 1] == 'l') {
        *lenght_modifier = LONG_DOUBLE;
        *curr_char_in_format += 2;
      } else {
        *lenght_modifier = LONG;
        *curr_char_in_format += 1;
      }
      break;
    case 'L':
      *lenght_modifier = LONG_DOUBLE;
      *curr_char_in_format += 1;
      break;
    default:
      break;
  }
}

void in_width(const char *format, int *miss_input,
              s21_size_t *curr_char_in_format, int *number_width,
              enum Condition *condition) {
  if (format[*curr_char_in_format] == '*') {
    *miss_input = 1;
    *curr_char_in_format += 1;
  }
  while (isdigit(format[*curr_char_in_format])) {
    if (*number_width == -1) *number_width = 0;

    *number_width = 10 * (*number_width) + format[*curr_char_in_format] - '0';
    *curr_char_in_format += 1;
  }
  *condition = IN_FORMAT;
}

int no_condition(const char *format, const char *buf,
                 s21_size_t *curr_char_in_format, int *curr_char_in_buf,
                 enum Condition *condition) {
  int output = 0;
  if (format[*curr_char_in_format] == '%') {
    *curr_char_in_format += 1;
    *condition = IN_WIDTH;
  } else if (format[*curr_char_in_format] == buf[*curr_char_in_buf]) {
    *curr_char_in_buf += 1;
    *curr_char_in_format += 1;
  } else if (format[*curr_char_in_format] == ' ' ||
             format[*curr_char_in_format] == '\t' ||
             format[*curr_char_in_format] == '\n') {
    *curr_char_in_format += 1;
  } else {
    output = 1;
  }
  return output;
}
