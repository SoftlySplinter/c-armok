#ifndef DF_RUN
#define DF_RUN

#include "parse.h"

#define WORLD_SIZE 255
#define ROCKS 64
#define TRADER 1
#define MANAGER 2
#define APPRAISER 3


void setup();
void teardown();
void step(dwarf *dwarf);
void step_inc();

#endif
