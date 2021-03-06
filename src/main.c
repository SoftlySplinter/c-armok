#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

#include "syntax.h"
#include "parse.h"
#include "run.h"

int dwarves_alive(fortress *fort) {
  for(int i = 0; i < (fort->dwarf_size + fort->sub_size); i++) {
    if(!fort->dwarves[i]->dead) {
      return 1;
    }
  }
  return 0;
}

char *load(char *filename) {
  char * buffer = 0;
  long length;
   FILE * f = fopen (filename, "rb");

  if (f)
  {
    fseek (f, 0, SEEK_END);
    length = ftell (f);
    fseek (f, 0, SEEK_SET);
    buffer = malloc (length);
    if (buffer)
    {
      int res = fread (buffer, 1, length, f);
    }
    fclose (f);
  }
  return buffer;  
}

int main(int argc, char** argv) {
  setlocale(LC_ALL,"");

  if(argc <= 1) {
    fprintf(stderr, "Expected at least 1 argument\n");
    return 255;
  }

  char *prog = load(argv[1]);

  if(syntax_check(prog)) {
    fortress *fort = parse(prog);

    setup(argv[2], fort);

    while(dwarves_alive(fort)) {
      step();
    }

    free_fort(fort);
    teardown();
    free(prog);
    printf("\n");
  }

  return EXIT_SUCCESS;
}


