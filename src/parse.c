#include <stdio.h>

#include "parse.h"

char *parse_error = "";

int syntax_check_token(char token) {
  static int sub;
  static int dwarf;

  if(token == SUB) {
    sub++;
    return 1;
  }

  if(token == DWARF) {
    dwarf++;
    return 1;
  }

  if(token == '\0') {
    int ret = dwarf > 0;
    if(!ret) {
      parse_error = "No dwarves";
    }
    return ret;
  }

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

  parse_error = "Illegal token";
  return 0;
}

int syntax_check(char *tokens) {
  char token = *tokens;
  int line = 1;
  int byte = 1;
  int result = 1;
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
        result *= res;
        if(!res) {
          fprintf(stderr, "file.df:%d:%d: error: %s\n", byte, line,  parse_error);
        }
      case ' ':
        byte++;
        break;
    }
    tokens++;
  } while(token != '\0');
  return 0;
}

