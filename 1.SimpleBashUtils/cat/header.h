
#ifndef header_h
#define header_h

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct options {
  bool b, e, n, s, t, v;
} opt;

int parser(int argc, char *argv[], opt *options);
void cat(FILE *mf, opt options, const char *table[static 256]);
void reader(int argc, char *argv[], opt options, const char *table[static 256]);
void cat_set_table(const char *table[static 256]);
void cat_set_E(const char *table[static 256]);
void cat_set_T(const char *table[static 256]);
void cat_set_v(const char *table[static 256]);

#endif /* moduls_h */
