#include "header.h"

static struct option long_option[] = {{"number-nonblank", 0, 0, 'b'},
                                      {"number", 0, 0, 'n'},
                                      {"squeeze-blank", 0, 0, 's'},
                                      {0, 0, 0, 0}};

void cat(FILE *mf, opt options, const char *table[static 256]) {
  int symbol = 0;
  int last = '\n';
  bool squeeze = false;
  int count_lines = 0;
  while (fread(&symbol, 1, 1, mf) > 0) {
    if (last == '\n') {
      if (options.s && symbol == '\n') {
        if (squeeze) continue;
        squeeze = true;
      } else {
        squeeze = false;
      }
      if (options.b) {
        if (symbol != '\n') {
          printf("%6i\t", ++count_lines);
        } else if (options.e) {
          printf("%6s\t", " ");
        }
      } else if (options.n) {
        printf("%6i\t", ++count_lines);
      }
    }
    if (!*table[symbol])
      printf("%c", '\0');
    else
      printf("%s", table[symbol]);
    last = symbol;
  }
}

int parser(int argc, char *argv[], opt *options) {
  int opt, option_index;
  int error = 0;

  while ((opt = getopt_long(argc, argv, "+benstvTE", long_option,
                            &option_index)) != -1) {
    switch (opt) {
      case 'v':
        options->v = true;
        break;
      case 'b':
        options->b = true;
        break;
      case 'n':
        options->n = true;
        break;
      case 's':
        options->s = true;
        break;
      case 'e':
        options->e = options->v = true;
        break;
      case 't':
        options->t = options->v = true;
        break;
      case 'E':
        options->e = true;
        break;
      case 'T':
        options->t = true;
        break;
      default:
        error = 1;
        break;
    }
    if (error == 1) break;
  }
  return error;
}

void reader(int argc, char *argv[], opt options,
            const char *table[static 256]) {
  FILE *mf = NULL;
  int error = 0;
  while (optind != argc) {
    mf = fopen(argv[optind], "rb");
    if (mf == NULL) {
      fprintf(stderr, "error_open_file");
      break;
    } else {
      cat(mf, options, table);
      optind++;
      if (fclose(mf) == EOF) {
        fprintf(stderr, "error_close_file");
        error = 1;
      }
    }
    if (error == 1) break;
  }
}

void cat_set_table(const char *table[static 256]) {
  const char *raw_table[] = {
      "\00",  "\01",  "\02",  "\03",  "\04",  "\05",  "\06",  "\07",  "\b",
      "\t",   "\n",   "\v",   "\014", "\r",   "\016", "\017", "\020", "\021",
      "\022", "\023", "\024", "\025", "\026", "\027", "\030", "\031", "\032",
      "\033", "\034", "\035", "\036", "\037", " ",    "!",    "\"",   "#",
      "$",    "%",    "&",    "\'",   "(",    ")",    "*",    "+",    ",",
      "-",    ".",    "/",    "0",    "1",    "2",    "3",    "4",    "5",
      "6",    "7",    "8",    "9",    ":",    ";",    "<",    "=",    ">",
      "?",    "@",    "A",    "B",    "C",    "D",    "E",    "F",    "G",
      "H",    "I",    "J",    "K",    "L",    "M",    "N",    "O",    "P",
      "Q",    "R",    "S",    "T",    "U",    "V",    "W",    "X",    "Y",
      "Z",    "[",    "\\",   "]",    "^",    "_",    "`",    "a",    "b",
      "c",    "d",    "e",    "f",    "g",    "h",    "i",    "j",    "k",
      "l",    "m",    "n",    "o",    "p",    "q",    "r",    "s",    "t",
      "u",    "v",    "w",    "x",    "y",    "z",    "{",    "|",    "}",
      "~",    "\x7f", "\x80", "\x81", "\x82", "\x83", "\x84", "\x85", "\x86",
      "\x87", "\x88", "\x89", "\x8a", "\x8b", "\x8c", "\x8d", "\x8e", "\x8f",
      "\x90", "\x91", "\x92", "\x93", "\x94", "\x95", "\x96", "\x97", "\x98",
      "\x99", "\x9a", "\x9b", "\x9c", "\x9d", "\x9e", "\x9f", "\xa0", "\xa1",
      "\xa2", "\xa3", "\xa4", "\xa5", "\xa6", "\xa7", "\xa8", "\xa9", "\xaa",
      "\xab", "\xac", "\xad", "\xae", "\xaf", "\xb0", "\xb1", "\xb2", "\xb3",
      "\xb4", "\xb5", "\xb6", "\xb7", "\xb8", "\xb9", "\xba", "\xbb", "\xbc",
      "\xbd", "\xbe", "\xbf", "\xc0", "\xc1", "\xc2", "\xc3", "\xc4", "\xc5",
      "\xc6", "\xc7", "\xc8", "\xc9", "\xca", "\xcb", "\xcc", "\xcd", "\xce",
      "\xcf", "\xd0", "\xd1", "\xd2", "\xd3", "\xd4", "\xd5", "\xd6", "\xd7",
      "\xd8", "\xd9", "\xda", "\xdb", "\xdc", "\xdd", "\xde", "\xdf", "\xe0",
      "\xe1", "\xe2", "\xe3", "\xe4", "\xe5", "\xe6", "\xe7", "\xe8", "\xe9",
      "\xea", "\xeb", "\xec", "\xed", "\xee", "\xef", "\xf0", "\xf1", "\xf2",
      "\xf3", "\xf4", "\xf5", "\xf6", "\xf7", "\xf8", "\xf9", "\xfa", "\xfb",
      "\xfc", "\xfd", "\xfe", "\xff"};

  memcpy(table, raw_table, sizeof raw_table);
}

