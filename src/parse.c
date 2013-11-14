#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse.h"

char *parse_error = "";

/* Checks the syntax of a token is correct, given all previous tokens.
 *  token - the token to check the correctness of.
 * Returns false if the token is syntacitcally incorrect and will set
 * parse_error to an error message relating to the syntacical problem.
 */
int syntax_check_token(char token) {
  // These two are inverted due to the initialisation value of 0 of static
  // integers
  static int sub;
  static int dwarf;

  // Special case to ensure the program can run.
  if(token == '\0') {
    int ret = dwarf > 0;
    if(!ret) {
      parse_error = "No dwarves";
    }
    return ret;
  }

  if(token == '\n' || token == ' ') return 1;

  // Subroutine and dwarf token.
  if(token == SUB) {
    sub++;
    return 1;
  }
  if(token == DWARF) {
    dwarf++;
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

  parse_error = "Illegal token";
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
          fprintf(stderr, "file.df:%d:%d: error: %s\n", byte, line,  parse_error);
        }
      case ' ':
        byte++;
        break;
    }
    tokens++;
  } while(token != '\0');
  return res;
}

int count(char *tokens, char search) {
  char token;
  int count = 0;
  do {
    token = *tokens;
    if(token == search) count++;
    tokens++;
  } while(token != '\0');
  return count;
}

int inst_len(char *tokens) {
  int len = 0;
  while(*(tokens + 1 + len) != DWARF && 
        *(tokens + 1 + len) != SUB && 
        *(tokens + 1 + len) != '\0') {
    len++;
  }
  return len;
}

fortress *parse(char *tokens) {
  fortress *fort = malloc(sizeof(fortress));
  fort->dwarf_size = count(tokens, DWARF) + count(tokens, SUB);
  fort->alive = fort->dwarf_size;
  fort->dwarves = malloc(sizeof(dwarf*) * fort->dwarf_size);
  int cur_id = -1;
  dwarf *cur = NULL;

  char token;
  int step = 0;
  do {
    token = *tokens;
    
    switch(token) {
      case DWARF:
      case SUB:
        cur_id++;
        dwarf *cur = malloc(sizeof(dwarf));
        cur->id = cur_id;
        cur->pos = 1;
        int l = inst_len(tokens);
        cur->instructions = malloc(sizeof(char) * l);
        cur->inst_offset = 0;
        cur->dead = (token != DWARF);
        cur->rocks = 0;
        fort->dwarves[cur_id] = cur;
        step = 0;
        break;
      case MINE:
      case WORK:
      case DUMP:
      case LEFT:
      case RIGHT:
        cur->instructions[step] = token;
        step++;
    }
    tokens++;
  } while(token != '\0');
  return fort;
}

void free_fort(fortress* fortress) {
  for(int i = 0; i < fortress->dwarf_size; i++) {
    free(fortress->dwarves[i]->instructions);
    free(fortress->dwarves[i]);
  }
  free(fortress->dwarves);
  free(fortress);
}

