#define _GNU_SOURCE
#include <getopt.h>
#include <pcre.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Flags {
  bool flag_e;
  bool flag_i;
  bool flag_v;
  bool flag_c;
  bool flag_l;
  bool flag_n;
  bool flag_h;
  bool flag_s;
  bool flag_f;
  bool flag_o;
  int file_count;
};

struct arguments {
  pcre **pattern;
  int count;
};

void flags_parcer(int argc, char **argv, struct arguments *template,
                  struct Flags *flags);
void Grep_regular(char *source_line, struct arguments *template,
                  struct Flags *flags);
void Grep_regular_from_file(char *filename, struct arguments *template,
                            struct Flags *flags);
void free_memory(struct arguments *template);
void Grep_functional(char *filename, struct arguments template,
                     struct Flags flags);
void Grep_with_flag_c(FILE *file, char *filename, struct arguments template,
                      struct Flags flags);
void Grep_with_flag_l(FILE *file, char *filename, struct arguments template,
                      struct Flags flags);
void Grep_with_flag_o(FILE *file, char *filename, struct arguments template,
                      struct Flags flags);
void Grep_with_flag_v(FILE *file, char *filename, struct arguments template,
                      struct Flags flags);

int main(int argc, char **argv) {
  struct Flags flags = {false, false, false, false, false, false,
                        false, false, false, false, 0};
  struct arguments patterns = {NULL, 0};
  flags_parcer(argc, argv, &patterns, &flags);
  if (!flags.flag_e) {
    if (optind < argc) Grep_regular(argv[optind++], &patterns, &flags);
  }
  if (argc - optind > 1) flags.file_count = 1;
  for (int i = optind; i < argc; i++) Grep_functional(argv[i], patterns, flags);
  free_memory(&patterns);
  return 0;
}

