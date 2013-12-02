#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "unit.h"

int errors = 0;
int asserts = 0;

char **error_messages;

void assert(int condition, const char *message, ...) {
  asserts++;
  if(!condition) {
    errors++;
    error_messages = realloc(error_messages, sizeof(char) * errors);
    error_messages[errors - 1] = malloc(sizeof(char) * 255);
    va_list arg;
    va_start(arg, message);
    vsprintf(error_messages[errors-1], message, arg);
    va_end(arg);
    printf("\e[1;31m-\e[0m");
  } else {
    printf(".");
  }
}

int report(const char* name) {
  printf("\n");
  printf("\n");
  if(errors > 0) {
    printf("\e[1;31m%s: %d tests failed:\e[0m\n", name, errors);
    for(int i = 0; i < errors; i++) {
      printf("  %s\n", error_messages[i]);
      free(error_messages[i]);
    }
    free(error_messages);
  } else {
    printf("\e[1;32m%s: All tests passed\e[0m\n", name);
  }
  printf("\e[1;30m%d\e[0m assertions: \e[1;32m%d\e[0m passed, \e[1;31m%d\e[0m failures.\n", asserts, asserts - errors, errors);
  printf("\n");
  printf("\n");

  int ret = errors;
  errors = 0;
  asserts = 0;

  return ret;
}
