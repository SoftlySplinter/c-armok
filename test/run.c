#include <stdio.h>

#include "unit.h"
#include "run.h"

#include "../src/parse.h"
#include "../src/run.h"

const char *res_workshop(int id) {
  switch(id) {
  case 0:
    return "No Workshop";
  case TRADER:
    return "Trade Depo";
  case MANAGER:
    return "Manager";
  case APPRAISER:
    return "Appraiser";
  default:
    return "Unknown Workshop";
  }
}

void test_run_setup() {
  fortress *fort = parse("+-");
  char *in = NULL;
  setup(in, fort);

  assert(rock_pos == 4, "Rock position should start at position 4, not %d", rock_pos); 
  assert(step_count == 0, "Step count should start at 0, not %d", step_count);

  int pos_wrong = 0;
  int work_wrong = 0;
  for(int i = 0; i < WORLD_SIZE; i++) {
    if(workshops[i] == 0) {
      work_wrong++;
    }
    if(i < rock_pos) {
      assert(world[i] == 0, "There should be no rocks at position %d, found %d rocks", i, world[i]);
    } else {
      if(world[i] != 64) {
        pos_wrong++;
      }
    }
  }
  // TODO build a string with the incorrect positions in.
  assert(pos_wrong == 0, "Positions after %d should have 64 rocks, found %d places with rocks != 6", WORLD_SIZE);
  assert(work_wrong == 0, "World should start with no workshops, found %d workshops.", work_wrong);

  for(int i = 0; i < fort->dwarf_size + fort->sub_size; i++) {
    assert(fort->dwarves[i]->pos == 1, "Dwarf %d should have started at position %d, not %d", i, 1, fort->dwarves[i]->pos);
    assert(fort->dwarves[i]->rocks == 0, "Dwarf %d should have started with %d rocks, not %d", i, 0, fort->dwarves[i]->rocks);
  }
  
}

fortress* do_test(char *instructions, char *in) {
  fortress *fort = parse(instructions);
  setup(in, fort);
  return fort;
}

void test_basic() {
  fortress *fort = NULL;

  fort = do_test("+", NULL);
  assert(!fort->dwarves[0]->dead, "Dwarf 0 should start alive.");
  step();
  assert(fort->dwarves[0]->pos == 1, "Dwarf 0 should not have moved.");
  assert(fort->dwarves[0]->dead, "Dwarf 0 should have died of melancholy.");
  teardown();
  free_fort(fort);
}

void test_move() {
  fortress *fort = NULL;

  fort = do_test("+<", NULL);
  step();
  assert(fort->dwarves[0]->pos == 0, "Dwarf 0 should have moved to position 0, not %d", fort->dwarves[0]->pos);
  assert(fort->dwarves[0]->dead, "Dwarf 0 should have died from moving into lava.");
  teardown();
  free_fort(fort);

  fort = do_test("+>", NULL);
  step();
  assert(fort->dwarves[0]->pos == 2, "Dwarf 0 should have moved to position 2, not %d", fort->dwarves[0]->pos);
  step();
  assert(fort->dwarves[0]->dead, "Dwarf 0 should have died of melancholy.");
  teardown();

  fort = do_test("+><", NULL);
  step();
  assert(fort->dwarves[0]->pos == 2, "Dwarf 0 should have moved to position 2, not %d", fort->dwarves[0]->pos);
  step();
  assert(fort->dwarves[0]->pos == 1, "Dwarf 0 should have moved to position 1, not %d", fort->dwarves[0]->pos);
  step();
  assert(fort->dwarves[0]->dead, "Dwarf 0 should have died of melancholy.");
  teardown();

  fort = do_test("+>>>", NULL);
  assert(!fort->dwarves[0]->dead, "Dwarf 0 should start alive.");
  step();
  assert(fort->dwarves[0]->pos == 2, "Dwarf 0 should have moved to position 2, not %d", fort->dwarves[0]->pos);
  step();
  assert(fort->dwarves[0]->pos == 3, "Dwarf 0 should have moved to position 3, not %d", fort->dwarves[0]->pos);
  step();
  assert(fort->dwarves[0]->pos == 4, "Dwarf 0 should have moved to position 4, not %d", fort->dwarves[0]->pos);
  assert(fort->dwarves[0]->dead, "Dwarf 0 should have been hammered by stone.");
  teardown();
}

void test_mine() {
  fortress *fort = NULL;

  fort = do_test("+m", NULL);
  step();
  assert(rock_pos == 4, "Rock position should not have moved from position %d", rock_pos);
  assert(fort->dwarves[0]->rocks == 0, "Dwarf 0 should not have picked up any rocks, but has %d rocks", fort->dwarves[0]->pos);

  fort = do_test("+>>m", NULL);
  step();
  step();
  step();
  assert(rock_pos == 5, "Rock position should have moved to 5 due to mining, not %d", rock_pos);
  assert(fort->dwarves[0]->rocks == 1, "Dwarf 0 should have picked up 1 rock due to mining, not %d", fort->dwarves[0]->pos);
  assert(world[4] == 63, "Position 4 should have 63 rocks after mining, not %d", world[4]);
  step();
  assert(fort->dwarves[0]->dead, "Dwarf 0 should have been struck by melancholy.");
  teardown();
}

void test_dump() {
  fortress *fort = NULL;

  fort = do_test("+d", NULL);
  step();
  assert(fort->dwarves[0]->rocks == 0, "Dwarf 0 should still have 0 rocks, not %d", fort->dwarves[0]->rocks);
  assert(world[0] == 0, "Position 0 should still have 0 rocks, not %d", world[0]);

  fort = do_test("+>>md", NULL);
  step();
  step();
  step();
  step();
  assert(fort->dwarves[0]->rocks == 0, "Dwarf 0 should have 0 rocks after dumping, not %d", fort->dwarves[0]->rocks);
  assert(world[2] == 1, "Position 2 should have 1 rock after dumping, not %d", world[2]);
  teardown();
}

void test_work() {
  fortress *fort = NULL;

  fort = do_test("+>>mw", NULL);
  step();
  step();
  step();
  step();
  assert(workshops[3] == TRADER, "Workshop position 3 should have a Trade Depo, not %s", res_workshop(workshops[4]));
  assert(fort->dwarves[0]->rocks == 0, "Dwarf 0 should have 0 rocks after building a workshop, not %d", fort->dwarves[0]->pos);
  teardown();
}

void test_input() {
  fortress *fort = NULL;

  fort = do_test("+>>mww", NULL);
  step();
  step();
  step();
  step();
  step();
  assert(fort->dwarves[0]->dead, "Dwarf 0 should have been backstabbed by Elves.");
  teardown();

  fort = do_test("+>>mww", "H");
  step(); step(); step(); step(); step();
  assert(fort->dwarves[0]->rocks == 72, "Dwarf 0 should have been given 72 rock from the trader (Input string \"H\"), but has %d", fort->dwarves[0]->rocks);
  assert(!fort->dwarves[0]->dead, "Dwarf 0 should not have been backstabbed by Elves.");
}

int run_tests() {
//  test_run_setup();
  test_basic();
  test_move();
  test_mine();
  test_dump();
  test_work();
  test_input();
  return report("Run");
}

