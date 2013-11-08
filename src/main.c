#include <stdlib.h>
#include <stdio.h>

#include "parse.h"

int main(int argc, char** argv) {
  if(argc <= 1) {
    fprintf(stderr, "Expected at least 1 argument\n");
    return 255;
  }

  syntax_check(argv[argc-1]);

  return EXIT_SUCCESS;
}


