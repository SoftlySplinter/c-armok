#ifndef ARMOK_PARSE
#define ARMOK_PARSE

#define DWARF '+'
#define SUB '-'
#define LEFT '<'
#define RIGHT '>'
#define MINE 'm'
#define WORK 'w'
#define DUMP 'd'

// Defines an instruction stack
typedef struct _instr_stack {
  char instruction;
  struct _instr_stack *next;
} instr_stack;

// Defines a subroutine
typedef struct _sub {
  int id;
  instr_stack *instructions;
} sub;

// Defines a dwarf
typedef struct _dwarf {
  int id;
  int pos;
  sub* work_orders;
} dwarf;

// Checks the syntax of a program file is valid
int syntax_check(char *tokens);

// Parses a program file
void parse(char *tokens);

// Parses a token
void parse_token(char token);

// Adds an instruction to an instruction stack
void add_instruction(char token, instr_stack *stack);

#endif // ARMOK_PARSE
