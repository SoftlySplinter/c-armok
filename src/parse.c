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

fortress *parse(char *tokens) {
  fortress *fort = malloc(sizeof(fortress));
  fort->dwarf_size = count(tokens, DWARF);
  fort->sub_size = count(tokens, SUB);
  fort->alive = fort->dwarf_size;
  fort->dwarves = malloc(sizeof(dwarf*) * fort->dwarf_size);
  fort->subs = malloc(sizeof(sub*) * fort->sub_size);
  int cur_dwarf_id = -1;
  int cur_sub_id = -1;
  int dwarf_or_sub = 0;

  char token;
  do {
    token = *tokens;
    
    switch(token) {
      case DWARF:
        cur_dwarf_id++;
        dwarf *d = malloc(sizeof(dwarf));
        d->id = cur_dwarf_id;
        d->pos = 1;
        d->instructions = malloc(sizeof(char));
        d->dead = 0;
        d->rocks = 0;
        fort->dwarves[cur_dwarf_id] = d;
        dwarf_or_sub = 1;
        break;
      case SUB:
        cur_sub_id++;
        sub *s = malloc(sizeof(sub));
        s->id = cur_sub_id;
        s->instructions = malloc(sizeof(char));
        fort->subs[cur_sub_id] = s;
        dwarf_or_sub = 2;
        break;
      default:
        if(dwarf_or_sub == 1) {
          char *inst = fort->dwarves[cur_dwarf_id]->instructions;
          int len = strlen(inst);
          fort->dwarves[cur_dwarf_id]->instructions = (char *) realloc(inst, len + 1);
          strncat(inst, &token, len + 1);
        }
        if(dwarf_or_sub == 2) {
          char *inst = fort->subs[cur_sub_id]->instructions;
          int len = strlen(inst);
          fort->subs[cur_sub_id]->instructions = (char *) realloc(inst, len + 1);
          strncat(inst, &token, len + 1);
        }
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
  for(int i = 0; i< fortress->sub_size; i++) {
    free(fortress->subs[i]->instructions);
    free(fortress->subs[i]);
  }

  free(fortress);
}

