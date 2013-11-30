#ifndef ARMOK_RUN
#define ARMOK_RUN

#include "parse.h"

#define WORLD_SIZE 255
#define ROCKS 64
#define TRADER 1
#define MANAGER 2
#define APPRAISER 3

extern int rock_pos;
extern int *world;
extern int *workshops;
extern int step_count; 

void setup();
void teardown();
void step();
void do_step(dwarf *dwarf);

#endif
