#include <stdio.h>

#include "header.h"

int main(int argc, char *argv[]) {
  opt options = {false, false, false, false, false, false};
  const char *table[256];

  cat_set_table(table);
  if (!parser(argc, argv, &options)) {
    if (options.v) cat_set_v(table);
    if (options.e) cat_set_E(table);
    if (options.t) cat_set_T(table);

    reader(argc, argv, options, table);
  }

  return 0;
}
