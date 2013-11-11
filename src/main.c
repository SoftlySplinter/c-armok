#include <stdlib.h>
#include <stdio.h>

#include "parse.h"
#include "run.h"

int dwarves_alive(fortress *fort) {
  for(int i = 0; i < fort->dwarf_size; i++) {
    if(!fort->dwarves[i]->dead) {
      return 1;
    }
  }
  return 0;
}

int main(int argc, char** argv) {
  if(argc <= 1) {
    fprintf(stderr, "Expected at least 1 argument\n");
    return 255;
  }

  if(syntax_check(argv[argc-1])) {
    fortress *fort = parse(argv[argc-1]);

    setup();

    while(dwarves_alive(fort)) {
      for(int i = 0; i < fort->dwarf_size; i++) {
        step(fort->dwarves[i]);
      }
      step_inc();
    }

    teardown();
    free_fort(fort);
  }

  return EXIT_SUCCESS;
}


