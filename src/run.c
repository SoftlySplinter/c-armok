#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "encode.h"
#include "syntax.h"
#include "run.h"

int step_count;
int rock_pos;
int* world;
int* workshops;
fortress* fort;
wchar_t *input = NULL;
wchar_t *output = NULL;
int input_off;
int output_off;
int print = 1;

void setup(char *in, fortress *_fort) {
  if(in != NULL) {
    input = malloc(sizeof(wchar_t) * strlen(in));
    mbstowcs(input, in, strlen(in));
  }
  output = malloc(sizeof(wchar_t));
  output[0] = '\0';
  output_off = 0;
  step_count = 0;
  rock_pos = 4;
  world = malloc(sizeof(int) * WORLD_SIZE);
  workshops = malloc(sizeof(int) * WORLD_SIZE);
  fort = _fort;
  world[0] = 0;
  world[1] = 0;
  world[2] = 0;
  world[3] = 0;
  for(int i = rock_pos; i < WORLD_SIZE; i++) {
    world[i] = ROCKS;
  }
  for(int i = 0; i < WORLD_SIZE; i++) {
    workshops[i] = 0;
  }
}

void teardown() {
  free(input);
  free(output);
  free(world);
  free(workshops);
  fort = NULL;
}

void step() {
  for(int i = 0; i < fort->dwarf_size + fort->sub_size; i++) {
    do_step(fort->dwarves[i]);
  }
  step_count++;
}

void move(dwarf *dwarf, int direction) {
  int amount = 0;
  switch(direction) {
    case LEFT:
      amount = -1;
      break;
    case RIGHT:
      amount = 1;
      break;
  }

  dwarf->pos = dwarf->pos + amount;

  if(dwarf->pos == 0) {
    fprintf(stderr, "A dwarf went insane and tried to swim in lava\n");
    dwarf->dead = 1;
  }
  if(dwarf->pos == rock_pos) {
    fprintf(stderr, "A dwarf was hammered by stone\n");
    dwarf->dead = 1;
  }
}

void mine(dwarf *dwarf) {
  if(dwarf->pos == rock_pos - 1) {
    rock_pos++;
  }
  if(world[dwarf->pos + 1] > 0) {
    world[dwarf->pos + 1]--;
    dwarf->rocks++;
  }
}

void work_trader(dwarf *dwarf) {
  if(dwarf->rocks == 0) {
    if(input == NULL || *(input + input_off) == 0x0000) {
      fprintf(stderr, "Elves stabbed a dwarf in the back\n");
      dwarf->dead = 1;
    } else {
      wchar_t i = decode(*(input + input_off));
      dwarf->rocks = i;
      input_off++;
    }
  } else {
    output_off++;
    output = realloc(output, sizeof(wchar_t) * (output_off + 1));
    wchar_t c = encode(dwarf->rocks);
    output[output_off - 1] = c;
    output[output_off] = '\0';

    if(print) {
      printf("%lc", c);
    }

    dwarf->rocks = 0;
  }
}

void work_manager(dwarf *dwarf) {
  if(world[dwarf->pos] > (fort->dwarf_size + fort->sub_size)) {
    fprintf(stderr, "A dwarf was executed for breaking a mandate\n");
    dwarf->dead = 1;
  } else if(world[dwarf->pos] == 0) {
    workshops[dwarf->pos] = 0;
  } else {
    char *new_inst = fort->dwarves[world[dwarf->pos] - 1]->instructions;
    char *remain_inst = dwarf->instructions + dwarf->inst_offset + step_count + 1;


    if(strlen(remain_inst) <= 0) {
      free(dwarf->instructions);
      dwarf->instructions = malloc(sizeof(char) * strlen(new_inst));
      strcpy(dwarf->instructions, new_inst);
      dwarf->inst_offset = -(step_count + 1);
    } else {
      dwarf->inst_offset = -(step_count + 1);
      char *new = (char *) malloc(sizeof(char) * (strlen(new_inst) + strlen(remain_inst) + 1));
      new = strcpy(new, new_inst);
      new = strcat(new, remain_inst);
      free(dwarf->instructions);
      dwarf->instructions = new;
    }
  }
}

void work_appraiser(dwarf *dwarf) {
  if(dwarf->rocks > world[dwarf->pos]) {
    dwarf->rocks--;
    world[dwarf->pos - 1]++;
  }
}

void work(dwarf *dwarf) {
  switch(workshops[dwarf->pos]) {
  case TRADER:
    work_trader(dwarf);
    break;
  case MANAGER:
    work_manager(dwarf);
    break;
  case APPRAISER:
    work_appraiser(dwarf);
    break;
  default:
    switch(dwarf->rocks) {
      case 0:
        fprintf(stderr, "A dwarf when stark raving mad\n");
        dwarf->dead = 1;
        break;
      case TRADER:
      case MANAGER:
      case APPRAISER:
        workshops[dwarf->pos] = dwarf->rocks;
        dwarf->rocks = 0;
        break;
      default:
        fprintf(stderr, "Unknown workshop %d\n", dwarf->rocks);
    }
  }
}

void do_step(dwarf *dwarf) {
  if(!dwarf->dead) {
    if(strlen(dwarf->instructions) <= dwarf->inst_offset + step_count) {
      fprintf(stderr, "A dwarf was struck by melancholy\n");
      dwarf->dead = 1;
    } else {
      char token = *(dwarf->instructions + dwarf->inst_offset + step_count);
      switch(token) {
      case LEFT:
      case RIGHT:
        move(dwarf, token);
        break;
      case MINE:
        mine(dwarf);
        break;
      case DUMP:
        if(dwarf->rocks > 0) {
          dwarf->rocks--;
          world[dwarf->pos - 1]++;
        }
        break;
      case WORK:
        work(dwarf);
        break;
      }
    }
  }
}

void step_inc() {
  step_count++;
}
