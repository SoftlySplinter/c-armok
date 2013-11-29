#include <stdio.h>
#include <ctype.h>
#include "syntax.h"

char *syntax_error = NULL;

int prev_comment = 0;
int _syn_dwarf = 0;
int _syn_sub = 0;
int _syn_comment = 0;

int syntactically_correct(char token) {
  int temp_prev_comment = prev_comment;
  prev_comment = 0;
  switch(token) {
  case '\0':
    if(!(_syn_dwarf > 0)) {
      syntax_error = "No dwarves";
    }
    return _syn_dwarf > 0;
  case COMMENT:
    if(temp_prev_comment) {
      _syn_comment ^= 1;
    } else {
      prev_comment = 1;
    }
    return 1;
  }

  if(isspace(token) || _syn_comment) {
    return 1;
  }


  switch(token) {
  case SUB:
    _syn_sub++;
    return 1;
  case DWARF:
    _syn_dwarf++;
    return 1;
  }

  // Valid tokens, given that a sub or dwarf exists.
  if(_syn_dwarf || _syn_sub) {
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
  _syn_comment = 0;
  prev_comment = 0;
  _syn_dwarf = 0;
  _syn_sub = 0;

  char token;
  int line = 1;
  int byte = 1;
  int res;
  int end_res = 1;
  do {
    token = *tokens;
    switch(token) {
      case '\n':
        line++;
        byte = 1;
        break;
      default:
        res = syntactically_correct(token);
        if(!res) {
          fprintf(stderr, "file.df:%d:%d: error: %s\n", byte, line, syntax_error);
          end_res = 0;
        }
        byte++;
        break;
    }
    tokens++;
  } while(token != '\0');
  return end_res;
}

