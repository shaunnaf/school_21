#ifndef header_h
#define header_h

#define _GNU_SOURCE

#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Patterns {
  char **data;
  size_t cur_size;
  size_t max_size;
} Patterns;

typedef struct options {
  int regex_flag;
  bool v, c, l, n, h, s, o, f, e;
  struct Patterns patts;
} opt;

int parser(int argc, char *argv[], opt *options);
// void grep(FILE *mf, opt options, regex_t *preg, bool multiple_files,
//         char *filename);
void reader(int argc, char *argv[], opt *options);
void grep_2(FILE *mf, int argc, char *argv[], opt options, regex_t *preg,
            bool multiple_files, char *filename);
void patterns_init(Patterns *const patts);
void patterns_add(Patterns *const patts, const char *const patt);
void patterns_add_from_string(Patterns *const patts, const char *const str);
int patterns_add_from_file(Patterns *const patts, char *const filename);
void options_free(opt *options);
void patterns_free(Patterns *const patts);

#endif /* moduls_h */
