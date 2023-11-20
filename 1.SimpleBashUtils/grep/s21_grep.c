#include "header.h"

int main(int argc, char *argv[]) {
  opt options = {0};
  if (!parser(argc, argv, &options)) {
    reader(argc, argv, &options);
  }
  options_free(&options);

  return 0;
}