void flags_parcer(int argc, char **argv, struct arguments *patterns,
                  struct Flags *flags) {
  int current_flag;
  while ((current_flag = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (current_flag) {
      case 'e':
        flags->flag_e = true;
        Grep_regular(optarg, patterns, flags);
        break;
      case 'i':
        flags->flag_i = true;
        break;
      case 'v':
        flags->flag_v = true;
        break;
      case 'c':
        flags->flag_c = true;
        break;
      case 'l':
        flags->flag_l = true;
        break;
      case 'n':
        flags->flag_n = true;
        break;
      case 'h':
        flags->flag_h = true;
        break;
      case 's':
        flags->flag_s = true;
        break;
      case 'f':
        flags->flag_f = true;
        flags->flag_e = true;
        Grep_regular_from_file(optarg, patterns, flags);
        break;
      case 'o':
        flags->flag_o = true;
        break;
      default:
        fprintf(stderr, "Invalid flag\n");
        exit(1);
        break;
    }
  }
}
/*
int pcre_exec(const pcre *code, const pcre_extra *extra, PCRE_SPTR subject, int
length, int startoffset, int options, int *ovector, int ovecsize);

Параметры функции:

1) code: Указатель на скомпилированное регулярное выражение (результат
2) pcre_compile. extra: Дополнительные параметры
3) subject: Строка текста, в которой будет выполняться поиск совпадения.
4) length: Длина строки текста.
5) startoffset: Начальное смещение в строке, с которого начинается поиск.
6) options: Опции поиска.
7) ovector: Массив для хранения информации о совпадениях
8) ovecsize: Размер массива ovector в элементах.

pcre *pcre_compile(const char *pattern, int options, const char **errptr, int
*erroffset, const unsigned char *tables);

Параметры функции:

1) pattern: указатель на строку, содержащую регулярное выражение.
2) options: опции компиляции, которые управляют поведением регулярного
выражения. Например, можно указать игнорирование регистра или включение режима
многострочного поиска.
3) errptr: указатель на строку, в которой будет сохранено сообщение об ошибке
4) erroffset: указатель на переменную, в которой будет сохранено смещение
синтаксической ошибки в регулярном выражении. Если компиляция прошла успешно,
это значение будет -1.
5) tables: указатель на таблицу символов, которая является необязательным
параметром. Если не указано, будет использоваться таблица по умолчанию.
*/

void Grep_regular(char *current_line, struct arguments *patterns,
                  struct Flags *flags) {
  const char *error;
  int erroffset;
  pcre *regular_expression =
      pcre_compile(current_line, ((flags->flag_i) ? PCRE_CASELESS : 0), &error,
                   &erroffset, NULL);
  if (regular_expression) {
    patterns->count++;
    patterns->pattern =
        realloc(patterns->pattern, patterns->count * sizeof(pcre *));
    patterns->pattern[patterns->count - 1] = regular_expression;
  } else {
    fprintf(stderr, "Failed to compile regular expression\n");
    exit(1);
  }
}

void Grep_regular_from_file(char *filename, struct arguments *patterns,
                            struct Flags *flags) {
  size_t length = 0;
  char *current_line = NULL;
  FILE *file = fopen(filename, "r");
  if (file) {
    while (getline(&current_line, &length, file) != EOF) {
      if (current_line) {
        if (current_line[strlen(current_line) - 1] == '\n')
          current_line[strlen(current_line) - 1] = '\0';
      }
      Grep_regular(current_line, patterns, flags);
    }
    free(current_line);
    fclose(file);
  } else {
    fprintf(stderr, "No such file or directory\n");
    exit(1);
  }
}

void free_memory(struct arguments *patterns) {
  if (patterns->pattern) {
    for (int i = 0; i < patterns->count; i++) {
      if (patterns->pattern[i]) pcre_free(patterns->pattern[i]);
    }
    free(patterns->pattern);
  }
}

void Grep_functional(char *filename, struct arguments patterns,
                     struct Flags flags) {
  FILE *file = fopen(filename, "r");
  if (file) {
    if (flags.flag_c) Grep_with_flag_c(file, filename, patterns, flags);
    if (flags.flag_l)
      Grep_with_flag_l(file, filename, patterns, flags);
    else if (flags.flag_o && !flags.flag_v)
      Grep_with_flag_o(file, filename, patterns, flags);
    else
      Grep_with_flag_v(file, filename, patterns, flags);
    fclose(file);
  } else {
    if (!flags.flag_s) fprintf(stderr, "No such file or directory");
  }
}

void Grep_with_flag_c(FILE *file, char *filename, struct arguments patterns,
                      struct Flags flags) {
  size_t length = 0;
  char *current_line = NULL;
  int file_count = 0;
  int line_number = 0;
  int match_count = 0;
  int ovector[50];
  while (getline(&current_line, &length, file) != EOF) {
    line_number++;
    for (int i = 0; i < patterns.count; i++) {
      if ((pcre_exec(patterns.pattern[i], NULL, current_line,
                     strlen(current_line), 0, 0, ovector, 50)) > 0)
        match_count++;
    }
  }
  if (match_count > 0 || ((line_number - match_count) > 0 && flags.flag_v))
    file_count = 1;
  if (flags.file_count && !flags.flag_h) printf("%s:", filename);
  if (flags.flag_l)
    printf("%d\n", file_count);
  else
    printf("%d\n", (flags.flag_v ? line_number - match_count : match_count));
  free(current_line);
}

void Grep_with_flag_l(FILE *file, char *filename, struct arguments patterns,
                      struct Flags flags) {
  size_t length = 0;
  char *current_line = NULL;
  int check_match = 0;
  int ovector[50];
  fseek(file, 0, 0);
  while (getline(&current_line, &length, file) != EOF) {
    for (int i = 0; i < patterns.count && !check_match; i++) {
      if (((flags.flag_v ? -1 : 1) *
           pcre_exec(patterns.pattern[i], NULL, current_line,
                     strlen(current_line), 0, 0, ovector, 50)) > 0) {
        printf("%s\n", filename);
        check_match = 1;
      }
    }
  }
  free(current_line);
}

//
void Grep_with_flag_o(FILE *file, char *filename, struct arguments patterns,
                      struct Flags flags) {
  size_t length = 0;
  char *current_line = NULL;
  int line_number = 0;
  int ovector[50];
  while ((getline(&current_line, &length, file) != EOF)) {
    line_number++;
    for (int i = 0; i < patterns.count; i++) {
      unsigned int offset = 0;
      length = strlen(current_line);
      int regular_expression;
      while (offset < length &&
             (regular_expression = pcre_exec(patterns.pattern[i], 0,
                                             current_line, strlen(current_line),
                                             offset, 0, ovector, 50)) > 0) {
        for (int j = 0; j < regular_expression; ++j) {
          if (flags.file_count && !flags.flag_h) printf("%s:", filename);
          if (flags.flag_n) printf("%d:", line_number);
          size_t start_index = (ovector[2 * j] > 0) ? ovector[2 * j] : 0;
          size_t end_index = (strlen(current_line) < (size_t)ovector[2 * j + 1])
                                 ? strlen(current_line)
                                 : (size_t)ovector[2 * j + 1];
          for (size_t k = start_index; k < end_index; k++)
            printf("%c", current_line[k]);
          printf("\n");
        }
        offset = ovector[1];
      }
    }
  }
  free(current_line);
}

void Grep_with_flag_v(FILE *file, char *filename, struct arguments patterns,
                      struct Flags flags) {
  size_t length = 0;
  char *current_line = NULL;
  int check_match = 0;
  int line_number = 0;
  int ovector[50];
  while (getline(&current_line, &length, file) != EOF) {
    check_match = 0;
    line_number++;
    for (int i = 0; i < patterns.count && !check_match; i++) {
      if ((pcre_exec(patterns.pattern[i], NULL, current_line,
                     strlen(current_line), 0, 0, ovector, 50)) > 0)
        check_match = 1;
    }
    if (flags.flag_v) check_match = !check_match;
    if (check_match) {
      if (flags.file_count && !flags.flag_h) printf("%s:", filename);
      if (flags.flag_n) printf("%d:", line_number);
      printf((current_line[strlen(current_line) - 1] == '\n' ? "%s" : "%s\n"),
             current_line);
    }
  }
  free(current_line);
}
