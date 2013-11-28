#include <stdio.h>
#include <stdlib.h>

#include "unit.h"
#include "../src/syntax.h"

void syntax_tests() {
  // Syntactically Correct
  assert(syntax_check("+"), "'+' is syntactically correct.");
  assert(syntax_check("+mmmm"), "'+mmmm' is syntactically correct.");
  assert(syntax_check("-m+"), "'-m+' is syntactically correct.");
  assert(syntax_check("+!!comment!!m"), "'!!comment!!m' is syntactically correct.");
  

  // Syntactically incorrect
  assert(!(syntax_check("")), "'' is not syntactically correct");
  assert(!(syntax_check("m")), "'m' is not syntactically correct");
  assert(!(syntax_check("-m")), "'-m' is not syntactically correct");
  assert(!(syntax_check("+l")), "'+l' is not syntactically correct");
  assert(!(syntax_check("!!comment!!")), "'!!comment!!' is not syntactically correct");
  assert(!(syntax_check("!!+!!mmm")), "'!!+!!mmm' is not syntactically correct");
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
