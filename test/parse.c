#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "unit.h"
#include "parse.h"
#include "../src/parse.h"

void do_valid_parse(char *inst, int no_dwarves, int no_subs, ...) {
  va_list args;
  va_start(args, no_dwarves + no_subs);
  fortress *fort = parse(inst);
  char message[64 + strlen(inst)];// = "'%s' should have created 1 dwarves and 1 subs"
  sprintf(message, "'%s' expected %d dwarves, %d subs. Actual %d dwarves, %d subs", inst, no_dwarves, no_subs, fort->dwarf_size, fort->sub_size);

  int res = fort->dwarf_size == no_dwarves && fort->sub_size == no_subs;
  assert(res, message);

  if(!res) return;

  for(int i = 0; i < no_dwarves + no_subs; i++) {
    char *actual = fort->dwarves[i]->instructions;
    char *expected = va_arg(args, char*);
    char message[64 + strlen(actual) + strlen(expected)];
    sprintf(message, "Actual instructions '%s' do not match expected '%s'", actual, expected);
    int cmp = strcmp(actual, expected);
    assert(cmp == 0, message);
  }

  free_fort(fort);
  va_end(args);
}

void valid_parse() {
  do_valid_parse("+", 1, 0, "");
  do_valid_parse("++", 2, 0, "", "");
  do_valid_parse("+-", 1, 1, "", "");
  do_valid_parse("-+", 1, 1, "", "");
  do_valid_parse("+m", 1, 0, "m");
  do_valid_parse("+m-m", 1, 1, "m", "m");
  do_valid_parse("+mmmm", 1, 0, "mmmm");
  do_valid_parse("+mmmmmmmmmmmmmmmmmmmm", 1, 0, "mmmmmmmmmmmmmmmmmmmm");
  do_valid_parse("++<+w+>>>+>>mww", 5, 0, "", "<", "w", ">>>", ">>mww");
  do_valid_parse("+>>mmwm>d<w-><w+ww", 2, 1, ">>mmwm>d<w", "><w", "ww");
}

void invalid_parse() {

}

void parse_tests() {
  valid_parse();
  invalid_parse();
}

