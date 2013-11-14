#ifndef ARMOK_SYNTAX
#define ARMOK_SYNTAX

#define DWARF '+'
#define SUB '-'
#define LEFT '<'
#define RIGHT '>'
#define MINE 'm'
#define WORK 'w'
#define DUMP 'd'

/* Checks the syntax of a token is correct, given all previous tokens.
 *  token - the token to check the correctness of.
 * Returns false if the token is syntacitcally incorrect and will set
 * parse_error to an error message relating to the syntacical problem.
 */
int syntactically_correct(char token);

// Checks the syntax of a program file is valid
int syntax_check(char *tokens);

#endif
