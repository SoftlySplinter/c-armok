#ifndef ARMOK_SYNTAX
#define ARMOK_SYNTAX

// Constructs
#define DWARF '+'
#define SUB '-'

// Operations
#define LEFT '<'
#define RIGHT '>'
#define WORK 'w'
#define BUILD 'b'

// Functions
#define MINE 'm'
#define DUMP 'd'

// Comment
#define COMMENT '!'

// Checks the syntax of a token is correct, given all previous tokens.
//  token - the token to check the correctness of.
// Returns false if the token is syntacitcally incorrect and will set
// parse_error to an error message relating to the syntacical problem.
int syntactically_correct(char token);

// Checks the syntax of a program file is valid
int syntax_check(char *tokens);

#endif
