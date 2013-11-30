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

int inst_len(char *tokens, int offset) {
  int len = 0;
  int count = 1 + offset;
  int comment = 0;
  int prev_comment = 0;
  char token = *(tokens + count);
  int slen = strlen(tokens);
  while((token != DWARF || comment) && 
        (token != SUB || comment) && 
        token != '\0') {
    int temp_prev_comment = prev_comment;
    prev_comment = 0;
    if(token == COMMENT) {
      if(temp_prev_comment) {
        comment = !(comment);
      } else {
        prev_comment = 1;
      }
    }
    if(!comment) {
      switch (token) {
        case MINE:
        case WORK:
        case DUMP:
        case LEFT:
        case RIGHT:
          len++;
      }
    }
    count++;
    token = *(tokens + count);
  }
  return len;
}

fortress *parse(char *tokens) {
  fortress *fort = malloc(sizeof(fortress));
  fort->dwarf_size = count(tokens, DWARF);
  fort->sub_size = count(tokens, SUB);
  fort->alive = fort->dwarf_size;
  fort->dwarves = malloc(sizeof(dwarf*) * (fort->dwarf_size + fort->sub_size));
  int cur_id = -1;
  int comment = 0;
  int prev_comment = 0;
  dwarf *cur = NULL;

  char token = *tokens;
  int step = 0;
  int c = 0;
  while(token != '\0') {
    #ifdef DEBUG
    printf("Processing Token: %c\n", token);
    #endif

    int temp_prev_comment = prev_comment;
    prev_comment = 0;
    if(token == COMMENT) {
      if(temp_prev_comment) {
        comment ^= 1;
      } else {
        prev_comment = 1;
      }
    }

    if(!comment) {
      switch(token) {
      case DWARF:
      case SUB:
        cur_id++;
        dwarf *cur = malloc(sizeof(dwarf));
        cur->id = cur_id;
        cur->pos = 1;
        int l = inst_len(tokens, c);
        cur->inst_offset = 0;
        cur->dead = (token != DWARF);
        cur->rocks = 0;
        fort->dwarves[cur_id] = cur;

        cur->instructions = malloc(sizeof(char) * l + 1);
        cur->instructions[l] = '\0';

        step = 0;
        break;
      case MINE:
      case WORK:
      case DUMP:
      case LEFT:
      case RIGHT:
        cur->instructions[step] = token;
        step++;
        break;
      }
    }
    c++;
    token = *(tokens + c);
  }
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

