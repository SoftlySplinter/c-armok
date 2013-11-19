#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "syntax.h"
#include "parse.h"

char *parse_error = "";

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
  int comment = 0;
  while(*(tokens + 1 + len) != DWARF && 
        *(tokens + 1 + len) != SUB && 
        *(tokens + 1 + len) != '\0') {
    if(*(tokens + 1) == COMMENT) comment ^= 1;
    if(!comment) len++;
  }
  return len;
}

fortress *parse(char *tokens) {
  fortress *fort = malloc(sizeof(fortress));
  fort->dwarf_size = count(tokens, DWARF) + count(tokens, SUB);
  fort->alive = fort->dwarf_size;
  fort->dwarves = malloc(sizeof(dwarf*) * fort->dwarf_size);
  int cur_id = -1;
  int comment = 0;
  dwarf *cur = NULL;

  char token;
  int step = 0;
  do {
    #ifdef DEBUG
    printf("Processing Token: %c\n", token);
    #endif

    token = *tokens;

    if(token == COMMENT) {
      comment ^= 1;
    }
    if(!comment) {
      switch(token) {
      case DWARF:
      case SUB:
        cur_id++;
        dwarf *cur = malloc(sizeof(dwarf));
        cur->id = cur_id;
        cur->pos = 1;
        int l = inst_len(tokens);
        cur->inst_offset = 0;
        cur->dead = (token != DWARF);
        cur->rocks = 0;
        fort->dwarves[cur_id] = cur;
        fort->dwarves[cur_id]->instructions = malloc(sizeof(char) * l);
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

