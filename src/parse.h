#ifndef ARMOK_PARSE
#define ARMOK_PARSE

#define DWARF '+'
#define SUB '-'
#define LEFT '<'
#define RIGHT '>'
#define MINE 'm'
#define WORK 'w'
#define DUMP 'd'

// Defines a subroutine
typedef struct _sub {
  int id;
  char *instructions;
} sub;

// Defines a dwarf
typedef struct _dwarf {
  int id;
  int pos;
  char *instructions;
} dwarf;

typedef struct _fortress {
  int dwarf_size;
  int sub_size;
  int alive;
  dwarf **dwarves;
  sub **subs;
} fortress;

// Checks the syntax of a program file is valid
int syntax_check(char *tokens);

// Parses a program file
fortress *parse(char *tokens);


void free_fort(fortress* fortress);

#endif // ARMOK_PARSE
