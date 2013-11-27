#include <stdio.h>
#include <stdlib.h>

#include "unit.h"

int main(int argc, char **argv) {
  int a = number_of_asserts();
  int e = number_of_errors();
  assert(a == 0, "Asserts should start at 0");
  assert(e == 0, "Errors should start at 0");

  assert(1, "Something");


  if(number_of_errors() > 0) {
    printf("\e[1;31m%d tests failed\e[0m\n", number_of_errors());
  } else {
    printf("\e[1;32mAll tests passed\e[0m\n");
  }
  printf("\e[1;30m%d\e[0m assertions, \e[1;31m%d\e[0m failures.\n", number_of_asserts(), number_of_errors());

  return number_of_errors();
}
