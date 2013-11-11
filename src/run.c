#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "run.h"

int step_count = 0;
int rock_pos = 4;
int* world;
char* input = NULL;

void setup(char *in) {
  input = in;
  world = malloc(sizeof(int) * WORLD_SIZE);
  world[0] = 0;
  world[1] = 0;
  world[2] = 0;
  world[3] = 0;
  for(int i = rock_pos; i < WORLD_SIZE; i++) {
    world[i] = ROCKS;
  }
}

void teardown() {
  free(world);
}

void step(dwarf *dwarf) {
  if(!dwarf->dead) {
    if(strlen(dwarf->instructions) <= step_count) {
      printf("\nA dwarf was struck by melancholy\n");
      dwarf->dead = 1;
    } else {
      char token = *(dwarf->instructions+step_count);
//      printf("%c\n", token);
      switch(token) {
        case LEFT:
          dwarf->pos = dwarf->pos - 1;
          if(dwarf->pos == 0) {
            printf("\nA dwarf went insane and tried to swim in lava\n");
            dwarf->dead = 1;
          }
          break;
        case RIGHT:
          dwarf->pos = dwarf->pos + 1;
          if(dwarf->pos == rock_pos) {
            printf("\nA dwarf was hammered by stone\n");
            dwarf->dead = 1;
          }
          break;
        case MINE:
          if(dwarf->pos == rock_pos - 1) {
            rock_pos++;
          }
          if(world[dwarf->pos + 1] > 0) {
            world[dwarf->pos + 1]--;
            dwarf->rocks++;
          }
          break;
        case WORK:
          switch(world[dwarf->pos]) {
            case TRADER:
              if(dwarf->rocks == 0) {
                if(*input = '\0') {
                  printf("\nElves stabbed a dwarf in the back\n");
                  dwarf->dead = 1;
                } else {
                  printf("%s\n", input); 
//                  dwarf->rocks = (int) *input;
                  input++;
                }
              } else {
                unsigned char character = dwarf->rocks;
                printf("%c", character, dwarf->rocks);
                dwarf->rocks = 0;
              }
            default:
              switch(-dwarf->rocks) {
                case 0:
                  printf("A dwarf when stark raving mad\n");
                  dwarf->dead = 1;
                  break;
                case TRADER:
                case MANAGER:
                case APPRAISER:
                  world[dwarf->pos] = -dwarf->rocks;
                  break;
              }
          }
      }
    }
  }
}

void step_inc() {
  step_count++;
}
