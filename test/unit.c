#include <stdio.h>

#include "unit.h"

int errors;
int asserts;

void assert(int condition, char *message) {
  asserts++;
  if(!condition) {
    errors++;
    fprintf(stderr, "\e[1;31mAssertion failed: %s\e[0m\n", message);
  }
}

int number_of_errors() {
  return errors;
}

int number_of_asserts() {
  return asserts;
}

