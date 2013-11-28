#include <stdio.h>
#include <stdlib.h>

#include "unit.h"
#include "../src/syntax.h"

void reset() {
  _syn_dwarf = 0;
  _syn_sub = 0;
  _syn_comment = 0;
}

void syntax_tests() {
  // Syntactically Correct
  assert(syntax_check("+"), "'+' is syntactically correct.");
  assert(_syn_dwarf == 1, "'+' should have created 1 dwarf.");
  assert(_syn_sub == 0, "'+' should have created 0 subs.");

  assert(syntax_check("+mmmm"), "'+mmmm' is syntactically correct.");
  assert(_syn_dwarf == 1, "'+mmmm' should have created 1 dwarf."); 
  assert(_syn_sub == 0, "'+mmmm' should have created 0 subs.");

  assert(syntax_check("-m+"), "'-m+' is syntactically correct.");
  assert(_syn_dwarf == 1, "'-m+' should have created 1 dwarf."); 
  assert(_syn_sub == 1, "'-m+' should have created 1 subs.");

  assert(syntax_check("+!!comment!!m"), "'+!!comment!!m' is syntactically correct.");
  assert(_syn_dwarf == 1, "'+!!comment!!m' should have created 1 dwarf."); 
  assert(_syn_sub == 0, "'+!!comment!!m' should have created 0 subs.");
  

  assert(syntax_check("++<+w+>>mmww"), "'++<+w+>>mmww' is syntactically correct.");
  assert(_syn_dwarf == 4, "'++<+w+>>mmww' should have created 4 dwarves."); 
  assert(_syn_sub == 0, "'++<+w+>>mmww' should have created 0 subs.");

  // Syntactically incorrect
  assert(!syntax_check(""), "'' is not syntactically correct");
  assert(!syntax_check("m"), "'m' is not syntactically correct");
  assert(!syntax_check("-m"), "'-m' is not syntactically correct");
  assert(!syntax_check("+l"), "'+l' is not syntactically correct");
  assert(!syntax_check("!!comment!!"), "'!!comment!!' is not syntactically correct");
  assert(!syntax_check("!!+!!mmm"), "'!!+!!mmm' is not syntactically correct");
  assert(!syntax_check("m+"), "'m+' is not syntactically correct.");

  
  // Valid tokens
  reset();
  assert(syntax_check_token(DWARF), "'+' is a valid token");
  assert(_syn_dwarf == 1, "'+' should have created 1 dwarf");
  assert(_syn_sub == 0, "'+' should have created 0 subs");

  reset();
  assert(syntax_check_token(SUB), "'-' is a valid token");
  assert(_syn_dwarf == 0, "'-' should have created 0 dwarves");
  assert(_syn_sub == 1, "'-' should have created 1 sub");
  
  reset();
  assert(syntax_check_token(COMMENT), "'!' is a valid token");
  assert(syntax_check_token(COMMENT), "'!' following a '!' is a valid token");
  assert(_syn_dwarf == 0, "'!!' should have created 0 dwarves");
  assert(_syn_sub == 0, "'!!' should have created 0 subs");
  assert(_syn_comment, "''!!' should have toggelled comment");

  reset();
  _syn_comment = 1;
  assert(syntax_check_token('t'), "'t' is a valid token in comment");
  assert(syntax_check_token(DWARF), "'+' is a valid token in comment");
  assert(_syn_dwarf == 0, "Comments should not create dwaves");
  assert(_syn_sub == 0, "Comments should not create subs");
  assert(_syn_comment, "Comment should not toggle");
}

int main(int argc, char **argv) {
  syntax_tests();


  if(number_of_errors() > 0) {
    printf("\e[1;31m%d tests failed\e[0m\n", number_of_errors());
  } else {
    printf("\e[1;32mAll tests passed\e[0m\n");
  }
  printf("\e[1;30m%d\e[0m assertions, \e[1;31m%d\e[0m failures.\n", number_of_asserts(), number_of_errors());

  return number_of_errors();
}
