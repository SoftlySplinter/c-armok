#include <stdio.h>
#include <stdlib.h>

#include "unit.h"
#include "syntax.h"

int main(int argc, char **argv) {
  syntax_tests();


  if(number_of_errors() > 0) {
    printf("\e[1;31m%d tests failed\e[0m\n", number_of_errors());
  } else {
    printf("\e[1;32mAll tests passed\e[0m\n");
  }
  printf("\e[1;30m%d\e[0m assertions: \e[1;32m%d\e[0m passed, \e[1;31m%d\e[0m failures.\n", number_of_asserts(), number_of_asserts() - number_of_errors(), number_of_errors());

  return number_of_errors();
}
