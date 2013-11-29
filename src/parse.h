#ifndef ARMOK_PARSE
#define ARMOK_PARSE


// Defines a dwarf
typedef struct _dwarf {
  int id;
  int pos;
  char *instructions;
  int inst_offset;
  int dead;
  int rocks;
} dwarf;

typedef struct _fortress {
  int dwarf_size;
  int sub_size;
  int alive;
  dwarf **dwarves;
} fortress;


// Parses a program file
fortress *parse(char *tokens);

void free_fort(fortress* fortress);

#endif // ARMOK_PARSE