void cat_set_E(const char *table[static 256]) { table['\n'] = "$\n"; }

void cat_set_T(const char *table[static 256]) { table['\t'] = "^I"; }

void cat_set_v(const char *table[static 256]) {
  const char *sample1[] = {"^@", "^A", "^B", "^C", "^D",
                           "^E", "^F", "^G", "^H"};
  const char *sample2[] = {"^K", "^L", "^M", "^N",  "^O", "^P", "^Q",
                           "^R", "^S", "^T", "^U",  "^V", "^W", "^X",
                           "^Y", "^Z", "^[", "^\\", "^]", "^^", "^_"};
  const char *sample3[] = {
      "^?",   "M-^@", "M-^A",  "M-^B", "M-^C", "M-^D", "M-^E", "M-^F", "M-^G",
      "M-^H", "M-^I", "M-^J",  "M-^K", "M-^L", "M-^M", "M-^N", "M-^O", "M-^P",
      "M-^Q", "M-^R", "M-^S",  "M-^T", "M-^U", "M-^V", "M-^W", "M-^X", "M-^Y",
      "M-^Z", "M-^[", "M-^\\", "M-^]", "M-^^", "M-^_", "M- ",  "M-!",  "M-\"",
      "M-#",  "M-$",  "M-%",   "M-&",  "M-'",  "M-(",  "M-)",  "M-*",  "M-+",
      "M-,",  "M--",  "M-.",   "M-/",  "M-0",  "M-1",  "M-2",  "M-3",  "M-4",
      "M-5",  "M-6",  "M-7",   "M-8",  "M-9",  "M-:",  "M-;",  "M-<",  "M-=",
      "M->",  "M-?",  "M-@",   "M-A",  "M-B",  "M-C",  "M-D",  "M-E",  "M-F",
      "M-G",  "M-H",  "M-I",   "M-J",  "M-K",  "M-L",  "M-M",  "M-N",  "M-O",
      "M-P",  "M-Q",  "M-R",   "M-S",  "M-T",  "M-U",  "M-V",  "M-W",  "M-X",
      "M-Y",  "M-Z",  "M-[",   "M-\\", "M-]",  "M-^",  "M-_",  "M-`",  "M-a",
      "M-b",  "M-c",  "M-d",   "M-e",  "M-f",  "M-g",  "M-h",  "M-i",  "M-j",
      "M-k",  "M-l",  "M-m",   "M-n",  "M-o",  "M-p",  "M-q",  "M-r",  "M-s",
      "M-t",  "M-u",  "M-v",   "M-w",  "M-x",  "M-y",  "M-z",  "M-{",  "M-|",
      "M-}",  "M-~",  "M-?"};
  memcpy(table, sample1, sizeof sample1);
  memcpy(&table[9 + 2], sample2, sizeof sample2);
  memcpy(&table['~' + 1], sample3, sizeof sample3);
}
