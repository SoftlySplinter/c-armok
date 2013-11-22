#include <stdio.h>
#include <ctype.h>
#include "syntax.h"

char *syntax_error = NULL;

int comment = 0;
int prev_comment = 0;
int sub = 0;
int dwarf = 0;

int syntax_check_token(char token) {
  int temp_prev_comment = prev_comment;
  prev_comment = 0;
  switch(token) {
  case '\0':
    if(!(dwarf > 0)) {
      syntax_error = "No dwarves";
    }
    return dwarf > 0;
  case COMMENT:
    if(temp_prev_comment) {
      comment ^= 1;
    } else {
      prev_comment = 1;
    }
    return 1;
  case SUB:
    sub++;
    return 1;
  case DWARF:
    dwarf++;
    return 1;
  }

  if(isspace(token) || comment) {
    return 1;
  }

  // Valid tokens, given that a sub or dwarf exists.
  if(dwarf || sub) {
    switch(token) {
    case MINE:
    case DUMP:
    case WORK:
    case LEFT:
    case RIGHT:
      return 1;
    }
  }

  syntax_error = "Illegal token";
  return 0;
}

int syntax_check(char *tokens) {
  char token;
  int line = 1;
  int byte = 1;
  int res;
  do {
    token = *tokens;
    switch(token) {
      case '\n':
        line++;
        byte = 1;
        break;
      default:
        res = syntax_check_token(token);
        if(!res) {
          fprintf(stderr, "file.df:%d:%d: error: %s\n", byte, line, syntax_error);
        }
        byte++;
        break;
    }
    tokens++;
  } while(token != '\0');
  return res;
}

