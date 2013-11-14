#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "run.h"

int step_count = 0;
int rock_pos = 4;
int* world;
int* workshops;
fortress* fort;
char* input = NULL;

void setup(char *in, fortress *_fort) {
  input = in;
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
  free(world);
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
    default:
      fprintf(stderr, "Invalid Direction: %d", direction);
  }

  dwarf->pos = dwarf->pos + amount;

  if(dwarf->pos == 0) {
    printf("\nA dwarf went insane and tried to swim in lava\n");
    dwarf->dead = 1;
  }
  if(dwarf->pos == rock_pos) {
    printf("\nA dwarf was hammered by stone\n");
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
    if(input == NULL || *input == '\0') {
      printf("\nElves stabbed a dwarf in the back\n");
      dwarf->dead = 1;
    } else {
      dwarf->rocks = (int) *input;
      input++;
    }
  } else {
    printf("%c", (unsigned char) dwarf->rocks);
    dwarf->rocks = 0;
  }
}

void work_manager(dwarf *dwarf) {
  if(world[dwarf->pos] > fort->dwarf_size) {
    printf("A dwarf was executed for breaking a mandate\n");
    dwarf->dead = 1;
  } else if(world[dwarf->pos] == 0) {
    printf("Destroying workshop\n");
    workshops[dwarf->pos] = 0;
  } else {
    char *new_inst = fort->dwarves[world[dwarf->pos] - 1]->instructions;
    char *remain_inst = dwarf->instructions + dwarf->inst_offset + step_count + 1;

//    printf("%s + %s\n", new_inst, remain_inst);

    if(strlen(remain_inst) <= 0) {
      free(dwarf->instructions);
      dwarf->instructions = malloc(sizeof(char) * strlen(new_inst));
      strcpy(dwarf->instructions, new_inst);
      dwarf->inst_offset = -(step_count + 1);
//      printf("%s\n", dwarf->instructions);
    } else {
      char *temp = malloc(sizeof(char) * strlen(remain_inst));
      strcpy(temp, remain_inst);
      dwarf->inst_offset = -(step_count + 1);
//      free(dwarf->instructions);
      char *new = malloc(sizeof(char) * strlen(new_inst) + strlen(temp));
      strcat(new, new_inst);
      strcat(new, temp);
      dwarf->instructions = malloc(sizeof(char) * strlen(new));
      strcpy(dwarf->instructions, new);
//      free(new);
//      free(temp);
    }
  }
}

void work_appraiser(dwarf *dwarf) {

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
        printf("A dwarf when stark raving mad\n");
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

void step(dwarf *dwarf) {
  if(!dwarf->dead) {
    if(strlen(dwarf->instructions) <= dwarf->inst_offset + step_count) {
      printf("%c\n", *(dwarf->instructions));
      printf("\nA dwarf was struck by melancholy\n");
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
