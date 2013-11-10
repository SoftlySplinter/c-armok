#include <stdlib.h>
#include <stdio.h>

#include "parse.h"

int main(int argc, char** argv) {
  if(argc <= 1) {
    fprintf(stderr, "Expected at least 1 argument\n");
    return 255;
  }

  if(syntax_check(argv[argc-1])) {
    fortress *fort = parse(argv[argc-1]);
    printf("%s\n", fort->dwarves[0]->instructions);
    free_fort(fort);
  }

  return EXIT_SUCCESS;
}


