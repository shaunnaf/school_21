#include "header.h"

void grep_files_with_matches(bool multiple_files, char *filename, opt options,
                             int count_line_c) {
  if (count_line_c > 0) {
    if (options.c) {
      if (!options.h && multiple_files) printf("%s:", filename);
      printf("1\n");
    }
    printf("%s\n", filename);
  } else {
    if (!options.h && multiple_files) printf("%s:", filename);
    if (options.c) printf("0\n");
  }
}

void grep_match_count(bool multiple_files, char *filename, opt options,
                      int count_line_c) {
  if (!options.h && multiple_files) printf("%s:", filename);
  printf("%d\n", count_line_c);
}

void grep_lines_with_matches(regmatch_t match, char *line, opt options) {
  if (options.v)
    printf("%s", line);
  else {
    for (int j = match.rm_so; j < match.rm_eo; ++j) {
      printf("%c", line[j]);
    }
    printf("\n");
  }
}

void grep_2(FILE *mf, int argc, char *argv[], opt options, regex_t *preg,
            bool multiple_files, char *filename) {
  char *line = 0;
  int count_line_c, count_line_n, res;
  char *end = argv[argc];
  count_line_c = count_line_n = 0;
  size_t lenght = 0;
  regmatch_t match;
  while (getline(&line, &lenght, mf) > 0) {
    for (size_t i = 0; i < options.patts.cur_size; i++) {
      if (regcomp(preg, options.patts.data[i], options.regex_flag))
        fprintf(stderr, "failed to compile regcomp");
      else {
        if (options.patts.data[i] == end)
          fprintf(stderr, "no pattern\n");
        else {
          count_line_n++;
          res = regexec(preg, line, 1, &match, 0);
          if (options.v) {
            if (res == 0) {
              if (options.patts.cur_size > 1) break;
              res = 1;
            } else {
              if (i + 1 == options.patts.cur_size) res = 0;
            }
          }
          if (res == 0) {
            count_line_c++;
            if (!(options.l || options.c)) {
              if (!options.h && multiple_files) printf("%s:", filename);
              if (options.n) printf("%d:", count_line_n);
              if (options.o)
                grep_lines_with_matches(match, line, options);
              else {
                printf("%s", line);
              }
            }
            if (options.patts.cur_size > 1) break;
          }
        }
      }
    }
  }
  if (options.l)
    grep_files_with_matches(multiple_files, filename, options, count_line_c);
  else if (options.c)
    grep_match_count(multiple_files, filename, options, count_line_c);
  else if (options.v && count_line_c != 0)
    printf("\n");
}

int parser(int argc, char *argv[], opt *options) {
  int opt;
  patterns_init(&options->patts);
  int error = 0;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        options->regex_flag |= REG_EXTENDED;
        patterns_add_from_string(&options->patts, optarg);
        options->e = true;
        break;
      case 'i':
        options->regex_flag |= REG_ICASE;
        break;
      case 'v':
        options->v = true;
        break;
      case 'c':
        options->c = true;
        break;
      case 'l':
        options->l = true;
        break;
      case 'n':
        options->n = true;
        break;
      case 'h':
        options->h = true;
        break;
      case 's':
        options->s = true;
        break;
      case 'o':
        options->o = true;
        break;
      case 'f':
        options->f = true;
        error = patterns_add_from_file(&options->patts, optarg);
        break;
      default:
        fprintf(stderr, "error_pattern");
        break;
        error = 1;
    }
    if (error == 1) {
      break;
    }
  }
  return error;
}

void reader(int argc, char *argv[], opt *options) {
  FILE *mf = NULL;
  bool multiple_files = false;
  regex_t preg_storage;
  regex_t *preg = &preg_storage;
  char *filename;
  if (options->e || options->f)
    optind--;
  else {
    patterns_add_from_string(&options->patts, argv[optind]);
  }
  if (optind + 2 != argc) multiple_files = true;
  for (optind++; optind != argc; optind++) {
    filename = argv[optind];
    mf = fopen(filename, "rb");
    if (mf == NULL) {
      if (options->s) continue;
      fprintf(stderr, "error_open_file");
      break;
    } else {
      grep_2(mf, argc, argv, *options, preg, multiple_files, filename);
    }
    fclose(mf);
  }
  regfree(preg);
}

void patterns_init(Patterns *const patts) {
  patts->cur_size = 0;
  patts->max_size = 128;
  patts->data = malloc(sizeof(char *) * patts->max_size);
}

void patterns_add_from_string(Patterns *const patts, const char *const str) {
  char *temp_patts = malloc(sizeof(char) * strlen(str) + sizeof(char));
  strcpy(temp_patts, str);
  char *token = strtok(temp_patts, "\n");
  while (token != NULL) {
    patterns_add(patts, token);
    token = strtok(NULL, "\n");
  }
  free(temp_patts);
}

void patterns_add(Patterns *const patts, const char *const patt) {
  if (patts->cur_size == patts->max_size) {
    patts->max_size += 128;
    patts->data = realloc(patts->data, patts->max_size * sizeof(char *));
  }
  patts->data[patts->cur_size] =
      malloc(sizeof(char) * strlen(patt) + sizeof(char));
  strcpy(patts->data[patts->cur_size++], patt);
}

void options_free(opt *options) { patterns_free(&options->patts); }

void patterns_free(Patterns *const patts) {
  for (size_t i = 0; i < patts->cur_size; ++i) {
    free(patts->data[i]);
  }
  free(patts->data);
}

int patterns_add_from_file(Patterns *const patts, char *const filename) {
  int error = 0;
  FILE *file = fopen(filename, "rb");
  if (file == NULL) {
    fprintf(stderr, "error_open_patter_file");
    error = 1;
  } else {
    char *buffer = malloc(sizeof(char) * 128);
    fscanf(file, "%s", buffer);
    patterns_add_from_string(patts, buffer);
    free(buffer);
    fclose(file);
  }
  return error;
}
