#include <stdio.h>
#include <stdarg.h>

#include "unit.h"

int errors;
int asserts;

void assert(int condition, const char *message, ...) {
  asserts++;
  if(!condition) {
    errors++;
    va_list arg;
    va_start(arg, message);
    printf("\e[1;31mAssertion failed: ");
    vprintf(message, arg);
    printf("\e[0m\n");
    va_end(arg);
  }
}

int number_of_errors() {
  return errors;
}

int number_of_asserts() {
  return asserts;
}

